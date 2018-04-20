cmake_minimum_required(VERSION 3.1)
project(fnode-test)

include_directories(
    ../include
)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-pedantic)
endif ()

add_executable(fnode-test main.c)
add_dependencies(fnode-test fnode)
target_link_libraries(fnode-test fnode)
