--TEST--
LinkedList: Test operations on head/tail (getFirst, getLast, push, pop, shift, unshift)
--FILE--
<?php

$linkedList = new SPL\Datastructures\LinkedList;

$linkedList->push('c');
$linkedList->push('d');

$linkedList->unshift('b');
$linkedList->unshift('a');

var_dump($linkedList->getFirst());
var_dump($linkedList->shift());
var_dump($linkedList->getLast());
var_dump($linkedList->pop());

var_dump($linkedList->getFirst());
var_dump($linkedList->shift());
var_dump($linkedList->getLast());
var_dump($linkedList->pop());

?>
--EXPECT--
string(1) "a"
string(1) "a"
string(1) "d"
string(1) "d"
string(1) "b"
string(1) "b"
string(1) "c"
string(1) "c"
