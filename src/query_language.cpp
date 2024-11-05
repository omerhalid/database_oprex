#include "../include/query_language.hpp"

// for other types as well?
void QueryLanguage::execute_query(HashMap<int, std::string>& hashmap, const std::vector<std::string>& tokens) {
    if (tokens.empty()) return;

    const std::string& command = tokens[0];

    if (command == "PUT" && tokens.size() == 3) {
        int key = std::stoi(tokens[1]);
        const std::string& value = tokens[2];
        hashmap.put(key, value);
        std::cout << "PUT " << key << " " << value << std::endl;
    } else if (command == "GET" && tokens.size() == 2) {
        int key = std::stoi(tokens[1]);
        try {
            std::string value = hashmap.get(key);
            std::cout << "GET " << key << ": " << value << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Key not found" << std::endl;
        }
    } else if (command == "REMOVE" && tokens.size() == 2) {
        int key = std::stoi(tokens[1]);
        hashmap.remove(key);
        std::cout << "REMOVE " << key << std::endl;
    } else if (command == "CONTAINS" && tokens.size() == 2) {
        int key = std::stoi(tokens[1]);
        bool exists = hashmap.contains(key);
        std::cout << "CONTAINS " << key << ": " << (exists ? "true" : "false") << std::endl;
    } else if (command == "SAVE" && tokens.size() == 2) {
        const std::string& filename = tokens[1];
        Disk_Input_Output::save_to_disk(hashmap, filename);
        std::cout << "SAVE to " << filename << std::endl;
    } else if (command == "LOAD" && tokens.size() == 2) {
        const std::string& filename = tokens[1];
        hashmap = Disk_Input_Output::load_from_disk(filename);
        std::cout << "LOAD from " << filename << std::endl;
    } else {
        std::cout << "Invalid command" << std::endl;
    }
}