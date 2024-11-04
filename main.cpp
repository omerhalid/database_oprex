#include <iostream>
#include <unordered_map>
#include <fstream>
#include "C:/Users/katka/source/market_data_handler/json/json.hpp"

using json = nlohmann::json;

void save_to_json(const std::unordered_map<int, std::string>& hashmap, const std::string& filename) {
    json j;
    for (const auto& pair : hashmap) {
        j[std::to_string(pair.first)] = pair.second;
    }
    std::ofstream file(filename);
    file << j.dump(4);
}

std::unordered_map<int, std::string> load_from_json(const std::string& filename) {
    std::unordered_map<int, std::string> hashmap;
    std::ifstream file(filename);
    json j;
    file >> j;
    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        hashmap[std::stoi(it.key())] = it.value();
    }
    return hashmap;
}

int main() {
    std::unordered_map<int, std::string> hashmap;

    hashmap[0] = "Test 1";
    hashmap[1] = "Test 2";
    hashmap[2] = "Test 3";

    save_to_json(hashmap, "database.json");

    std::unordered_map<int, std::string> loaded_hashmap = load_from_json("database.json");

    for (const auto& pair : loaded_hashmap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}