(:*******************************************************:)
(:Test: distinct-duration-equal-1.xq                     :)
(:Written By: Carmelo Montanez                           :)
(:Date: March 20, 2006                                   :)
(:Purpose: Evaluates The "yearMonthDuration" and         :)
(:"dayTimeDuration" data types with fn:distinct function :)
(: given on example.                                     :)
(:*******************************************************:)

fn:distinct-values((xs:yearMonthDuration('P0Y'), xs:dayTimeDuration('P0D')))