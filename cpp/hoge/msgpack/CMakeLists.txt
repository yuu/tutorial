cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME msgpack)
project (${PROJECT_NAME})

if(NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/submodule/msgpack)
    # featch msgpack
    execute_process(
        COMMAND git submodule update --init --depth 1
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

    # build msgpack
    execute_process(
        COMMAND cmake .
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/submodule/msgpack
    )
    execute_process(
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/submodule/msgpack
    )
endif()

file(GLOB PROJECT_SOURCES msgpack.cpp)

include_directories(${CMAKE_SOURCE_DIR}/submodule/msgpack/include)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_definitions("-std=c++11")
add_definitions("-Wall -Wextra")
add_definitions("-g")

set(CMAKE_BUILD_TYPE Debug)
