cmake_minimum_required(VERSION 3.1)
project(fnet-test)

include_directories(
    ../include
)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-pedantic)
endif ()

add_executable(fnet-test-client client.c)
add_dependencies(fnet-test-client fnet)
target_link_libraries(fnet-test-client fnet)

add_executable(fnet-test-server server.c)
add_dependencies(fnet-test-server fnet)
target_link_libraries(fnet-test-server fnet)
