cmake_minimum_required (VERSION 2.6)

set(BINARY_NAME testencoding)

project (${BINARY_NAME})

add_executable(${BINARY_NAME} main.cpp)

if (NOT TARGET encoding)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../  build_encoding)
endif ()
target_link_libraries(${BINARY_NAME} encoding)

add_custom_command(
        TARGET ${BINARY_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${BINARY_NAME}> ${CMAKE_CURRENT_SOURCE_DIR}/$<TARGET_FILE_NAME:${BINARY_NAME}>
)
