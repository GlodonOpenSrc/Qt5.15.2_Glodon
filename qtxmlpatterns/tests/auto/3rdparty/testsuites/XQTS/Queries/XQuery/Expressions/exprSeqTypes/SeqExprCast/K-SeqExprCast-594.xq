(:*******************************************************:)
(: Test: K-SeqExprCast-594                               :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:22+01:00                       :)
(: Purpose: Casting from xs:integer to xs:string is allowed and should always succeed. :)
(:*******************************************************:)
xs:integer("6789") cast as xs:string
                    ne
                  xs:string("an arbitrary string")