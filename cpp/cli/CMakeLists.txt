cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -O3)

add_executable(rs rs.cpp)

target_link_libraries(rs RiffleScrambler)
