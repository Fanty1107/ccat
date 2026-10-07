#include <iostream>
#include "../include/log.h"
int main(int argc, char* argv[]){
    if (argc < 2) {
        return 1;
    }
        std::ifstream filein(argv[1], std::ios::in);
        MyLog log_file;
        bool status_log = true;

        if (!filein.is_open()) {
            log_file.add_log("Cannot open the file", !status_log);
            return 1;
        }
        std::string buffer;
        std::string line;
        while (std::getline(filein, line)) {
            std::cout << line << std::endl;
        }
        if (filein.eof()) {
            log_file.add_log((std::string)"Read the file: " + argv[1], status_log);
        }else {
            log_file.add_log("Cannot read the file", !status_log);
        }
        filein.close();
        return 0;
}
