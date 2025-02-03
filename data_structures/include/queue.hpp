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

    virtual void enqueue(const Type &value)
    {
        this->list.insertOnHead(value);
    }

    virtual Type dequeue()
    {
        return this->list.removeFromTail();
    }

    virtual const Type &front()
    {
        if(this->list.size())
            return this->list.head->value;
        else
            throw std::runtime_error("Empty queue does not contain first element");
    }

    virtual size_t size()
    {
        return this->list.size();
    }
};

#endif
