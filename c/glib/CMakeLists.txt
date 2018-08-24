cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME app)
project (${PROJECT_NAME})

find_package(PkgConfig)
pkg_check_modules(GLIB glib-2.0 REQUIRED)
pkg_check_modules(GOBJ gobject-2.0 REQUIRED)
pkg_check_modules(GLESv2 glesv2 REQUIRED)
pkg_check_modules(EGL egl REQUIRED)
pkg_check_modules(X11 x11 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLIB_INCLUDE_DIRS}
    ${GOBJ_INCLUDE_DIRS}
    ${GLESv2_INCLUDE_DIRS}
    ${EGL_INCLUDE_DIRS}
    ${X11_INCLUDE_DIRS}
)

link_directories(
    ${GLIB_LIBRARY_DIRS}
    ${GOBJ_LIBRARY_DIRS}
    ${GLESv2_LIBRARY_DIRS}
    ${EGL_LIBRARY_DIRS}
    ${X11_LIBRARY_DIRS}
)

set(LIBS
    ${GLIB_LIBRARIES}
    ${GOBJ_LIBRARIES}
    ${GLESv2_LIBRARIES}
    ${EGL_LIBRARIES}
    ${X11_LIBRARIES}
)

function(myfunc file app)
    add_executable(${app} ${file})
    target_link_libraries(${app} ${LIBS})
endfunction()

file(GLOB SS src/*.c)
add_executable(app ${SS})
target_link_libraries(app ${LIBS})

add_definitions("-std=c11")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-g")