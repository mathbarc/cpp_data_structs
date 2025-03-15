#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include <cstddef>
#include <functional>
#include <optional>
#include <stdexcept>
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
    };

    std::vector<Entry> table;

    const std::hash<Key> hashFunc;

    size_t getIndex(const Key &key) const
    {
        return this->hashFunc(key) % this->capacity;
    }

    std::optional<size_t> findKey(const Key &key) const
    {
        size_t index = this->getIndex(key);
        size_t originalIndex = index;

        while(this->table[index].isOccupied)
        {
            if(this->table[index].key == key)
            {
                return index;
            }

            index = (index + 1) % this->capacity;
            if(originalIndex == index)
                return std::nullopt;
        }

        return std::nullopt;
    }

  public:
    HashMap(size_t initialCapacity = 2) : capacity(initialCapacity), nElements(0), table(initialCapacity), hashFunc()
    {
    }

    ~HashMap()
    {
    }

    void remove(const Key &key)
    {
        std::optional<size_t> index = this->findKey(key);
        if(index)
        {
            table[*index].isOccupied = false;
            --this->nElements;
        }
        else
        {
            throw std::runtime_error("key not found");
        }
    }

    bool contains(const Key &key)
    {
        return this->findKey(key).has_value();
    }

    size_t size()
    {
        return this->nElements;
    }

    void insert(const Key &key, const Value &value)
    {
        size_t index = this->getIndex(key);
        size_t attempts = 0;

        while(table[index].isOccupied)
        {
            if(table[index].key == key)
            {
                table[index].value = value;
                return;
            }

            index = (index + 1) % this->capacity;
            attempts++;
            if(attempts == this->capacity)
                throw std::runtime_error("Hash table is full");
        }

        table[index] = {key, value, true};
        ++this->nElements;
    }

    const Value &get(const Key &key) const
    {
        std::optional<size_t> index = this->findKey(key);
        if(index)
            return this->table[*index].value;
        else
            throw std::runtime_error("key not found");
    }
};

#endif
