--TEST--
LinkedList: Test $linkedList->toArray()
--FILE--
<?php

$linkedList = new SPL\Datastructures\LinkedList;
var_dump($linkedList->toArray());

$linkedList->push('x');
$linkedList->push(array(42));
$linkedList->push(new stdClass);

var_dump($linkedList->toArray());

?>
--EXPECT--
array(0) {
}
array(3) {
  [0]=>
  string(1) "x"
  [1]=>
  array(1) {
    [0]=>
    int(42)
  }
  [2]=>
  object(stdClass)#2 (0) {
  }
}
