--TEST--
Queue: Test iteration
--FILE--
<?php

$queue = new SPL\Datastructures\Queue;
var_dump($queue instanceof Traversable);

$queue->push('x');
$queue->push('y');
$queue->push('z');

foreach ($queue as $index => $item) {
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
