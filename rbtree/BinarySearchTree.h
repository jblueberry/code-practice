#pragma once
#include "BinaryTree.h"
#include <cassert>
#include <iostream>

namespace daniel
{
    template <typename T>
    class BinarySearchTree : public BinaryTree<T>
    {
        using Node = typename BinaryTree<T>::Node;
        using Pointer = typename BinaryTree<T>::NodePointer;

        using BinaryTree<T>::root;

        size_t size = 0;

        Pointer Find(T value) const
        {
            auto pos = root;
            while (pos != nullptr)
            {
                if (value < pos->value)
                    pos = pos->left;
                else if (value > pos->value)
                    pos = pos->right;
                else
                    return pos;
            }
            return nullptr;
        }

        bool IsLeaf(auto node) const
        {
            return node->left == nullptr && node->right == nullptr;
        }

        bool IsLeftChild(auto node) const
        {
            return node->parent->left == node;
        }

    public:
        BinarySearchTree() = default;

        bool Insert(T value) override
        {
            Pointer parent = nullptr;
            auto pos = root;
            while (pos != nullptr)
            {
                parent = pos;
                if (value < pos->value)
                    pos = pos->left;
                else if (value > pos->value)
                    pos = pos->right;
                else
                    return false;
            }
            assert(pos == nullptr);

            auto newNode = std::make_shared<Node>(value, nullptr, nullptr, parent);

            if (parent == nullptr)
                root = newNode;
            else if (value < parent->value)
                parent->left = newNode;
            else
                parent->right = newNode;
            ++size;
            return true;
        }

        bool Remove(const T & value) override
        {
            auto pos = Find(value);
            if (pos == nullptr)
                return false;

            if (IsLeaf(pos))
            {
                if (IsLeftChild(pos))
                    pos->parent->left = nullptr;
                else
                    pos->parent->right = nullptr;
            }

            --size;
            return true;
        }

        size_t Size() const override
        {
            return size;
        }

        bool Contains(const T &value) const override
        {
            auto pos = root;
            while (pos != nullptr)
            {
                if (value < pos->value)
                    pos = pos->left;
                else if (value > pos->value)
                    pos = pos->right;
                else
                    return true;
            }
            return false;
        }

        bool Empty() const override
        {
            return root == nullptr;
        }
    };
}