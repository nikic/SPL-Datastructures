--TEST--
Queue: UnderflowException on $queue->peek() and $queue->pop() for empty queue
--FILE--
<?php

$queue = new SPL\Datastructures\Queue;

try {
    $queue->peek();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

try {
    $queue->pop();
} catch (UnderflowException $e) {
    var_dump($e->getMessage());
}

?>
--EXPECT--
string(25) "Can't peek an empty queue"
string(24) "Can't pop an empty queue"
