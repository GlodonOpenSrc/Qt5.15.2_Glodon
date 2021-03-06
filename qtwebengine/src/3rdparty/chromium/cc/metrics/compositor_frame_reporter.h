// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_METRICS_COMPOSITOR_FRAME_REPORTER_H_
#define CC_METRICS_COMPOSITOR_FRAME_REPORTER_H_

#include <memory>
#include <vector>

#include "base/containers/flat_set.h"
#include "base/time/time.h"
#include "cc/base/base_export.h"
#include "cc/cc_export.h"
#include "cc/metrics/begin_main_frame_metrics.h"
#include "cc/metrics/event_metrics.h"
#include "cc/metrics/frame_sequence_tracker.h"
#include "components/viz/common/frame_sinks/begin_frame_args.h"
#include "components/viz/common/frame_timing_details.h"

namespace viz {
struct FrameTimingDetails;
}

namespace cc {
class LatencyUkmReporter;

// This is used for tracing and reporting the duration of pipeline stages within
// a single frame.
//
// For each stage in the frame pipeline, calling StartStage will start tracing
// that stage (and end any currently running stages).
//
// If the tracked frame is presented (i.e. the frame termination status is
// kPresentedFrame), then the duration of each stage along with the total
// latency will be reported to UMA. If the tracked frame is not presented (i.e.
// the frame termination status is kDidNotPresentFrame or
// kReplacedByNewReporter), then the duration is reported under
// CompositorLatency.DroppedFrame.*.
// The format of each stage reported to UMA is
// "CompositorLatency.[DroppedFrame.][Interaction_name.].<StageName>".
class CC_EXPORT CompositorFrameReporter {
 public:
  enum class FrameTerminationStatus {
    // The tracked compositor frame was presented.
    kPresentedFrame,

    // The tracked compositor frame was submitted to the display compositor but
    // was not presented.
    kDidNotPresentFrame,

    // Reporter that is currently at a stage is replaced by a new one (e.g. two
    // BeginImplFrames can happen without issuing BeginMainFrame, so the first
    // reporter would terminate with this status).
    kReplacedByNewReporter,

    // Frame that was being tracked did not end up being submitting (e.g. frame
    // had no damage or LTHI was ended).
    kDidNotProduceFrame,

    // Default termination status. Should not be reachable.
    kUnknown
  };

  // These values are used for indexing the UMA histograms.
  enum class FrameReportType {
    kNonDroppedFrame = 0,
    kMissedDeadlineFrame = 1,
    kDroppedFrame = 2,
    kMaxValue = kDroppedFrame
  };

  // These values are used for indexing the UMA histograms.
  enum class StageType {
    kBeginImplFrameToSendBeginMainFrame = 0,
    kSendBeginMainFrameToCommit = 1,
    kCommit = 2,
    kEndCommitToActivation = 3,
    kActivation = 4,
    kEndActivateToSubmitCompositorFrame = 5,
    kSubmitCompositorFrameToPresentationCompositorFrame = 6,
    kTotalLatency = 7,
    kStageTypeCount
  };

  enum class VizBreakdown {
    kSubmitToReceiveCompositorFrame = 0,
    kReceivedCompositorFrameToStartDraw = 1,
    kStartDrawToSwapStart = 2,
    kSwapStartToSwapEnd = 3,
    kSwapEndToPresentationCompositorFrame = 4,
    kBreakdownCount
  };

  enum class BlinkBreakdown {
    kHandleInputEvents = 0,
    kAnimate = 1,
    kStyleUpdate = 2,
    kLayoutUpdate = 3,
    kPrepaint = 4,
    kComposite = 5,
    kPaint = 6,
    kScrollingCoordinator = 7,
    kCompositeCommit = 8,
    kUpdateLayers = 9,
    kBeginMainSentToStarted = 10,
    kBreakdownCount
  };

  struct StageData {
    StageType stage_type;
    base::TimeTicks start_time;
    base::TimeTicks end_time;
    StageData();
    StageData(StageType stage_type,
              base::TimeTicks start_time,
              base::TimeTicks end_time);
    StageData(const StageData&);
    ~StageData();
  };

  CompositorFrameReporter(
      const base::flat_set<FrameSequenceTrackerType>* active_trackers,
      const viz::BeginFrameId& id,
      const base::TimeTicks frame_deadline,
      LatencyUkmReporter* latency_ukm_reporter,
      bool should_report_metrics);
  ~CompositorFrameReporter();

  CompositorFrameReporter(const CompositorFrameReporter& reporter) = delete;
  CompositorFrameReporter& operator=(const CompositorFrameReporter& reporter) =
      delete;

  std::unique_ptr<CompositorFrameReporter> CopyReporterAtBeginImplStage() const;

  const viz::BeginFrameId frame_id_;

  // Note that the started stage may be reported to UMA. If the histogram is
  // intended to be reported then the histograms.xml file must be updated too.
  void StartStage(StageType stage_type, base::TimeTicks start_time);
  void TerminateFrame(FrameTerminationStatus termination_status,
                      base::TimeTicks termination_time);
  void SetBlinkBreakdown(std::unique_ptr<BeginMainFrameMetrics> blink_breakdown,
                         base::TimeTicks begin_main_start);
  void SetVizBreakdown(const viz::FrameTimingDetails& viz_breakdown);
  void SetEventsMetrics(std::vector<EventMetrics> events_metrics);

  int StageHistorySizeForTesting() { return stage_history_.size(); }

  void OnFinishImplFrame(base::TimeTicks timestamp);
  void OnAbortBeginMainFrame(base::TimeTicks timestamp);
  void OnDidNotProduceFrame();
  bool did_finish_impl_frame() const { return did_finish_impl_frame_; }
  bool did_abort_main_frame() const { return did_abort_main_frame_; }
  bool did_not_produce_frame() const { return did_not_produce_frame_; }
  base::TimeTicks impl_frame_finish_time() const {
    return impl_frame_finish_time_;
  }

 private:
  void DroppedFrame();
  void MissedDeadlineFrame();

  void TerminateReporter();
  void EndCurrentStage(base::TimeTicks end_time);
  void ReportCompositorLatencyHistograms() const;
  void ReportLatencyHistograms(bool report_event_latency = false,
                               bool report_delayed_latency = false);
  void ReportStageHistogramWithBreakdown(
      const StageData& stage,
      FrameSequenceTrackerType frame_sequence_tracker_type =
          FrameSequenceTrackerType::kMaxType) const;
  void ReportBlinkBreakdowns(
      const base::TimeTicks start_time,
      FrameSequenceTrackerType frame_sequence_tracker_type) const;

  // Report histogram and trace event stage for one Viz breakdown
  void ReportVizBreakdownStage(
      VizBreakdown stage,
      const base::TimeTicks start_time,
      const base::TimeTicks end_time,
      FrameSequenceTrackerType frame_sequence_tracker_type) const;

  void ReportVizBreakdowns(
      const base::TimeTicks start_time,
      FrameSequenceTrackerType frame_sequence_tracker_type) const;
  void ReportCompositorLatencyHistogram(
      FrameSequenceTrackerType intraction_type,
      const int stage_type_index,
      base::TimeDelta time_delta) const;
  void ReportEventLatencyHistograms() const;

  // Generate a trace event corresponding to a Viz breakdown under
  // SubmitCompositorFrameToPresentationCompositorFrame stage in
  // PipelineReporter. This function only generates trace events and does not
  // report histograms.
  void ReportVizBreakdownTrace(VizBreakdown substage,
                               const base::TimeTicks start_time,
                               const base::TimeTicks end_time) const;

  void ReportAllTraceEvents(const char* termination_status_str) const;

  const bool should_report_metrics_;

  StageData current_stage_;
  BeginMainFrameMetrics blink_breakdown_;
  viz::FrameTimingDetails viz_breakdown_;

  // Stage data is recorded here. On destruction these stages will be reported
  // to UMA if the termination status is |kPresentedFrame|. Reported data will
  // be divided based on the frame submission status.
  std::vector<StageData> stage_history_;

  // This method is only used for DCheck
  base::TimeDelta SumOfStageHistory() const;

  // List of metrics for events affecting this frame.
  std::vector<EventMetrics> events_metrics_;

  FrameReportType report_type_ = FrameReportType::kNonDroppedFrame;
  base::TimeTicks frame_termination_time_;
  base::TimeTicks begin_main_frame_start_;
  FrameTerminationStatus frame_termination_status_ =
      FrameTerminationStatus::kUnknown;

  const base::flat_set<FrameSequenceTrackerType>* active_trackers_;

  LatencyUkmReporter* latency_ukm_reporter_;

  // Indicates if work on Impl frame is finished.
  bool did_finish_impl_frame_ = false;
  // Indicates if main frame is aborted after begin.
  bool did_abort_main_frame_ = false;
  // Flag indicating if DidNotProduceFrame is called for this reporter
  bool did_not_produce_frame_ = false;
  // The time that work on Impl frame is finished. It's only valid if the
  // reporter is in a stage other than begin impl frame.
  base::TimeTicks impl_frame_finish_time_;
  base::TimeTicks frame_deadline_;
};
}  // namespace cc

#endif  // CC_METRICS_COMPOSITOR_FRAME_REPORTER_H_"
