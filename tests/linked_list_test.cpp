#include "linked_list.hpp"
#include <cassert>
#include <iostream>

int main(int argc, char **argv)
{
    LinkedList<int> list;

    list.insert(10);
    list.insert(20);
    list.insert(30);
    list.insert(40);

    int v = 50;
    list.insert(v);

    assert(list.size() == 5);
    for(auto v : list)
    {
        std::cout << v << std::endl;
    }

    while(list.size())
    {
        list.remove();
    }

    assert(list.size() == 0);

    return 0;
}
