(:*******************************************************:)
(: Test: K-SeqExprCast-377                               :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: '00004-08-01' is an invalid lexical representation for xs:date; if the year part has more than four digits, leading zeros are prohibited. :)
(:*******************************************************:)
xs:date("00004-08-01")