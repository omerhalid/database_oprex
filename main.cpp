#include <iostream>
#include "C:/Users/katka/source/market_data_handler/json/json.hpp"
#include "hashmap.hpp"
#include "disk_io.hpp"
#include "query_language.hpp"

using json = nlohmann::json;

std::vector<std::string> parse_query(const std::string& query) {
    std::istringstream iss(query);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    HashMap<int, std::string> hashmap(10, 0.75); // Provide initial capacity and load factor

    std::string query;

    while(true)
    {
        std::cout<<"> ";
        std::getline(std::cin, query);
        if(query == "EXIT")
            break;
        
        std::vector<std::string> tokens = parse_query(query);
        QueryLanguage::get_instance().execute_query(hashmap, tokens);
    }
    
    return 0;
}