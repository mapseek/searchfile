#include "search_file.hpp"
#include <functional>
#include <unistd.h>
#include <vector>
#include <queue>

search_file::search_file(std::string name_file) :
    file_name_for_search{ name_file }
{
}

std::string search_file::search_start() {
    try {
        std::string directory_path = "/home/" + std::string{ getlogin() } + "/";

        std::function<void()> searchFiles =
            [&]() {
                std::string current_directory;
                while (true) {
                    {
                        std::lock_guard<std::mutex> lock(directories_mutex);
                        if (directories_to_process.empty()) {
                            break; // Exit the thread when no directories to process
                        }
                        current_directory = directories_to_process.front();
                        directories_to_process.pop();
                    }

                    try {
                        for (const auto& entry : fs::directory_iterator(current_directory)) {
                            if (file_found) {
                                break;
                            }
                            if (fs::is_regular_file(entry) && entry.path().filename() == file_name_for_search) {
                                std::lock_guard<std::mutex> lock(file_mutex);
                                file_found = true;
                                path_to_file = entry.path().string();
                                std::cout << "Found file: " << path_to_file << std::endl;
                            } else if (fs::is_directory(entry)) {
                                std::lock_guard<std::mutex> lock(file_mutex);
                                directories_to_process.push(entry.path().string());
                            }
                        }
                    } catch (const std::filesystem::filesystem_error& ex) {
                        std::cerr << "Error: " << ex.what() << std::endl;
                    }
                }
            };

        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (!fs::is_regular_file(entry)) {
                std::cout << "subdir " << entry.path().filename().string() << std::endl;
                directories_to_process.push(entry.path().string());
            }
        }

        size_t num_threads = std::min(directories_to_process.size(), static_cast<size_t>(max_threads_count));
        for (size_t i = 0; i < num_threads; ++i) {
            std::cout << "run " << i << std::endl;
            threads.emplace_back(searchFiles);
        }

        // Join all threads to wait for their completion
        for (auto& thread : threads) {
            thread.join();
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    if (!file_found) {
        std::cout << "File not found!" << std::endl;
        return std::string{};
    }

    return path_to_file;
}
