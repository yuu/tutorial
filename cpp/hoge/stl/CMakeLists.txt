cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME exe)
project (${PROJECT_NAME})

file(GLOB PROJECT_SOURCES src/*.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME}
    pthread
)

add_definitions("-std=c++14")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-g")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
