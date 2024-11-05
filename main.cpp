#include <iostream>
#include <fstream>
#include "C:/Users/katka/source/market_data_handler/json/json.hpp"
#include "hashmap.hpp"

using json = nlohmann::json;

void save_to_json(const HashMap<int, std::string>& hashmap, const std::string& filename) {
    json j;
    for (int i = 0; i < hashmap.get_capacity(); ++i) {
        const auto& table = hashmap.get_table();
        if (table[i].has_value() && !table[i]->is_deleted) {
            j[std::to_string(table[i]->key)] = table[i]->value;
        }
    }
    std::ofstream file(filename);
    file << j.dump(4);
}

HashMap<int, std::string> load_from_json(const std::string& filename) {
    HashMap<int, std::string> hashmap;
    std::ifstream file(filename);
    json j;
    file >> j;
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        hashmap.put(std::stoi(it.key()), it.value());
    }
    return hashmap;
}

int main() {
    HashMap<int, std::string> hashmap(10, 0.75); // Provide initial capacity and load factor

    hashmap.put(0, "Test 4");
    hashmap.put(1, "Test 5");
    hashmap.put(2, "Test 6");

    save_to_json(hashmap, "database.json");

    HashMap<int, std::string> loaded_hashmap = load_from_json("database.json");

    for (int i = 0; i < loaded_hashmap.get_capacity(); ++i) {
        const auto& table = loaded_hashmap.get_table();
        if (table[i].has_value() && !table[i]->is_deleted) {
            std::cout << table[i]->key << ": " << table[i]->value << std::endl;
        }
    }

    return 0;
}