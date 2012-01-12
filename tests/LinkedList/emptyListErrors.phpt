--TEST--
LinkedList: Test UnderflowException on getFirst/getLast/shift/pop on empty linked list
--FILE--
<?php

$linkedList = new SPL\Datastructures\LinkedList;

try {
    $linkedList->getFirst();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

try {
    $linkedList->getLast();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

try {
    $linkedList->shift();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

try {
    $linkedList->pop();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

?>
--EXPECT--
string(47) "Can't get first element of an empty linked list"
string(46) "Can't get last element of an empty linked list"
string(32) "Can't shift an empty linked list"
string(30) "Can't pop an empty linked list"
