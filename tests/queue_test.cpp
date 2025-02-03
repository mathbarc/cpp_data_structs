#include "queue.hpp"
#include <cassert>
#include <iostream>

int main(int argc, char **argv)
{
    Queue<int> queue;

    queue.enqueue(10);
    queue.enqueue(20);

    assert(queue.size() == 2);

    assert(queue.front() == 10);
    assert(queue.dequeue() == 10);
    assert(queue.dequeue() == 20);

    assert(queue.size() == 0);

    return 0;
}
