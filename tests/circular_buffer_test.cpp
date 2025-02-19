#include "circular_buffer.hpp"
#include <cassert>

int main(int argc, char **argv)
{
    CircularBuffer<int> buffer(3);

    buffer.push(0);
    buffer.push(1);
    buffer.push(2);
    buffer.push(3);

    for(int i = 1; i < 4; i++)
    {
        assert(i == buffer.pop());
    }

    assert(buffer.isEmpty());

    buffer.push(0);
    buffer.push(1);
    buffer.push(2);

    assert(buffer.size() == 3);
    assert(buffer.isFull());
    assert(buffer.peek() == 0);

    return 0;
}
