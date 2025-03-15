#include "hash_map.hpp"
#include <cassert>
#include <iostream>

int main(int argc, char **argv)
{
    HashMap<std::string, int> map;

    map.insert("matheus", 10);

    assert(map.get("matheus") == 10);

    map.insert("marcelo", 100);

    assert(map.size() == 2);

    map.remove("matheus");

    assert(map.size() == 1);

    return 0;
}
