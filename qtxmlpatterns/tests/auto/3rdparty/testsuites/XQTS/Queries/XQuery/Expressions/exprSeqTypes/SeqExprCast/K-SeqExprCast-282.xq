(:*******************************************************:)
(: Test: K-SeqExprCast-282                               :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Testing timezone field in xs:gYearMonth: the minute component cannot be -60. :)
(:*******************************************************:)
xs:gYearMonth("1999-01-10:60")