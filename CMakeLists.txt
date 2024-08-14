# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

cmake_minimum_required(VERSION 3.22.1)

project(tetris-3d)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(${CMAKE_SOURCE_DIR}/cmake)

include(cmake/ShaderString.cmake)
ShaderString()

add_subdirectory(${CMAKE_SOURCE_DIR}/engine)

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

set(CORE_SOURCES
    src/core/mesh.cpp
    src/core/mesh.h
    src/core/shader.cpp
    src/core/shader.h
    src/core/timer.h
    src/core/window.cpp
    src/core/window.h
)

set(DEMO_SOURCES
    src/main.cpp
)

add_executable(tetris-3d ${LIBS_SOURCES} ${CORE_SOURCES} ${DEMO_SOURCES})

target_include_directories(tetris-3d PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/engine/include
)

target_link_libraries(tetris-3d PRIVATE
    OpenGL::GL
    engine
    fmt::fmt
    glad::glad
    glfw
)