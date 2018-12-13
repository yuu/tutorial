# cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# cmake --build build/
cmake_minimum_required(VERSION 2.8)

file(GLOB PROJECT_SOURCES mylog.cpp)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Boost COMPONENTS system thread log REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

macro(exec name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${Boost_LIBRARIES} ${ARGN})
endmacro(exec)

exec(mylog)

add_definitions("-std=c++14")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-DBOOST_LOG_DYN_LINK")
