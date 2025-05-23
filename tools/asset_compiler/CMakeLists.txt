cmake_minimum_required(VERSION 3.20)

project(asset_compiler VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_CODE
    "src/main.cpp"
)

add_executable(asset_compiler ${SOURCE_CODE})

target_include_directories(asset_compiler PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image
)

include(GNUInstallDirs)

install(TARGETS asset_compiler
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)