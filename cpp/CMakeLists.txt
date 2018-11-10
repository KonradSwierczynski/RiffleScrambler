cmake_minimum_required(VERSION 3.12)
project(cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp src/main.cpp include/riffle_shuffle.h src/riffle_shuffle.cpp include/riffle_permutation.h src/riffle_permutation.cpp src/BinMatrix.cpp include/BinMatrix.h include/generate_graph.h src/generate_graph.cpp include/evaluate_graph.h src/evaluate_graph.cpp include/permutation_element.h)
target_link_libraries(cpp crypto ssl)
