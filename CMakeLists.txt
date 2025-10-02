cmake_minimum_required(VERSION 3.20)

project(gl3x VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINE_HIDDEN ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(GL3X_BUILD_DOCS "Build API documentation using Doxygen" ON)
option(GL3X_BUILD_EXAMPLES "Build example application" ON)
option(GL3X_BUILD_IMGUI "Build and integrate ImGui from the vendored source" ON)
option(GL3X_BUILD_TESTS "Build unit tests and test infrastructure using GTest" ON)
option(GL3X_BUILD_TOOLS "Build additional CLI tools used for asset processing" ON)

add_subdirectory("vendor")
add_subdirectory("src")

if (GL3X_BUILD_TESTS)
    include(CTest)
    add_subdirectory("tests")
endif()

if (GL3X_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

if (GL3X_BUILD_TOOLS)
    add_subdirectory("tools/asset_builder")
endif()

if (GL3X_BUILD_DOCS)
    include(Doxygen)
endif()
