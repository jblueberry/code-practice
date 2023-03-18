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
    using RBTree = daniel::RedBlackTree<int>;
    RBTree tree;

    // get 1000 random numbers
    std::vector<int> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10000);
    for (int i = 0; i < 1000; ++i)
    {
        numbers.push_back(dis(gen));
    }

    // insert them into the tree
    std::cout << "Inserting: ";
    for (auto n : numbers)
    {
        std::cout << n << ", ";
    }
    std::cout << std::endl;

    for (auto n : numbers)
    {
        tree.Insert(n);
    }

    // print size
    std::cout << "size: " << tree.Size() << std::endl;
    // pre-order traverse the tree
    std::cout << "pre-order traverse: ";
    tree.PreOrderTraverse([](auto n)
                          { std::cout << n << ", "; });
    std::cout << std::endl;

    if (daniel::CheckBST(tree))
    {
        std::cout << "This is a BST" << std::endl;
    }
    else
    {
        std::cout << "This is not a BST" << std::endl;
    }

    daniel::OrderedMap<int, std::string> map;
    map.Put(1, "1");
    map.Put(2, "3");

    std::cout << map.Get(1) << std::endl;
    std::cout << map.Get(2) << std::endl;

    map.Put(1, "hello world");
    std::cout << map.Get(1) << std::endl;


    daniel::OrderedMap<NonOrderable, int> map2;
}