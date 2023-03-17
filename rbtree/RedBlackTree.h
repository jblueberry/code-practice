#pragma once
#include <concepts>
#include "BinaryTree.h"

namespace daniel
{
    template <std::totally_ordered T>
    class RedBlackTree : public BinaryTree<T>
    {
        struct Node : public BinaryTree<T>::Node
        {
            using Pointer = std::shared_ptr<Node>;
            bool isRed = true;
        };

        using Pointer = typename Node::Pointer;
        using BinaryTree<T>::root;
        size_t size = 0;

        bool IsLeftChild(auto node) const
        {
            return node->parent->left == node;
        }

        Pointer ParentOf(auto node) const
        {
            return node->parent;
        }

        Pointer GrandparentOf(auto node) const
        {
            return ParentOf(node)->parent;
        }

        Pointer UncleOf(auto node) const
        {
            auto parent = ParentOf(node);
            if (IsLeftChild(parent))
                return GrandparentOf(node)->right;
            else
                return GrandparentOf(node)->left;
        }

        void InsertCase1(auto node)
        {
            if (ParentOf(node) == nullptr)
                node->isRed = false;
            else
                InsertCase2(node);
        }

        void InsertCase2(auto node)
        {
            if (ParentOf(node)->isRed == false)
                return;
            else
                InsertCase3(node);
        }

        void InsertCase3(auto node)
        {
            auto uncle = UncleOf(node);
            auto parent = ParentOf(node);
            auto grandparent = GrandparentOf(node);
            if (uncle != nullptr && uncle->isRed)
            {
                parent->isRed = false;
                uncle->isRed = false;
                grandparent->isRed = true;
                InsertCase1(grandparent);
            }
            else
                InsertCase4(node);
        }

        void InsertCase4(auto node)
        {
            auto parent = ParentOf(node);
            auto grandparent = GrandparentOf(node);
            if (IsLeftChild(node) && !IsLeftChild(parent))
            {
                RotateLeft(parent);
                node = parent;
                parent = ParentOf(node);
            }
            else if (!IsLeftChild(node) && IsLeftChild(parent))
            {
                RotateRight(parent);
                node = parent;
                parent = ParentOf(node);
            }
            InsertCase5(node);
        }

        void InsertCase5(auto node)
        {
            auto parent = ParentOf(node);
            auto grandparent = GrandparentOf(node);
            parent->isRed = false;
            grandparent->isRed = true;
            if (IsLeftChild(node))
                RotateRight(grandparent);
            else
                RotateLeft(grandparent);
        }

    public:
        RedBlackTree() = default;
        ~RedBlackTree() = default;

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

            auto newNode = std::make_shared<Node>(value, nullptr, nullptr, parent, true);
            if (parent == nullptr)
                root = newNode;
            else if (value < parent->value)
                parent->left = newNode;
            else
                parent->right = newNode;
            ++size;
            InsertCase1(newNode);
            return true;
        }
    };

}