--TEST--
Queue: Test count($queue), $queue->count(), $queue->isEmpty() and Countable interface
--FILE--
<?php

$queue = new SPL\Datastructures\Queue;
var_dump($queue instanceof Countable);
var_dump($queue->count());
var_dump($queue->isEmpty());
var_dump(count($queue));

$queue->push('x');
var_dump($queue->isEmpty());
var_dump(count($queue));

$queue->push('y');
var_dump(count($queue));

$queue->pop();
var_dump(count($queue));

$queue->pop();
var_dump($queue->isEmpty());
var_dump(count($queue));

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
