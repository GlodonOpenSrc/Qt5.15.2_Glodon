(: Name: ReturnExpr018 :)
(: Description: Apply comparison operator inside 'return' statement :)

(: insert-start :)
declare variable $input-context external;
(: insert-end :)

for $file in ($input-context//Folder)[1]/File
return ($file/Stream/StreamSize)[1] > 1004