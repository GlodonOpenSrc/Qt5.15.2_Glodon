(:*******************************************************:)
(: Test: K2-AnyURILeGe-9                                 :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Invoked 'gt' on xs:anyURI values.            :)
(:*******************************************************:)
xs:string("http://example.com/B") gt xs:anyURI("http://example.com/A")