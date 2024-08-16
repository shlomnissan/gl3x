# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

include(ShaderString)
ShaderString()

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

set(CORE_SOURCES
    core/mesh.cpp
    core/mesh.h
    core/shader.cpp
    core/shader.h
    core/timer.h
    core/window.cpp
    core/window.h
)

set(DEMO_SOURCES
    main.cpp
)

add_executable(example ${LIBS_SOURCES} ${CORE_SOURCES} ${DEMO_SOURCES})

target_include_directories(example PRIVATE
    ${CMAKE_SOURCE_DIR}/example
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(example PRIVATE
    OpenGL::GL
    engine
    fmt::fmt
    glad::glad
    glfw
)