#pragma once
#include <fstream>
#include <string>
#include <filesystem>

class MyLog{
public:
    MyLog();
    void add_log(std::string text_logged, bool status_code);
private:
    std::filesystem::path log_path;
    std::ofstream file;
};
