#include <iostream>
#include <fstream>
#include "C:/Users/katka/source/market_data_handler/json/json.hpp"
#include "hashmap.hpp"

using json = nlohmann::json;

void save_to_disk(const HashMap<int, std::string>& hashmap, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file for writing");
    }
    for (int i = 0; i < hashmap.get_capacity(); ++i) {
        const auto& table = hashmap.get_table();
        if (table[i].has_value() && !table[i]->is_deleted) {
            file.write(reinterpret_cast<const char*>(&table[i]->key), sizeof(table[i]->key));
            size_t value_size = table[i]->value.size();
            file.write(reinterpret_cast<const char*>(&value_size), sizeof(value_size));
            file.write(table[i]->value.data(), value_size);
        }
    }
}

HashMap<int, std::string> load_from_disk(const std::string& filename) {
    HashMap<int, std::string> hashmap;
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file for reading");
    }
    while (file) {
        int key;
        file.read(reinterpret_cast<char*>(&key), sizeof(key));
        size_t value_size;
        file.read(reinterpret_cast<char*>(&value_size), sizeof(value_size));
        std::string value(value_size, '\0');
        file.read(&value[0], value_size);
        if (file) {
            hashmap.put(key, value);
        }
    }
    return hashmap;
}

int main() {
    HashMap<int, std::string> hashmap(10, 0.75); // Provide initial capacity and load factor

    hashmap.put(0, "Test 4");
    hashmap.put(1, "Test 5");
    hashmap.put(2, "Test 6");

    save_to_disk(hashmap, "database.json");

    HashMap<int, std::string> loaded_hashmap = load_from_disk("database.json");

    for (int i = 0; i < loaded_hashmap.get_capacity(); ++i) {
        const auto& table = loaded_hashmap.get_table();
        if (table[i].has_value() && !table[i]->is_deleted) {
            std::cout << table[i]->key << ": " << table[i]->value << std::endl;
        }
    }

    return 0;
}