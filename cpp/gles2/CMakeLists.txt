cmake_minimum_required(VERSION 3.0.0)

project(app VERSION 0.0.1)

option(USE_iMX6FB_BACKEND     "Use iMX6FB for EGL Backend"        OFF)
option(USE_X11_BACKEND        "Use desktop X11 for EGL Backend"   ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLESv2 glesv2 REQUIRED)
pkg_check_modules(EGL egl REQUIRED)
pkg_check_modules(PNG libpng REQUIRED)

if (USE_X11_BACKEND)
    pkg_check_modules(X11 x11 REQUIRED)
    include_directories(${X11_INCLUDE_DIRS})
    link_directories(${X11_LIBRARY_DIRS})
    set(LIBS ${LIBS} ${X11_LIBRARIES})
endif()

include_directories(
    ${GLESv2_INCLUDE_DIRS}
    ${EGL_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
)

link_directories(
    ${GLESv2_LIBRARY_DIRS}
    ${EGL_LIBRARY_DIRS}
    ${PNG_LIBRARY_DIRS}
)

set(LIBS ${LIBS}
    ${GLESv2_LIBRARIES}
    ${EGL_LIBRARIES}
    ${PNG_LIBRARIES}
)

file(GLOB SOURCES
    main.cpp
)

if(USE_iMX6FB_BACKEND)
    message(("USE iMX6FB BACKEND"))
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/backend_fb.cpp)

    add_definitions("-DUSE_iMX6FB_BACKEND")
    add_definitions("-DEGL_API_FB")
    add_definitions("-DLINUX")
endif()

if(USE_X11_BACKEND)
    message("USE X11 BACKEND")
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/backend_x11.cpp)

    add_definitions("-DUSE_X11_BACKEND")
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

add_definitions("-std=c++14")
add_definitions("-Wall")
add_definitions("-Wextra")
add_definitions("-g")

