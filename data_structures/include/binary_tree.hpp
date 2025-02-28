#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "double_linked_list.hpp"
#include "linked_list.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

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

    void inOrderRetrieve(std::vector<Node *> &nodeArray, Node *rootNode)
    {
        LinkedList<std::pair<Node *, bool>> visited;

        visited.insert(std::make_pair(rootNode, false));
        while(visited.size())
        {
            std::pair<Node *, bool> current = visited.remove();
            if(current.second)
            {
                nodeArray.push_back(current.first);
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
    }

    void preOrderRetrieve(std::vector<Node *> &nodeArray, Node *rootNode)
    {
        LinkedList<Node *> visited;

        visited.insert(rootNode);
        Node *current;
        while(visited.size())
        {
            current = visited.remove();
            nodeArray.push_back(current);
            if(current->right != nullptr)
                visited.insert(current->right);
            if(current->left != nullptr)
                visited.insert(current->left);
        }
    }

    void postOrderRetrieve(std::vector<Node *> &nodeArray, Node *rootNode)
    {
        LinkedList<std::pair<Node *, bool>> visited;

        visited.insert(std::make_pair(rootNode, false));
        while(visited.size())
        {
            std::pair<Node *, bool> current = visited.remove();
            if(current.second)
            {
                nodeArray.push_back(current.first);
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
    }

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

    void inOrderPrint()
    {
        std::vector<Node *> nodes;
        this->inOrderRetrieve(nodes, this->root);

        for(Node *node : nodes)
        {
            std::cout << node->value << " ";
        }
        std::cout << std::endl;
    }

    void preOrderPrint()
    {
        std::vector<Node *> nodes;
        this->preOrderRetrieve(nodes, this->root);

        for(Node *node : nodes)
        {
            std::cout << node->value << " ";
        }

        std::cout << std::endl;
    }

    void postOrderPrint()
    {
        std::vector<Node *> nodes;
        this->postOrderRetrieve(nodes, this->root);

        for(Node *node : nodes)
        {
            std::cout << node->value << " ";
        }

        std::cout << std::endl;
    }

    size_t height()
    {
        if(this->root == nullptr)
            return 0;

        size_t height = 0;

        LinkedList<Node *> visited;
        visited.insert(this->root);

        while(visited.size())
        {

            size_t levelSize = visited.size();
            height++;

            for(size_t i = 0; i < levelSize; i++)
            {
                Node *current = visited.remove();

                if(current->left != nullptr)
                    visited.insert(current->left);
                if(current->right != nullptr)
                    visited.insert(current->right);
            }
        }
        return height;
    }

    void balance()
    {
        std::vector<Node *> nodes;
        this->inOrderRetrieve(nodes, this->root);
    }
};

#endif
