--TEST--
Stack: Test $stack->push(), $stack->pop() and $stack->peek()
--FILE--
<?php

$stack = new SPL\Datastructures\Stack;

$stack->push('x');
$stack->push(array(42));
$stack->push(new stdClass);

var_dump($stack->peek());
var_dump($stack->pop());

var_dump($stack->peek());
var_dump($stack->pop());

var_dump($stack->peek());
var_dump($stack->pop());

?>
--EXPECT--
object(stdClass)#2 (0) {
}
object(stdClass)#2 (0) {
}
array(1) {
  [0]=>
  int(42)
}
array(1) {
  [0]=>
  int(42)
}
string(1) "x"
string(1) "x"
