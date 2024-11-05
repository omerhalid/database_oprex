#pragma once

#include "../include/hashmap.hpp"
#include "../include/disk_io.hpp"
#include <iostream>
#include <vector>

class QueryLanguage
{
public:
    static QueryLanguage& get_instance() {
        static QueryLanguage instance;
        return instance;
    }

    void execute_query(HashMap<int, std::string>& hashmap, const std::vector<std::string>& tokens);

private:
    QueryLanguage() {} // Private constructor
    QueryLanguage(const QueryLanguage&) = delete;
    QueryLanguage& operator=(const QueryLanguage&) = delete;
};
