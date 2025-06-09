# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

set(SOURCE_CODE
    "example_scene.hpp"
    "ui_helpers.cpp"
    "ui_helpers.hpp"
    "effects/example_blending.cpp"
    "effects/example_blending.hpp"
    "effects/example_fog.cpp"
    "effects/example_fog.hpp"
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
    "meshes/example_arbitrary_mesh.cpp"
    "meshes/example_arbitrary_mesh.hpp"
    "meshes/example_primitive_mesh.cpp"
    "meshes/example_primitive_mesh.hpp"
    "resources/example_arrow_resource.cpp"
    "resources/example_arrow_resource.hpp"
    "resources/example_grid_resource.cpp"
    "resources/example_grid_resource.hpp"
    "test/example_frustum_culling_test.cpp"
    "test/example_frustum_culling_test.hpp"
    "test/example_lerp_animation_test.cpp"
    "test/example_lerp_animation_test.hpp"
)

find_package(imgui REQUIRED)

add_executable(gleam-examples main.cpp ${SOURCE_CODE})

# disable RTTI and exceptions
target_compile_options(gleam-examples PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:Clang>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:AppleClang>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:MSVC>:/GR- /EHs-c->
)

target_include_directories(gleam-examples PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/examples>
)

target_link_libraries(gleam-examples PRIVATE
    gleam
    imgui::imgui
)

add_custom_command(
    TARGET gleam-examples POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:gleam-examples>/assets
)