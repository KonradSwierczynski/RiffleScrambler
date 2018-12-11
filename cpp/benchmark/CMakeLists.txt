cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -O3)

add_executable(benchmark benchmark.cpp)
add_executable(rf_bench riffle_scrambler.cpp)
add_executable(utils utils.cpp)

target_link_libraries(rf_bench RiffleScrambler)
target_link_libraries(benchmark RiffleScrambler)
