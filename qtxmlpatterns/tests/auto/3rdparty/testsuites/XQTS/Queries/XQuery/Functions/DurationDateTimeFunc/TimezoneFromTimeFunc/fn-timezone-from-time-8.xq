(:*******************************************************:)
(:Test: fn-timezone-from-time-8                          :)
(:Written By: Carmelo Montanez                           :)
(:Date: June 27, 2005                                    :)
(:Purpose: Evaluates The "timezone-from-time" function   :)
(:as part of a "+" expression.                           :) 
(:*******************************************************:)

fn:timezone-from-time(xs:time("02:00:00Z")) + fn:timezone-from-time(xs:time("10:00:10Z"))
