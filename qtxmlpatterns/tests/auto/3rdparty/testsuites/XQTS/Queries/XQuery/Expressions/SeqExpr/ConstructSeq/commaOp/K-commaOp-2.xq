(:*******************************************************:)
(: Test: K-commaOp-2                                     :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:20+01:00                       :)
(: Purpose: An expression sequence containing only empty sequences. On some implementations this triggers certain optimization paths. :)
(:*******************************************************:)
empty(((), (), ((), (), ((), (), (())), ()), (), (())))