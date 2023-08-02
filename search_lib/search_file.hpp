#ifndef SEARCH_FILE_HPP
#define SEARCH_FILE_HPP

#include <iostream>
#include <filesystem>
#include <string>
#include <thread>
#include <queue>
#include <mutex>

namespace fs = std::filesystem;

class search_file
{
private:
    static const uint8_t max_threads_count = 8;
    std::string file_name_for_search {};
    bool file_found {false};
    std::string path_to_file;
    std::mutex file_mutex;
    std::vector<std::thread> threads;
    std::queue<std::string> directories_to_process;
    std::mutex directories_mutex; // Mutex to protect access to directories_to_process

public:
    search_file(std::string name_file);

    std::string search_start();

    ~search_file() = default;
};

#endif // SEARCH_FILE_HPP
