#include "search_file.hpp"
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <file_name>" << std::endl;
        return 1;
    }

    std::string file_name(argv[1]);
    search_file f(file_name);
    std::cout << f.search_start();
    return 0;
}
