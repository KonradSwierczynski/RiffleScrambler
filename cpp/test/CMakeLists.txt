cmake_minimum_required(VERSION 3.12)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -O3)

add_library(CatchLib STATIC test_main)

function(addCatchTest target)
    add_executable(${target} ${ARGN})
    add_test(${target} ${target})

    target_link_libraries(${target} CatchLib RiffleScrambler)
endfunction()

addCatchTest(catch_test
        test
        )
