(:*******************************************************:)
(:Test:CastAs212:)
(:Written By:Joanne Tong:)
(:Date:2005-07-21T09:49:53-07:00:)
(:Purpose:Try casting xs:double(-1.75e-3) to xs:decimal:)
(:*******************************************************:)

round-half-to-even(xs:double("-1.75e-3") cast as xs:decimal,5)