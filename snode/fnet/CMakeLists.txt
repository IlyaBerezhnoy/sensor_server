cmake_minimum_required(VERSION 3.1)
project(fnet)

set(FNET_HEADERS
    src/ip_address.h
    src/socket.h
)

set(FNET_SOURCES
    src/ip_address.c
)

if (WIN32)
else()
    set(FNET_SOURCES
        ${FNET_SOURCES}
        src/os/linux/socket.c
    )
endif (WIN32)

set(FNET_LIBS
)

if (WIN32)
    set(FNET_LIBS
        ${FNET_LIBS}
        ws2_32
    )
endif (WIN32)

use_c99()

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-pedantic -fPIC)
endif ()

include_directories(../fcommon/include)

add_library(fnet STATIC ${FNET_HEADERS} ${FNET_SOURCES})
target_link_libraries(fnet ${FNET_LIBS})

add_subdirectory(test fnet-test)
