declare default element namespace "http://www.w3.org/XQueryTestOrderBy";
(: name : orderBy59 :)
(: description : Evaluation of "order by" clause with the "order by" clause of a FLWR expression set to "string($x) ", where $x is a set of small negative numbers and the ordering mode set to ascending :)

(: insert-start :)
declare variable $input-context1 external;
(: insert-end :)

<results> {
for $x in $input-context1/DataValues/SmallNegativeNumbers/orderData
 order by string($x) ascending return string($x)
}
</results>
