--TEST--
Queue: Test $queue->toArray()
--FILE--
<?php

$queue = new SPL\Datastructures\Queue;
var_dump($queue->toArray());

$queue->push('x');
$queue->push(array(42));
$queue->push(new stdClass);

var_dump($queue->toArray());

?>
--EXPECT--
array(0) {
}
array(3) {
  [0]=>
  string(1) "x"
  [1]=>
  array(1) {
    [0]=>
    int(42)
  }
  [2]=>
  object(stdClass)#2 (0) {
  }
}
