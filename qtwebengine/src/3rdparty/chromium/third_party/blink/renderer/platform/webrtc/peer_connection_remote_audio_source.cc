// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/webrtc/peer_connection_remote_audio_source.h"

#include <string>
#include <utility>

#include "base/logging.h"
#include "base/strings/stringprintf.h"
#include "base/time/time.h"
#include "media/base/audio_bus.h"
#include "third_party/blink/public/platform/modules/webrtc/webrtc_logging.h"

namespace blink {

namespace {
// Used as an identifier for the down-casters.
void* const kPeerConnectionRemoteTrackIdentifier =
    const_cast<void**>(&kPeerConnectionRemoteTrackIdentifier);

void SendLogMessage(const std::string& message) {
  blink::WebRtcLogMessage("PCRAS::" + message);
}

}  // namespace

PeerConnectionRemoteAudioTrack::PeerConnectionRemoteAudioTrack(
    scoped_refptr<webrtc::AudioTrackInterface> track_interface)
    : MediaStreamAudioTrack(false /* is_local_track */),
      track_interface_(std::move(track_interface)) {
  blink::WebRtcLogMessage(
      base::StringPrintf("PCRAT::PeerConnectionRemoteAudioTrack({id=%s})",
                         track_interface_->id().c_str()));
}

PeerConnectionRemoteAudioTrack::~PeerConnectionRemoteAudioTrack() {
  blink::WebRtcLogMessage(
      base::StringPrintf("PCRAT::~PeerConnectionRemoteAudioTrack([id=%s])",
                         track_interface_->id().c_str()));
  // Ensure the track is stopped.
  MediaStreamAudioTrack::Stop();
}

// static
PeerConnectionRemoteAudioTrack* PeerConnectionRemoteAudioTrack::From(
    MediaStreamAudioTrack* track) {
  if (track &&
      track->GetClassIdentifier() == kPeerConnectionRemoteTrackIdentifier)
    return static_cast<PeerConnectionRemoteAudioTrack*>(track);
  return nullptr;
}

void PeerConnectionRemoteAudioTrack::SetEnabled(bool enabled) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  blink::WebRtcLogMessage(base::StringPrintf(
      "PCRAT::SetEnabled([id=%s] {enabled=%s})", track_interface_->id().c_str(),
      (enabled ? "true" : "false")));

  // This affects the shared state of the source for whether or not it's a part
  // of the mixed audio that's rendered for remote tracks from WebRTC.
  // All tracks from the same source will share this state and thus can step
  // on each other's toes.
  // This is also why we can't check the enabled state for equality with
  // |enabled| before setting the mixing enabled state. This track's enabled
  // state and the shared state might not be the same.
  track_interface_->set_enabled(enabled);

  MediaStreamAudioTrack::SetEnabled(enabled);
}

void* PeerConnectionRemoteAudioTrack::GetClassIdentifier() const {
  return kPeerConnectionRemoteTrackIdentifier;
}

PeerConnectionRemoteAudioSource::PeerConnectionRemoteAudioSource(
    scoped_refptr<webrtc::AudioTrackInterface> track_interface,
    scoped_refptr<base::SingleThreadTaskRunner> task_runner)
    : MediaStreamAudioSource(std::move(task_runner),
                             false /* is_local_source */),
      track_interface_(std::move(track_interface)),
      is_sink_of_peer_connection_(false) {
  DCHECK(track_interface_);
  SendLogMessage(base::StringPrintf("PeerConnectionRemoteAudioSource([id=%s])",
                                    track_interface_->id().c_str()));
}

PeerConnectionRemoteAudioSource::~PeerConnectionRemoteAudioSource() {
  SendLogMessage(base::StringPrintf("~PeerConnectionRemoteAudioSource([id=%s])",
                                    track_interface_->id().c_str()));
  EnsureSourceIsStopped();
}

std::unique_ptr<MediaStreamAudioTrack>
PeerConnectionRemoteAudioSource::CreateMediaStreamAudioTrack(
    const std::string& id) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  return std::make_unique<PeerConnectionRemoteAudioTrack>(track_interface_);
}

bool PeerConnectionRemoteAudioSource::EnsureSourceIsStarted() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  if (is_sink_of_peer_connection_)
    return true;
  SendLogMessage(base::StringPrintf("EnsureSourceIsStarted([id=%s])",
                                    track_interface_->id().c_str()));
  track_interface_->AddSink(this);
  is_sink_of_peer_connection_ = true;
  return true;
}

void PeerConnectionRemoteAudioSource::EnsureSourceIsStopped() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  if (is_sink_of_peer_connection_) {
    SendLogMessage(base::StringPrintf("EnsureSourceIsStopped([id=%s])",
                                      track_interface_->id().c_str()));
    track_interface_->RemoveSink(this);
    is_sink_of_peer_connection_ = false;
  }
}

void PeerConnectionRemoteAudioSource::OnData(const void* audio_data,
                                             int bits_per_sample,
                                             int sample_rate,
                                             size_t number_of_channels,
                                             size_t number_of_frames) {
  // Debug builds: Note that this lock isn't meant to synchronize anything.
  // Instead, it is being used as a run-time check to ensure there isn't already
  // another thread executing this method. The reason we don't use
  // base::ThreadChecker here is because we shouldn't be making assumptions
  // about the private threading model of libjingle. For example, it would be
  // legitimate for libjingle to use a different thread to invoke this method
  // whenever the audio format changes.
#ifndef NDEBUG
  const bool is_only_thread_here = single_audio_thread_guard_.Try();
  DCHECK(is_only_thread_here);
#endif

  // TODO(tommi): We should get the timestamp from WebRTC.
  base::TimeTicks playout_time(base::TimeTicks::Now());

  if (!audio_bus_ ||
      static_cast<size_t>(audio_bus_->channels()) != number_of_channels ||
      static_cast<size_t>(audio_bus_->frames()) != number_of_frames) {
    audio_bus_ = media::AudioBus::Create(number_of_channels, number_of_frames);
  }

  audio_bus_->FromInterleaved(audio_data, number_of_frames,
                              bits_per_sample / 8);

  media::AudioParameters params = MediaStreamAudioSource::GetAudioParameters();
  if (!params.IsValid() ||
      params.format() != media::AudioParameters::AUDIO_PCM_LOW_LATENCY ||
      static_cast<size_t>(params.channels()) != number_of_channels ||
      params.sample_rate() != sample_rate ||
      static_cast<size_t>(params.frames_per_buffer()) != number_of_frames) {
    MediaStreamAudioSource::SetFormat(
        media::AudioParameters(media::AudioParameters::AUDIO_PCM_LOW_LATENCY,
                               media::GuessChannelLayout(number_of_channels),
                               sample_rate, number_of_frames));
  }

  MediaStreamAudioSource::DeliverDataToTracks(*audio_bus_, playout_time);

#ifndef NDEBUG
  if (is_only_thread_here)
    single_audio_thread_guard_.Release();
#endif
}

}  // namespace blink
