--TEST--
LinkedList: Test iteration
--FILE--
<?php

$linkedList = new SPL\Datastructures\LinkedList;
var_dump($linkedList instanceof Traversable);

$linkedList->push('x');
$linkedList->push('y');
$linkedList->push('z');

foreach ($linkedList as $index => $item) {
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
