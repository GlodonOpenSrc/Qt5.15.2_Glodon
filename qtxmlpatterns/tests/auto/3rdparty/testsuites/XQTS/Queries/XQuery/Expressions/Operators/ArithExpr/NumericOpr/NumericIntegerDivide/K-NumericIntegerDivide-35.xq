(:*******************************************************:)
(: Test: K-NumericIntegerDivide-35                       :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: A test whose essence is: `xs:float("3") idiv xs:float("INF") eq xs:float(0)`. :)
(:*******************************************************:)
xs:float("3") idiv xs:float("INF") eq xs:float(0)