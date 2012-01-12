--TEST--
LinkedList: Test clone $linkedList
--FILE--
<?php

$linkedList = new SPL\Datastructures\LinkedList;
$linkedList->push('x');
$linkedList->push('y');

$clone = clone $linkedList;
$clone->pop();

var_dump($linkedList->toArray());
var_dump($clone->toArray());

?>
--EXPECT--
array(2) {
  [0]=>
  string(1) "x"
  [1]=>
  string(1) "y"
}
array(1) {
  [0]=>
  string(1) "x"
}
