cmake_minimum_required(VERSION 3.10)

project(speech-kit)

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
  configure_file(${SPEECH_SERVER}/${FILE} ${CMAKE_CURRENT_BINARY_DIR}/${FILE})
endforeach(FILE)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} curl)

