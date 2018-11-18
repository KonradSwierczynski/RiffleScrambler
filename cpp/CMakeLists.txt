cmake_minimum_required(VERSION 3.12)
project(cpp)

set(CMAKE_CXX_STANDARD 17)
add_executable(cpp main.cpp)

add_subdirectory(RiffleScrambler)
target_link_libraries(cpp RiffleScrambler)


enable_testing()
add_subdirectory(test)
