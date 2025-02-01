#ifndef DOUBLE_LINKED_LIST_HPP
#define DOUBLE_LINKED_LIST_HPP

#include <stdexcept>
template <typename Type> class DoubleLinkedList
{
  private:
    class Node
    {
      public:
        Type value;
        Node *next;
    };

    Node *head;
    Node *tail;
    size_t n_elements;

  public:
    class iterator
    {
      private:
        Node *current;

      public:
        iterator(Node *node) : current(node)
        {
        }

        iterator &operator++()
        {
            if(this->current != nullptr)
                this->current = this->current->next;
            return *this;
        }

        bool operator==(iterator other)
        {
            return this->current == other.current;
        }

        bool operator!=(iterator other)
        {
            return !(*this == other);
        }

        Type &operator*()
        {
            return this->current->value;
        }
    };

    DoubleLinkedList() : head(nullptr), tail(nullptr), n_elements(0)
    {
    }

    iterator begin()
    {
        return iterator(this->head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    void insertOnHead(const Type &value)
    {
        Node *newNode = new Node{value, nullptr};
        if(this->head != nullptr)
        {
            this->tail->next = newNode;
            this->tail = newNode;
        }
        else
        {
            this->tail = this->head = newNode;
        }
        ++this->n_elements;
    }

    Type removeFromTail()
    {
        if(this->head == nullptr)
            throw std::runtime_error("It is impossible to remove elements from empty list");

        Node *toDelete = this->head;
        this->head = this->head->next;
        --this->n_elements;
        Type value = toDelete->value;
        delete toDelete;
        return value;
    }

    size_t size()
    {
        return this->n_elements;
    }
};

#endif
