(:*******************************************************:)
(: Test: K-SeqExprCast-1115                              :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:22+01:00                       :)
(: Purpose: 'castable as' involving xs:gDay as source type and xs:string as target type should always evaluate to true. :)
(:*******************************************************:)
xs:gDay("---03") castable as xs:string