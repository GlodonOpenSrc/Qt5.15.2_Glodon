(:*******************************************************:)
(: Test: K-ErrorFunc-6                                   :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:22+01:00                       :)
(: Purpose: When fn:error() is passed a description, the first argument may be an empty sequence. :)
(:*******************************************************:)
error((), "description")