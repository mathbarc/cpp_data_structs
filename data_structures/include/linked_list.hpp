#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
template <typename Type> class LinkedList
{
  private:
    class Node
    {
      public:
        Type value;
        Node *next;
    };

    Node *head;
    size_t n_elements;

  public:
    class iterator
    {
      private:
        Node *current;

      public:
        iterator(Node *pointer) : current(pointer)
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

        Type operator*()
        {
            return this->current->value;
        }
    };

    LinkedList() : head(nullptr), n_elements(0)
    {
    }

    void insert(const Type &value)
    {
        Node *newNode = new Node{value, head};
        this->head = newNode;
        ++this->n_elements;
    }

    Type remove()
    {
        if(this->head == nullptr)
            throw std::runtime_error("It is not possible to remove elements from empty lists");
        Type value = this->head->value;
        Node *toRemove = this->head;
        this->head = this->head->next;
        delete toRemove;
        --this->n_elements;
        return value;
    }

    iterator begin()
    {
        return iterator(head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    size_t size()
    {
        return this->n_elements;
    }
};

#endif // !LINKED_LIST_HPP
