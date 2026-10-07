#include "../include/log.h"
#include <ctime>
#include <iomanip>
#include <iostream>

MyLog::MyLog()
    : log_path("/tmp") ,file(log_path/"ccat.log", std::ios::app) {
    if (file.is_open()) {
        const auto now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        file << "[USAGE]: " << std::put_time(std::localtime(&time), "%Y-%m-%d") << '\n';
    } else {
        std::cerr << "[ERROR]: Cannot open /tmp/ccat.log\n";
    }
}

void MyLog::add_log(std::string text_logged, bool status_code) {
    if (!file.is_open()) {
        std::cerr << "[ERROR]: /tmp/ccat.log is closed btw\n";
        return;
    }

    if (status_code) {
        const auto now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        file << "[INFO]: "<< std::put_time(std::localtime(&time), "%H:%M:%S")<< " - " << text_logged <<" (OK)" <<'\n';
    } else {
        const auto now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        file << "[ERROR]: "<< std::put_time(std::localtime(&time), "%H:%M:%S") <<" - "<< text_logged <<" (ERROR)"<<'\n';
    }
}
