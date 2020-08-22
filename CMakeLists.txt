cmake_minimum_required(VERSION 3.6)
project(GoProblemGenerator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
add_executable(GoProblemGenerator ${SOURCE_FILES})

#find_package(fuego)
#target_link_libraries(GoProblemGenerator fuego)

#target_include_directories(GoProblemGenerator PUBLIC "$ENV{BOOST_ROOT}/include")
#target_link_directories(GoProblemGenerator PUBLIC "$ENV{BOOST_ROOT}/lib")
#target_link_libraries(GoProblemGenerator PUBLIC libboost_date_time.a)
#target_link_libraries(GoProblemGenerator PUBLIC libboost_system.a)

#find_package(Boost COMPONENTS system filesystem REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})

#target_include_directories(GoProblemGenerator PUBLIC "$ENV{PACHI_DIR}")
#target_link_directories(GoProblemGenerator PUBLIC "$ENV{PACHI_DIR}")
#target_link_libraries(GoProblemGenerator PUBLIC libfuego_go.a)
