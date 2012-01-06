--TEST--
Queue: Test $queue->clear()
--FILE--
<?php

$queue = new SPL\Datastructures\Queue;

$queue->push('x');
$queue->push('y');
$queue->push('z');
var_dump(count($queue));

$queue->clear();
var_dump(count($queue));

?>
--EXPECT--
int(3)
int(0)
