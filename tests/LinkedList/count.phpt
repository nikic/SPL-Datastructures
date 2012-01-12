--TEST--
LinkedList: Test count($linkedList), $linkedList->count(), $linkedList->isEmpty() and Countable interface
--FILE--
<?php

$linkedList = new SPL\Datastructures\LinkedList;
var_dump($linkedList instanceof Countable);
var_dump($linkedList->count());
var_dump($linkedList->isEmpty());
var_dump(count($linkedList));

$linkedList->push('x');
var_dump($linkedList->isEmpty());
var_dump(count($linkedList));

$linkedList->push('y');
var_dump(count($linkedList));

$linkedList->pop();
var_dump(count($linkedList));

$linkedList->pop();
var_dump($linkedList->isEmpty());
var_dump(count($linkedList));

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
