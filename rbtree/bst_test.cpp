
#include <iostream>
#include <vector>
#include "BinarySearchTree.h"
#include <random>
#include "TreeUtils.h"

int main()
{
    using BST = daniel::BinarySearchTree<int>;

    BST tree;

    // get 1000 random numbers
    std::vector<int> numbers;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);
    for (int i = 0; i < 100; ++i)
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
}