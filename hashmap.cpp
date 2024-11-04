#include "hashmap.hpp"
#include <optional>

template<typename K, typename V>
HashMap<K, V>::HashMap(size_t initial_capacity = 16, float load_factor = 0.75) :
    capacity(initial_capacity), load_factor(load_factor), size(0)
{
    table.resize(capacity);
}

template<typename K, typename V>
size_t HashMap<K, V>::hash(const K& key) const
{
    return std::hash<K>{}(key) % capacity;
}

template<typename K, typename V>
void HashMap<K, V>::put(const K& key, const V& value)
{
    if(static_cast<float>(size) / capacity > load_factor)
        resize();
    
    size_t index = hash(key);
    size_t original_index = index;

    while(table[index].has_value() && !table[index]->is_deleted && table[index]->key != key)
    {
        index = (index + 1) % capacity;
        if(index == original_index)
            throw std::runtime_error("HashMap is full");
    }

    if(!table[index].has_value() || table[index]->is_deleted)
        ++size;
    
    table[index] = Entry(key, value);
}

template<typename K, typename V>
V HashMap<K, V>::get(const K& key) const
{
    size_t index = hash(key);
    size_t original_index = index;

    while(table[index].has_value())
    {
        if(!table[index]->is_deleted && table[index]->key == key)
        {
            return table[index]->value;
        }
        index = (index + 1) % capacity;
        if(index == original_index)
            break;
    }

    throw std::runtime_error("Key not found");
}