set(SOURCE_CODE
    "example_sandbox.cpp"
    "example_sandbox.hpp"
    "example_scene.hpp"
    "ui_helpers.cpp"
    "ui_helpers.hpp"
    "animation/example_animated_transform.cpp"
    "animation/example_animated_transform.hpp"
    "lighting/example_directional_light.cpp"
    "lighting/example_directional_light.hpp"
    "lighting/example_point_light.cpp"
    "lighting/example_point_light.hpp"
    "lighting/example_spot_light.cpp"
    "lighting/example_spot_light.hpp"
    "materials/example_phong_material.cpp"
    "materials/example_phong_material.hpp"
    "materials/example_shader_material.cpp"
    "materials/example_shader_material.hpp"
    "materials/example_unlit_material.cpp"
    "materials/example_unlit_material.hpp"
    "rendering_effects/example_blending.cpp"
    "rendering_effects/example_blending.hpp"
    "rendering_effects/example_fog.cpp"
    "rendering_effects/example_fog.hpp"
    "scene_features/example_debug_visuals.cpp"
    "scene_features/example_debug_visuals.hpp"
    "scene_features/example_frustum_culling.cpp"
    "scene_features/example_frustum_culling.hpp"
    "scene_features/example_mesh_instancing.cpp"
    "scene_features/example_mesh_instancing.hpp"
    "scene_features/example_model_loader.cpp"
    "scene_features/example_model_loader.hpp"
    "scene_features/example_primitives.cpp"
    "scene_features/example_primitives.hpp"
    "scene_features/example_sprite.cpp"
    "scene_features/example_sprite.hpp"
)

add_executable(gleam-examples main.cpp ${SOURCE_CODE})

# disable RTTI and exceptions
target_compile_options(gleam-examples PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:Clang>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:AppleClang>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:MSVC>:/GR /EHsc>
)

target_include_directories(gleam-examples PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/examples>
)

target_link_libraries(gleam-examples PRIVATE gleam)

add_custom_command(
    TARGET gleam-examples POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:gleam-examples>/assets
)