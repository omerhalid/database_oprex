#ifndef DISK_IO_HPP
#define DISK_IO_HPP

#include "../include/hashmap.hpp"
#include <fstream>

class Disk_Input_Output
{
public:
    static void save_to_disk(const HashMap<int, std::string>& hashmap, const std::string& filename);
    static HashMap<int, std::string> load_from_disk(const std::string& filename);
};

#endif // DISK_IO_HPP