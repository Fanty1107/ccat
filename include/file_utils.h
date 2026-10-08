#pragma once

#include <filesystem>

bool verify_exists_file(std::filesystem::path file_path);
bool verify_exists_dir(std::filesystem::path file_path);
void print_help();
