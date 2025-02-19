#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <stdexcept>
#include <vector>

template <typename Type> class CircularBuffer
{
  private:
    std::vector<Type> buffer;
    std::size_t head, tail;
    std::size_t maxCapacity;
    std::size_t n_elements;

    size_t translateIndex(size_t index)
    {
        return index % this->maxCapacity;
    }

  public:
    CircularBuffer(std::size_t capacity) : buffer(capacity), maxCapacity(capacity), head(0), tail(0), n_elements(0)
    {
    }

    ~CircularBuffer()
    {
    }

    void push(Type value)
    {
        if(this->isFull())
        {
            this->head = translateIndex(this->head + 1);
        }
        else
        {
            this->n_elements++;
        }

        this->buffer[this->tail] = value;
        this->tail = translateIndex(this->tail + 1);
    }

    Type pop()
    {
        if(this->isEmpty())
        {
            throw std::runtime_error("It is not possible to pop elements from empty buffer");
        }

        Type item = this->buffer[this->head];
        this->head = translateIndex(this->head + 1);
        this->n_elements--;
        return item;
    }

    Type peek()
    {
        if(this->isEmpty())
            throw std::runtime_error("Can't peek empty buffer");
        return this->buffer[this->head];
    }

    bool isFull()
    {
        return this->n_elements == this->maxCapacity;
    }

    bool isEmpty()
    {
        return !this->n_elements;
    }

    size_t size()
    {
        return this->n_elements;
    }

    size_t capacity()
    {
        return this->maxCapacity;
    }
};

#endif
