(:*******************************************************:)
(: Test: K-DateTimeEQ-8                                  :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Test that zone offset -00:00 is equal to +00:00, in xs:dateTime. :)
(:*******************************************************:)
xs:dateTime("1999-12-04T16:00:12.345-00:00") eq
		xs:dateTime("1999-12-04T16:00:12.345+00:00")