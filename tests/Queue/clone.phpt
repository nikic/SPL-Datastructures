--TEST--
Queue: Test clone $queue
--FILE--
<?php

$queue = new SPL\Datastructures\Queue;
$queue->push('x');
$queue->push('y');

$clone = clone $queue;
$clone->pop();

var_dump($queue->toArray());
var_dump($clone->toArray());

?>
--EXPECT--
array(2) {
  [0]=>
  string(1) "x"
  [1]=>
  string(1) "y"
}
array(1) {
  [0]=>
  string(1) "y"
}
