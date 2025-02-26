#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "linked_list.hpp"
#include <iostream>
#include <utility>

template <typename Type> class BinaryTree
{
  private:
    struct Node
    {
        Node *left;
        Node *right;
        Type value;
        Node(Type value) : value(value), left(nullptr), right(nullptr)
        {
        }
    };

    Node *root;

  public:
    BinaryTree() : root(nullptr)
    {
    }

    void insert(const Type &value)
    {
        Node *node = new Node(value);
        if(this->root == nullptr)
        {
            this->root = node;
        }
        else
        {
            Node *current = this->root;
            Node *last;
            while(current != nullptr)
            {
                last = current;
                if(value < current->value)
                    current = current->left;
                else
                    current = current->right;
            }

            if(value < last->value)
                last->left = node;
            else
                last->right = node;
        }
    }

    void inOrder()
    {
        LinkedList<std::pair<Node *, bool>> visited;

        visited.insert(std::make_pair(this->root, false));
        while(visited.size())
        {
            std::pair<Node *, bool> current = visited.remove();
            if(current.second)
            {
                std::cout << current.first->value << " ";
            }
            else
            {
                if(current.first->right != nullptr)
                    visited.insert(std::make_pair(current.first->right, false));
                visited.insert(std::make_pair(current.first, true));
                if(current.first->left != nullptr)
                    visited.insert(std::make_pair(current.first->left, false));
            }
        }
        std::cout << std::endl;
    }

    void preOrder();
    void postOrder();
    size_t height();

    void balance();
};

#endif
