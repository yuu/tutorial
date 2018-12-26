# cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
# cmake --build build/
cmake_minimum_required(VERSION 2.8)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/seedsm/src)

macro(exec name files)
    add_executable(${name} ${files})
    target_link_libraries(${name} -lev ${ARGN})
endmacro(exec)

exec(twr twochild-return.cpp)

add_definitions("-std=c++14")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-pedantic-errors")
