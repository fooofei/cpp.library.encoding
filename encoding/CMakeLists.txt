# This CMakeLists.txt is for encoding module.
# Other Module can use it by this:
#
# add_subdirectory(${CMAKE_HOME_DIRECTORY}/../../encoding  build_encoding)
# target_link_libraries(${PROJECT_NAME} encoding)
#
# add_subdirectory() is add this module for build.
# first argument is to tell the module(CMakeLists.txt) location,
# second argument is to tell where to build the module, make sure not to use
# the same directory with the current module.
#
# target_link_libraries() tell to link the module.
#
#

cmake_minimum_required(VERSION 2.6)
project(encoding)

if (APPLE)
    set(CMAKE_MACOSX_RPATH 0)
endif ()

if (WIN32)
    set(SOURCE_FILES
            encoding_win.cpp
            )
else()
    set(SOURCE_FILES
            encoding_posix.cpp
            )
endif()


add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

if (NOT WIN32)
    # fPIC for other library link
    target_compile_options(${PROJECT_NAME} PRIVATE -fPIC)
endif()

if (APPLE)
    # Only Apple need link with iconv
    target_link_libraries(${PROJECT_NAME} iconv)
endif()

#add_custom_command(TARGET ${PROJECT_NAME}
#        POST_BUILD
#        COMMAND mv $<TARGET_FILE_NAME:${PROJECT_NAME}> ../
#        )
