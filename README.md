# Key-Value Database

A NoSQL key-value database implemented in C++. This project supports CRUD operations, persistence, and a simple query language.

## Features

- **CRUD Operations**: Create, Read, Update, and Delete key-value pairs.
- **Persistence**: Save and load the database to and from disk.
- **Query Language**: A simple query language to interact with the database.
- **Singleton Pattern**: Ensures a single instance of the query language.
- **Modular Design**: Organized into separate classes for better maintainability.

## Getting Started

### Prerequisites

- C++17 or later
- CMake (for building the project)
- MinGW (for GCC on Windows)

### Building the Project

1. Clone the repository:
    ```sh
    git clone https://github.com/omerhalid/database_oprex.git
    cd database_oprex
    ```

2. Create a build directory and navigate to it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake .. -G "MinGW Makefiles"
    ```

4. Build the project:
    ```sh
    mingw32-make
    ```

### Running the Project

1. Navigate to the build directory:
    ```sh
    cd build
    ```

2. Run the executable:
    ```sh
    ./main
    ```

### Usage

The following commands are supported by the query language:

- `PUT key value`: Insert or update a key-value pair.
- `GET key`: Retrieve the value for a given key.
- `REMOVE key`: Remove a key-value pair.
- `CONTAINS key`: Check if a key exists.
- `SAVE filename`: Save the database to a file.
- `LOAD filename`: Load the database from a file.
- `EXIT`: Exit the program.


## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

Ömer Halit Cinar
omerhalidcinar@gmail.com