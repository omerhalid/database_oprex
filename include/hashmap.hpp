#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>
#include <optional>

template<typename K, typename V>
struct Entry {
    K key;
    V value;
    bool is_deleted;

    Entry(const K& key, const V& value) : key(key), value(value), is_deleted(false) {}
};

template<typename K, typename V>
class HashMap
{
public:
    HashMap(size_t initial_capacity, float load_factor);
    HashMap() : HashMap(10, 0.75) {} // Default constructor

    void put(const K& key, const V& value);
    V get(const K& key) const;
    void remove(const K& key);
    bool contains(const K& key) const;
    int get_capacity() const;
    const std::vector<std::optional<Entry<K, V>>>& get_table() const;

private:
    std::vector<std::optional<Entry<K, V>>> table;
    size_t capacity;
    float load_factor;
    size_t size;

    size_t hash(const K& key) const;
    void resize();
};

// Implementation of HashMap template class

template<typename K, typename V>
HashMap<K, V>::HashMap(size_t initial_capacity, float load_factor) :
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
    
    table[index] = Entry<K, V>(key, value);
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

template<typename K, typename V>
void HashMap<K, V>::remove(const K& key)
{
    size_t index = hash(key);
    size_t original_index = index;

    while(table[index].has_value())
    {
        if(!table[index]->is_deleted && table[index]->key == key)
        {
            table[index]->is_deleted = true;
            --size;
            return;
        }
        index = (index + 1) % capacity;
        if(index == original_index)
            break;
    }
}

template<typename K, typename V>
bool HashMap<K, V>::contains(const K& key) const
{
    size_t index = hash(key);
    size_t original_index = index;

    while(table[index].has_value())
    {
        if(!table[index]->is_deleted && table[index]->key == key)
        {
            return true;
        }
        index = (index + 1) % capacity;
        if(index == original_index)
            break;
    }
    return false;
}

template<typename K, typename V>
void HashMap<K, V>::resize()
{
    capacity *= 2;

    std::vector<std::optional<Entry<K, V>>> new_table(capacity);

    for(const auto& entry : table)
    {
        if(entry.has_value() && !entry->is_deleted)
        {
            size_t index = hash(entry->key);
            while(new_table[index].has_value())
            {
                index = (index + 1) % capacity;
            }
            new_table[index] = entry;
        }
    }
    
    table = std::move(new_table);
}

template<typename K, typename V>
int HashMap<K, V>::get_capacity() const
{
    return this->capacity;
}

template<typename K, typename V>
const std::vector<std::optional<Entry<K, V>>>& HashMap<K, V>::get_table() const
{
    return this->table;
}

#endif // HASHMAP_HPP