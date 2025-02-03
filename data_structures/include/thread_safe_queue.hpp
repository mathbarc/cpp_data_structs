#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#include "double_linked_list.hpp"
#include "queue.hpp"
#include <mutex>

template <typename Type> class ThreadSafeQueue : public Queue
{
  private:
    std::mutex mutex;

  public:
    ThreadSafeQueue()
    {
    }

    void enqueue(const Type &value)
    {
        this->mutex.lock();
        Queue<Type>::enqueue(value);
        this->mutex.unlock();
    }

    Type dequeue()
    {
        this->mutex.lock();
        Type value = Queue<Type>::dequeue();
        this->mutex.unlock();
        return value;
    }

    const Type &front()
    {
        this->mutex.lock();
        const Type &value = Queue<Type>::front();
        this->mutex.unlock();
        return value;
    }

    size_t size()
    {
        this->mutex.lock();
        size_t n_elem = Queue<Type>::size();
        this->mutex.unlock();
        return n_elem;
    }
};

#endif // !THREAD_SAFE_QUEUE
