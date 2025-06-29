cmake_minimum_required(VERSION 3.20)

project(gleam VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINE_HIDDEN ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(GLEAM_BUILD_TESTS "build tests" ON)
option(GLEAM_BUILD_EXAMPLES "build examples" ON)
option(GLEAM_BUILD_TOOLS "build tools" ON)
option(GLEAM_BUILD_DOCS "build documentation" ON)

add_subdirectory("vendor")
add_subdirectory("src")

if (GLEAM_BUILD_TESTS)
    include(CTest)
    add_subdirectory("tests")
endif()

if (GLEAM_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

if (GLEAM_BUILD_TOOLS)
    add_subdirectory("tools/asset_builder")
endif()

if (GLEAM_BUILD_DOCS)
    include(Doxygen)
endif()
