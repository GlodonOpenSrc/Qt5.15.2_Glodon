(:*******************************************************:)
(: Test: K-RangeExpr-21                                  :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:20+01:00                       :)
(: Purpose: A test whose essence is: `deep-equal((0, -1, -2, -3, -4, -5), reverse(-5 to 0))`. :)
(:*******************************************************:)
deep-equal((0, -1, -2, -3, -4, -5), reverse(-5 to 0))