cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DB_OPREX VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(main
    src/main.cpp
    src/disk_io.cpp
    src/query_language.cpp
)

# Link libraries (if any)
# target_link_libraries(main <library_name>)