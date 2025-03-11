#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <cstddef>
#include <functional>
#include <vector>

template <typename Key, typename Value> class HashMap
{

  private:
    size_t capacity;
    size_t nElements;

    struct Entry
    {
        Key key;
        Value value;
        bool isOccupied;
        bool isDeleted;
    };

    std::vector<Entry> table;

    const std::hash<Key> hashFunc;

    size_t getIndex(const Key &key) const
    {
        return this->hashFunc(key) % this->capacity;
    }

  public:
    HashMap(size_t initialCapacity = 2) : capacity(initialCapacity), nElements(0), table(initialCapacity)
    {
    }
};

#endif
