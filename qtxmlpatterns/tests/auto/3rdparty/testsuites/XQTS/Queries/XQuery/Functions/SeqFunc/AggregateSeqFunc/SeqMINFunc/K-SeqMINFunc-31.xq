(:*******************************************************:)
(: Test: K-SeqMINFunc-31                                 :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:23+01:00                       :)
(: Purpose: A test whose essence is: `string(min((xs:float(-3), xs:untypedAtomic("3"), xs:double("NaN")))) eq "NaN"`. :)
(:*******************************************************:)
string(min((xs:float(-3), xs:untypedAtomic("3"), xs:double("NaN"))))
			eq "NaN"