--TEST--
Queue: Test $queue->push(), $queue->pop() and $queue->peek()
--FILE--
<?php

$queue = new SPL\Datastructures\Queue;

$queue->push('x');
$queue->push(array(42));
$queue->push(new stdClass);

var_dump($queue->peek());
var_dump($queue->pop());

var_dump($queue->peek());
var_dump($queue->pop());

var_dump($queue->peek());
var_dump($queue->pop());

?>
--EXPECT--
string(1) "x"
string(1) "x"
array(1) {
  [0]=>
  int(42)
}
array(1) {
  [0]=>
  int(42)
}
object(stdClass)#2 (0) {
}
object(stdClass)#2 (0) {
}
