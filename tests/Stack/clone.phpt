--TEST--
Stack: Test clone $stack
--FILE--
<?php

$stack = new SPL\Datastructures\Stack;
$stack->push('x');
$stack->push('y');

$clone = clone $stack;
$clone->pop();

var_dump($stack->toArray());
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
