(:*******************************************************:)
(: Test: K-QuantExprWithout-92                           :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Nested variable bindings can reference each other. :)
(:*******************************************************:)
some $a in (1, 2), $b in $a satisfies $b