
file(GLOB_RECURSE RIFFLE_SOURCES "src/*.cpp")
file(GLOB_RECURSE RIFFLE_HEADERS "include/*.h")

set(RIFFLE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_library(RiffleScrambler ${RIFFLE_SOURCES} ${RIFFLE_HEADERS})
target_include_directories(RiffleScrambler PUBLIC ${RIFFLE_INCLUDE_DIR})

set_target_properties(RiffleScrambler PROPERTIES COMPILE_FLAGS "-O3")

target_link_libraries(RiffleScrambler ssl crypto)

