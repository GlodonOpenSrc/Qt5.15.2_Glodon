(:*******************************************************:)
(: Test: K-EscapeHTMLURIFunc-6                           :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:22+01:00                       :)
(: Purpose: Invoke fn:normalize-space() on the return value of fn:escape-html-uri(). :)
(:*******************************************************:)
normalize-space(iri-to-uri(("example.com", current-time())[1] treat as xs:string))