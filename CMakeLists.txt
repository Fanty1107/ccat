cmake_minimum_required(VERSION 3.10)
project(ccat)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(ccat src/main.cpp src/log.cpp)
target_include_directories(ccat PRIVATE include)
target_compile_features(ccat PRIVATE cxx_std_20)
