--TEST--
Stack: Test $stack->toArray()
--FILE--
<?php

$stack = new SPL\Datastructures\Stack;
var_dump($stack->toArray());

$stack->push('x');
$stack->push(array(42));
$stack->push(new stdClass);

var_dump($stack->toArray());

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
