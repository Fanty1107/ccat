#include "../include/file_utils.h"
#include <filesystem>
#include <system_error>
#include <iostream>

bool verify_exists_file(std::filesystem::path file_path){
    std::error_code err;
    const std::filesystem::file_status status = std::filesystem::status(file_path, err);
    if (err) {
        return false;
    }
    return std::filesystem::exists(status) && std::filesystem::is_regular_file(status);
}
bool verify_exists_dir(std::filesystem::path file_path){
    std::error_code err;
    const std::filesystem::file_status status = std::filesystem::status(file_path, err);
    if (err) {
        return false;
    }
    return std::filesystem::is_regular_file(status);
}
void print_help(){
    std::cout << "Usage: ccat [FILE]\n"
        << "       ccat [OPTION]\n"
        << "Show the content of a file in standard output\n"
        << "If the file is not especified you will get an error and logged in /tmp/ccat.log by default\n"
        << "All OPTIONS now is -s and -h\n";
}
