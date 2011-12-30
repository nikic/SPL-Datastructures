--TEST--
Stack: Test count($stack), $stack->count(), $stack->isEmpty() and Countable interface
--FILE--
<?php

$stack = new SPL\Datastructures\Stack;
var_dump($stack instanceof Countable);
var_dump($stack->count());
var_dump($stack->isEmpty());
var_dump(count($stack));

$stack->push('x');
var_dump($stack->isEmpty());
var_dump(count($stack));

$stack->push('y');
var_dump(count($stack));

$stack->pop();
var_dump(count($stack));

$stack->pop();
var_dump($stack->isEmpty());
var_dump(count($stack));

?>
--EXPECT--
bool(true)
int(0)
bool(true)
int(0)
bool(false)
int(1)
int(2)
int(1)
bool(true)
int(0)
