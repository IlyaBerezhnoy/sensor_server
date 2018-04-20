cmake_minimum_required(VERSION 3.10)

project(alice)

set(SOURCES
    main.c
    )

set(SERVER_FILES
    play.sh
    replay.sh
    server.py
    )

set(SPEECH_SERVER ./speech-kit)
foreach(FILE ${SERVER_FILES})
  configure_file(${SPEECH_SERVER}/${FILE} ${SHELLED_OUTPUT_DIR}/${FILE})
endforeach(FILE)

include_directories(
    ../../snode/fnode/include
    ../../snode/fcommon/include
    )


add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} fnode)
target_link_libraries(${PROJECT_NAME} curl fnode)

