cmake_minimum_required (VERSION 2.6)

set(BINARY_NAME encodingdemo)

project (${BINARY_NAME})

add_executable(${BINARY_NAME} main.cpp posix_encoding.cpp)

add_custom_command(
        TARGET ${BINARY_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${BINARY_NAME}> ../$<TARGET_FILE_NAME:${BINARY_NAME}>
)