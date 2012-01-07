--TEST--
Stack: UnderflowException on $stack->peek() and $stack->pop() for empty stack
--FILE--
<?php

$stack = new SPL\Datastructures\Stack;

try {
    $stack->peek();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

try {
    $stack->pop();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

?>
--EXPECT--
string(25) "Can't peek an empty stack"
string(24) "Can't pop an empty stack"
