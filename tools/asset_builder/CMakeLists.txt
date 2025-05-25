cmake_minimum_required(VERSION 3.20)

project(asset_builder VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_CODE
    "src/main.cpp"
    "src/mesh_converter.cpp"
    "src/mesh_converter.hpp"
    "src/texture_converter.cpp"
    "src/texture_converter.hpp"
)

add_executable(asset_builder ${SOURCE_CODE})

target_include_directories(asset_builder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(GNUInstallDirs)

install(TARGETS asset_builder
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)