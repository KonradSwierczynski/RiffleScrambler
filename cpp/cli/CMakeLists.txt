cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -O3)

add_executable(rf rf.cpp)
add_executable(cxxopts cxxopts.hpp)

target_link_libraries(rf RiffleScrambler)
