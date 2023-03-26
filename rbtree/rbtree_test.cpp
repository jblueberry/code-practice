#include "RedBlackTree.h"
#include <iostream>
#include <vector>
#include <random>
#include "TreeUtils.h"

int main()
{
    using RBTree = daniel::RedBlackTree<int>;

    RBTree tree;

    std::vector<int> values = {55, 93, 51, 28, 41, 65, 76, 85, 91, 45};
    for (auto value : values)
        tree.Insert(value);

    // Print the tree
    auto print = [](int &value, bool color)
    {
        auto color_str = color ? "R" : "B";
        std::cout << value << color_str << "\n";
    };
    tree.PostOrderTraverse<decltype(print), true>(print);

    return 0;
}