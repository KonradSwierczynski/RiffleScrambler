cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -O3)

add_library(CatchLib STATIC test_main)

function(addCatchTest target)
    add_executable(${target} ${ARGN})
    add_test(${target} ${target})

    target_link_libraries(${target} CatchLib RiffleScrambler)
endfunction()


addCatchTest(catch_test
        test
        test_bin_matrix
        test_evaluate_graph
        test_generate_graph
        test_permutation_element
        test_riffle_permutation
        test_riffle_shuffle
        test_riffle_scrambler
        )
