(:*******************************************************:)
(:Test: op-time-equal2args-20                            :)
(:Written By: Carmelo Montanez                           :)
(:Date: June 3, 2005                                     :)
(:Purpose: Evaluates The "op:time-equal" operator (ge)   :)
(: with the arguments set as follows:                    :)
(:$arg1 = xs:time(lower bound)                           :)
(:$arg2 = xs:time(upper bound)                           :)
(:*******************************************************:)

xs:time("00:00:00Z") ge xs:time("23:59:59Z")