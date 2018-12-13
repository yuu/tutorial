# cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# cmake --build build/
cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME app)
project (${PROJECT_NAME})

file(GLOB PROJECT_SOURCES mylog.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Boost COMPONENTS system thread log REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})

add_definitions("-std=c++14")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-DBOOST_LOG_DYN_LINK")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
