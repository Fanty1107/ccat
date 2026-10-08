#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

enum STATUS_LOG{
    OK,
    ERROR,
};
class MyLog{
private:
    std::string parse_log_into_str();
    std::vector<std::string> get_files_from_log(std::string& buffer);
    std::filesystem::path log_path;
    std::ofstream file;

public:
    MyLog();
    ~MyLog();
    void add_log(std::string text_logged, STATUS_LOG);
    void show_file_reads();
    void print_error_terminal(std::string);
    void print_ok_terminal(std::string);
};
