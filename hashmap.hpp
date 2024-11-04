#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <vector>
#include <functional>
#include <stdexcept>
#include <utility>

template<typename K, typename V>
class HashMap
{
public:

    HashMap(size_t initial_capacity = 16, float load_factor = 0.75) {}

    void put(const K& key, const V& value);
    V get(const K& key) const;
    void remove(const K& key);
    bool containes(const K& key) const;

private:
    struct Entry
    {
        K key;
        V value;
        bool is_deleted;

        Entry(K key_, V value_, ) : key(key_), value(value_), is_deleted(false) {}
    };
    
    size_t capacity;
    float load_factor;
    size_t size;

    size_t hash(const K& key) const;
    void resize();


};

#include "hashmap.cpp"

#endif // HASHMAP_HPP