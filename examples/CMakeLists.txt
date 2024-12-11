# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

set(SOURCE_CODE
    "example_light_directional.cpp"
    "example_light_directional.hpp"
    "example_material_flat.cpp"
    "example_material_flat.hpp"
    "example_material_phong.cpp"
    "example_material_phong.hpp"
)

add_executable(engine-examples main.cpp ${SOURCE_CODE})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/examples>
)


target_link_libraries(engine-examples PRIVATE engine)

add_custom_command(
    TARGET engine-examples POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:engine-examples>/assets
)