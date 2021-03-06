(:*******************************************************:)
(:Test: op-add-yearMonthDuration-to-date2args-4           :)
(:Written By: Carmelo Montanez                            :)
(:Date: Tue Apr 12 16:29:08 GMT-05:00 2005                :)
(:Purpose: Evaluates The "op:add-yearMonthDuration-to-date" operator:)
(: with the arguments set as follows:                    :)
(:$arg1 = xs:date(lower bound)                           :)
(:$arg2 = xs:yearMonthDuration(mid range)               :)
(:*******************************************************:)

xs:date("1970-01-01Z") + xs:yearMonthDuration("P1000Y6M")