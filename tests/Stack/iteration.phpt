--TEST--
Stack: Test iteration
--FILE--
<?php

$stack = new SPL\Datastructures\Stack;
var_dump($stack instanceof Traversable);

$stack->push('x');
$stack->push('y');
$stack->push('z');

foreach ($stack as $index => $item) {
    var_dump($index, $item);
}

?>
--EXPECT--
bool(true)
int(0)
string(1) "x"
int(1)
string(1) "y"
int(2)
string(1) "z"
