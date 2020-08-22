cmake_minimum_required(VERSION 3.6)
project(GoProblemGenerator)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(GoProblemGenerator ${SOURCE_FILES})

#find_package(fuego)
#target_link_libraries(GoProblemGenerator fuego)

target_include_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/go")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/go")
target_link_libraries(GoProblemGenerator PUBLIC libfuego_go.a)