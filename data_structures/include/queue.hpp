#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "double_linked_list.hpp"

template <typename Type> class Queue
{
  private:
    DoubleLinkedList<Type> list;

  public:
    Queue() : list()
    {
    }

    void enqueue(const Type &value)
    {
        this->list.insert(value);
    }

    Type enqueue()
    {
        return this->list.remove();
    }
};

#endif
