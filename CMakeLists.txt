cmake_minimum_required(VERSION 3.6)
project(GoProblemGenerator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp test.cpp)
add_executable(GoProblemGenerator ${SOURCE_FILES})