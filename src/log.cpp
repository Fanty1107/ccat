#include "../include/log.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

MyLog::MyLog()
    : log_path("/tmp") ,file(log_path/"ccat.log", std::ios::app) {
    if (file.is_open()) {
        const auto now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        file << "[OPEN]: " << std::put_time(std::localtime(&time), "%H:%M") <<" (OK) " << '\n';
    } else {
        std::cerr << "[ERROR]: Cannot open /tmp/ccat.log\n";
    }
}
MyLog::~MyLog(){
    if(file.is_open()){
    const auto now = std::chrono::system_clock::now();
    const std::time_t time = std::chrono::system_clock::to_time_t(now);
    file << "[END]: " << std::put_time(std::localtime(&time), "%H:%M:%S") << " (OK) " << '\n';
    file.close();
    }
}

void MyLog::add_log(std::string text_logged, STATUS_LOG status) {
    if (!file.is_open()) {
        std::cerr << "[ERROR]: /tmp/ccat.log is closed btw\n";
        return;
    }
    if (status == STATUS_LOG::OK) {
        const auto now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        file << "[INFO]: "<< std::put_time(std::localtime(&time), "%H:%M:%S")<< " - " << text_logged <<" (OK)" <<'\n';
    } else {
        const auto now = std::chrono::system_clock::now();
        const std::time_t time = std::chrono::system_clock::to_time_t(now);
        file << "[ERROR]: "<< std::put_time(std::localtime(&time), "%H:%M:%S") <<" - "<< text_logged <<" (ERROR)"<<'\n';
    }
}
std::string MyLog::parse_log_into_str(){
    file.flush();
    std::ifstream input_file(log_path / "ccat.log");
    if (!input_file) {
        std::cerr << "[Error] Cannot open log file\n" << (log_path / "ccat.log");
        return "";
    }
    std::string line;
    std::string buffer;
    while (std::getline(input_file, line)) {
        buffer += line + '\n';
    }
    return buffer;
}
std::vector<std::string> MyLog::get_files_from_log(std::string &buffer){
    const std::string marker = "[INFO]";
      const std::string begin = "Read the file: ";
      const std::string end = " (OK)";

      std::vector<std::string> files_name;
      std::size_t pos = 0;

      while ((pos = buffer.find(marker, pos)) != std::string::npos) {
          const auto startName = buffer.find(begin, pos);
          const auto endLine = buffer.find('\n', pos);

          if (startName == std::string::npos ||
              (endLine != std::string::npos && startName > endLine)) {
              pos += marker.size();
              continue;
          }

          const auto nameBegin = startName + begin.size();
          const auto nameEnd = buffer.find(end, nameBegin);

          if (nameEnd != std::string::npos &&
              (endLine == std::string::npos || nameEnd < endLine)) {
              files_name.push_back(buffer.substr(nameBegin, nameEnd - nameBegin));
              pos = nameEnd + end.size();
          } else {
              pos = nameBegin;
          }
      }
      return files_name;
}
void MyLog::show_file_reads(){
    std::string buffer = parse_log_into_str();
    std::vector<std::string> files_name = get_files_from_log(buffer);
    if (files_name.empty()) {
        std::cout << "Not a single file read by ccat '-' ";
        return;
    }
    for (auto name : files_name) {
        std::cout << name << '\n';
    }
}
