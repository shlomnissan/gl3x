# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

set(SOURCE_CODE
    "example_scene.hpp"
    "geometries/example_box_geometry.cpp"
    "geometries/example_box_geometry.hpp"
    "geometries/example_cylinder_geometry.cpp"
    "geometries/example_cylinder_geometry.hpp"
    "geometries/example_plane_geometry.cpp"
    "geometries/example_plane_geometry.hpp"
    "geometries/example_sphere_geometry.cpp"
    "geometries/example_sphere_geometry.hpp"
    "lights/example_directional_light.cpp"
    "lights/example_directional_light.hpp"
    "lights/example_point_light.cpp"
    "lights/example_point_light.hpp"
    "lights/example_spot_light.cpp"
    "lights/example_spot_light.hpp"
    "materials/example_flat_material.cpp"
    "materials/example_flat_material.hpp"
    "materials/example_phong_material.cpp"
    "materials/example_phong_material.hpp"
    "materials/example_shader_material.cpp"
    "materials/example_shader_material.hpp"
)

find_package(imgui REQUIRED)

add_executable(engine-examples main.cpp ${SOURCE_CODE})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/examples>
)

target_link_libraries(engine-examples PRIVATE
    engine
    imgui::imgui
)

add_custom_command(
    TARGET engine-examples POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:engine-examples>/assets
)