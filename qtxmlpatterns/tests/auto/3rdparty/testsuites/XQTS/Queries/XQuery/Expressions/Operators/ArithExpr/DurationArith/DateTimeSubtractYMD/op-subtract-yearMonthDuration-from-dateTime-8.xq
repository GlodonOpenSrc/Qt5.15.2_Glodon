(:*******************************************************:)
(:Test: op-subtract-yearMonthDuration-from-dateTime-8    :)
(:Written By: Carmelo Montanez                           :)
(:date: July 8, 2005                                     :)
(:Purpose: Evaluates The "subtract-yearMonthDuration-from-dateTime" operator that  :)
(:returns a negative value.                              :)
(:*******************************************************:)
 
(xs:dateTime("0001-01-01T01:01:01Z") - xs:yearMonthDuration("-P20Y07M"))