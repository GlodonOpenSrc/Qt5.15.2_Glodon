(:*******************************************************:)
(:Test: op-multiply-yearMonthDuration-2                  :)
(:Written By: Carmelo Montanez                           :)
(:Date: June 30, 2005                                    :)
(:Purpose: Evaluates The "multiply-yearMonthDuration" function :)
(:used as part of a boolean expression (and operator) and the "fn:false" function. :)
(: Apply "fn:string" function to account for new EBV.     :)
(:*******************************************************:)

fn:string((xs:yearMonthDuration("P10Y11M")) * 2.0) and fn:false()