(:*******************************************************:)
(: Test: K2-BaseURIFunc-31                               :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Compute the base URI from a processing instruction. :)
(:*******************************************************:)
fn:base-uri(exactly-one(<anElement xml:base="http://example.com/examples"><?target data?></anElement>/processing-instruction()))