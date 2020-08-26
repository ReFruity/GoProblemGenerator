cmake_minimum_required(VERSION 3.6)
project(GoProblemGenerator)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES src/*.cpp)
add_executable(GoProblemGenerator ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "-DNDEBUG")

#find_package(fuego)
#target_link_libraries(GoProblemGenerator fuego)

target_include_directories(GoProblemGenerator PUBLIC "$ENV{BOOST_ROOT}/include")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{BOOST_ROOT}/lib")
target_link_libraries(GoProblemGenerator PUBLIC libboost_chrono.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_date_time.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_filesystem.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_prg_exec_monitor.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_program_options.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_system.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_test_exec_monitor.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_thread.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_timer.a)
target_link_libraries(GoProblemGenerator PUBLIC libboost_unit_test_framework.a)

#target_include_directories(GoProblemGenerator PUBLIC "/usr/local/include")
#target_link_directories(GoProblemGenerator PUBLIC "/usr/local/lib")

#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

target_include_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/go")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/go")
target_link_libraries(GoProblemGenerator PUBLIC libfuego_go.a)

target_include_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/smartgame")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/smartgame")
target_link_libraries(GoProblemGenerator PUBLIC libfuego_smartgame.a)

target_include_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/features")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/features")
target_link_libraries(GoProblemGenerator PUBLIC libfuego_features.a)

target_include_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/gouct")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/gouct")
target_link_libraries(GoProblemGenerator PUBLIC libfuego_gouct.a)

target_include_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/simpleplayers")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/simpleplayers")
target_link_libraries(GoProblemGenerator PUBLIC libfuego_simpleplayers.a)

target_include_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/gtpengine")
target_link_directories(GoProblemGenerator PUBLIC "$ENV{FUEGO_DIR}/gtpengine")
target_link_libraries(GoProblemGenerator PUBLIC libfuego_gtpengine.a)
