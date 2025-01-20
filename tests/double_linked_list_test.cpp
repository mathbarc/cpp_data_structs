#include "double_linked_list.hpp"
#include <cassert>

int main(int argc, char **argv)
{
    DoubleLinkedList<int> list;

    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);

    assert(list.size() == 4);

    int v = 10;
    for(int i : list)
    {
        assert(i == v);
        v += 10;
    }

    list.remove();

    assert(list.size() == 3);

    return 0;
}
