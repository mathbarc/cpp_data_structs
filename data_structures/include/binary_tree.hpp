#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "double_linked_list.hpp"
#include "linked_list.hpp"
#include <iostream>
#include <stdexcept>
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

    void remove(Node *toDelete, Node *parent)
    {
        Node *y = toDelete;
        if(toDelete->left != nullptr && toDelete->right != nullptr)
        {
            Node *py = y;
            y = y->right;
            while(y->left != nullptr)
            {
                py = y;
                y = y->left;
            }
            if(y != toDelete)
            {
                toDelete->value = y->value;
                toDelete = y;
                parent = py;
            }
        }

        if(parent != nullptr)
        {
            if(parent->left == toDelete)
                parent->left = toDelete->left;
            if(parent->right == toDelete)
                parent->right = toDelete->right;
        }
        delete toDelete;
    }

    void remove(const Type &value)
    {
        Node *toDelete = this->root;
        Node *parent = nullptr;
        while(toDelete != nullptr)
        {
            if(value == toDelete->value)
                break;
            parent = toDelete;
            if(value < toDelete->value)
                toDelete = toDelete->left;
            else if(value > toDelete->value)
                toDelete = toDelete->right;
        }

        if(toDelete == nullptr)
            throw std::runtime_error("Value not found on tree");

        this->remove(toDelete, parent);
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

    void preOrder()
    {
        LinkedList<Node *> visited;

        visited.insert(this->root);
        while(visited.size())
        {
            Node *current = visited.remove();
            std::cout << current->value << " ";
            if(current->right != nullptr)
                visited.insert(current->right);
            if(current->left != nullptr)
                visited.insert(current->left);
        }
        std::cout << std::endl;
    }

    void postOrder()
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
                visited.insert(std::make_pair(current.first, true));
                if(current.first->right != nullptr)
                    visited.insert(std::make_pair(current.first->right, false));
                if(current.first->left != nullptr)
                    visited.insert(std::make_pair(current.first->left, false));
            }
        }
        std::cout << std::endl;
    }

    size_t height()
    {
        if(this->root == nullptr)
            return 0;
        LinkedList<std::pair<Node *, size_t>> visited;
        size_t highest_height = 0;

        visited.insert(std::make_pair(this->root, 1));

        while(visited.size())
        {
            std::pair<Node *, size_t> current = visited.remove();

            if(highest_height < current.second)
                highest_height = current.second;

            if(current.first->left != nullptr)
                visited.insert(std::make_pair(current.first->left, current.second + 1));
            if(current.first->right != nullptr)
                visited.insert(std::make_pair(current.first->right, current.second + 1));
        }
        return highest_height;
    }

    void balance();
};

#endif
