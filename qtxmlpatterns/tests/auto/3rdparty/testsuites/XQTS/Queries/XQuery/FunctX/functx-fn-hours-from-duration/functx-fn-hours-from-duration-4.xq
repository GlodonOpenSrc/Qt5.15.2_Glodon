(:**************************************************************:)
(: Test: functx-fn-hours-from-duration-4                                  :)
(: Written by: Priscilla Walmsley (Frans Englich is maintainer) :)
(: Date: 2008-05-16+02:00                                       :)
(:**************************************************************:)

declare namespace functx = "http://www.example.com/";
(hours-from-duration(
   xs:dayTimeDuration('PT2H59M')))
