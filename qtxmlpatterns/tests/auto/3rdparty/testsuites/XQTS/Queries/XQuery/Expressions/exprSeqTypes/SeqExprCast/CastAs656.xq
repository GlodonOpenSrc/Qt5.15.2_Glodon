(:*******************************************************:)
(:Test: CastAs656                                        :)
(:Written By: Carmelo Montanez                           :)
(:Date: July 10, 2006                                    :)
(:Purpose: Evaluates casting a string into an xs:unsignedInt :)
(:*******************************************************:)

(: insert-start :)
declare variable $input-context external;
(: insert-end :)

xs:string(300) cast as xs:unsignedInt