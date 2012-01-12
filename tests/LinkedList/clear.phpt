--TEST--
LinkedList: Test $linkedList->clear()
--FILE--
<?php

$linkedList = new SPL\Datastructures\LinkedList;

$linkedList->push('x');
$linkedList->push('y');
$linkedList->push('z');
var_dump(count($linkedList));

$linkedList->clear();
var_dump(count($linkedList));

?>
--EXPECT--
int(3)
int(0)
