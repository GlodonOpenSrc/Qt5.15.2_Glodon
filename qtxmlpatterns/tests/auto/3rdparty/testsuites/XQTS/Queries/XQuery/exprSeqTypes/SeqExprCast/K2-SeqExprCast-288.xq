(:*******************************************************:)
(: Test: K2-SeqExprCast-288                              :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Cast xs:float(NaN) to xs:short.              :)
(:*******************************************************:)
xs:short(xs:float("NaN"))