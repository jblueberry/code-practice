#include "RedBlackTree.h"
#include <iostream>
#include <vector>
#include <random>
#include "TreeUtils.h"

struct NonOrderable
{
    int value;
};

int main()
{
    using Map = daniel::OrderedMap<int, std::string>;

    Map map;
    map.Put(1, "1");
    map.Put(2, "3");

    std::cout << map.Get(1) << std::endl;
    std::cout << map.Get(2) << std::endl;

    map.Put(1, "hello world");
    std::cout << map.Get(1) << std::endl;

    map.Put(3, "3");
    std::cout << map.Get(3) << std::endl;

    return 0;
}