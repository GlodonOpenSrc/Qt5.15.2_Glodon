(:*******************************************************:) 
(: Test: fn-intersect-node-args-015.xq          :) 
(: Written By: Ravindranath Chennoju                             :) 
(: Date: Tue Jun 14 03:34:54 2005                        :) 
(: Purpose: arg: node and node                     :) 
(:*******************************************************:) 
 
(: insert-start :) 
declare namespace atomic="http://www.w3.org/XQueryTest";
declare variable $input-context external;
(: insert-end :) 
 
($input-context/atomic:root/atomic:integer) intersect ($input-context/atomic:root/atomic:integer) 
