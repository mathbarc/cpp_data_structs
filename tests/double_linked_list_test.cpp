#include "double_linked_list.hpp"
#include <cassert>
#include <iostream>

template <typename List> void print(List &list)
{
    for(auto v : list)
    {
        std::cout << v << std::endl;
    }
}

int main(int argc, char **argv)
{

    DoubleLinkedList<int> list;

    list.insertOnHead(10);
    list.insertOnHead(20);
    list.insertOnHead(30);
    list.insertOnHead(40);

    assert(list.size() == 4);

    int v = 10;
    for(int i : list)
    {
        assert(i == v);
        v += 10;
        std::cout << i << std::endl;
    }

    list.removeFromTail();
    assert(list.size() == 3);

    std::cout << std::endl;
    print(list);
    std::cout << std::endl;

    for(int &i : list)
    {
        i += 10;
    }

    print(list);

    return 0;
}
