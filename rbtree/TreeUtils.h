#pragma once
#include <concepts>
#include "BinaryTree.h"

namespace daniel
{
    template <typename T>
    bool CheckBST(const BinaryTree<T> &tree)
    {
        std::vector<T> inorder;
        tree.InOrderTraverse([&](auto value)
                             { inorder.push_back(value); });

        for (size_t i = 1; i < inorder.size(); ++i)
        {
            if (inorder[i - 1] > inorder[i])
                return false;
        }
        return true;
    }
}