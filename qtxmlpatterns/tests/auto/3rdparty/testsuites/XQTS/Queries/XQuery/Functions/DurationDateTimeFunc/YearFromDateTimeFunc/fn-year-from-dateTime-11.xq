(:*******************************************************:)
(:Test: year-from-dateTime-11                            :)
(:Written By: Carmelo Montanez                           :)
(:Date: June 8, 2005                                     :)
(:Purpose: Evaluates The "year-from-dateTime" function   :)
(:as part of a "div" expression.                         :) 
(:*******************************************************:)

fn:year-from-dateTime(xs:dateTime("1000-01-01T02:00:00Z")) div fn:year-from-dateTime(xs:dateTime("0050-01-01T10:00:00Z"))
