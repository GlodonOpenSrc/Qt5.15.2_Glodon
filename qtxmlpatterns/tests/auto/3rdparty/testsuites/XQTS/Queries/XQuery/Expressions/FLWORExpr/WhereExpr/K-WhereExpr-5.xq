(:*******************************************************:)
(: Test: K-WhereExpr-5                                   :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: A for expression binding to one single value, combined with a positive where clause. :)
(:*******************************************************:)
empty(for $i in 1 where false() return $i)