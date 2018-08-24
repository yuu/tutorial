cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME app)
project (${PROJECT_NAME})

file(GLOB PROJECT_SOURCES *.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

add_definitions("-std=c++11")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-g")

if ("Linux" MATCHES ${CMAKE_SYSTEM_NAME})
else()
    add_definitions("-stdlib=libc++")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
