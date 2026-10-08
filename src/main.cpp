#include <filesystem>
#include <iostream>
#include "log.h"
#include "file_utils.h"
int main(int argc, char* argv[]){
    MyLog log_file;
    if (argc < 2) {
        log_file.add_log("Didnt enter a file", STATUS_LOG::ERROR);
        std::cout << "Enter a file to read see -h for help\n";
        return 1;
    }
    std::string arg = argv[1];
    if (arg == "-h") {
        log_file.add_log("See help", STATUS_LOG::OK);
        print_help();
        return 0;
    }
    if (arg == "-s") {
        log_file.show_file_reads();
        return 0;
    }
    std::filesystem::path file_path = arg;
    std::ifstream filein(arg, std::ios::in);

    if (!verify_exists_dir(file_path)) {
        log_file.add_log("You enter a directory not a file", STATUS_LOG::ERROR);
        std::cout << "[ERROR]: Enter a file not a directory\n";
        return 1;
    }
    if(!verify_exists_file(file_path)){
        log_file.add_log("File doesnt exist", STATUS_LOG::ERROR);
        std::cout << "[ERROR]: File doesnt exist\n";
        return 1;
    }
    if (!filein.is_open()) {
        log_file.add_log("Cannot open the file", STATUS_LOG::ERROR);
        return 1;
    }
    std::string line;
    while (std::getline(filein, line)) {
        std::cout << line << std::endl;
    }
    if (filein.eof()) {
        log_file.add_log((std::string)"Read the file: " + arg, STATUS_LOG::OK);
    }else {
        log_file.add_log("Cannot read the file", STATUS_LOG::ERROR);
    }
    filein.close();
    return 0;
}
