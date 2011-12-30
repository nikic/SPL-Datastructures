--TEST--
Stack: Test $stack->clear()
--FILE--
<?php

$stack = new SPL\Datastructures\Stack;

$stack->push('x');
$stack->push('y');
$stack->push('z');
var_dump(count($stack));

$stack->clear();
var_dump(count($stack));

?>
--EXPECT--
int(3)
int(0)
