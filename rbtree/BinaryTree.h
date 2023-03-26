#pragma once
#include <memory>
#include <functional>

namespace daniel
{
    template <typename T>
    class BinaryTree
    {
    protected:
        struct Node
        {
            using Pointer = std::shared_ptr<Node>;
            T value;
            Pointer left;
            Pointer right;
            Pointer parent;
        };
        using NodePointer = typename Node::Pointer;

        NodePointer root = nullptr;

    public:
        virtual bool Insert(T value) = 0;
        virtual bool Remove(const T &) = 0;
        virtual bool Contains(const T& value) const = 0;
        virtual bool Empty() const = 0;
        virtual size_t Size() const = 0;

        virtual ~BinaryTree() = default;

        // TODO: add more constraint with F using concepts
        template <typename F>
        void PreOrderTraverse(F f) const
        {
            std::function<void(NodePointer)> traverse = [&](auto node)
            {
                if (node == nullptr)
                    return;
                f(node->value);
                traverse(node->left);
                traverse(node->right);
            };

            traverse(root);
        }

        template <typename F>
        void InOrderTraverse(F f) const
        {
            std::function<void(NodePointer)> traverse = [&](auto node)
            {
                if (node == nullptr)
                    return;
                traverse(node->left);
                f(node->value);
                traverse(node->right);
            };

            traverse(root);
        }
    };
}