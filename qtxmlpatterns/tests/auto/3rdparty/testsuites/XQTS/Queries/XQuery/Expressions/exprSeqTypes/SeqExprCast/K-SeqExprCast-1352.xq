(:*******************************************************:)
(: Test: K-SeqExprCast-1352                              :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:22+01:00                       :)
(: Purpose: Casting from xs:hexBinary to xs:gMonth isn't allowed. :)
(:*******************************************************:)
xs:hexBinary("0FB7") cast as xs:gMonth