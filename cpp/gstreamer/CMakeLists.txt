cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME gstreamer_tutorial)
project (${PROJECT_NAME})

find_package(PkgConfig)
pkg_check_modules(GST gstreamer-1.0 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GST_INCLUDE_DIRS}
)

link_directories(
    ${GST_LIBRARY_DIRS}
)

set(LIBS
    ${GST_LIBRARIES}
)

function(myfunc file app)
    add_executable(${app} ${file})
    target_link_libraries(${app} ${LIBS})
endfunction()

myfunc(src/basic-tutorial-1.cpp tuto1)
myfunc(src/basic-tutorial-2.cpp tuto2)
myfunc(src/basic-tutorial-3.cpp tuto3)

add_definitions("-std=c++14")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-g")