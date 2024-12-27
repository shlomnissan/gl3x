set(PUBLIC_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include/engine)

set(SOURCE_CODE
    "core/application_context.cpp"
    "core/disposable.hpp"
    "core/event.hpp"
    "core/event_dispatcher.cpp"
    "core/event_dispatcher.hpp"
    "core/geometry.cpp"
    "core/identity.hpp"
    "core/image.hpp"
    "core/program_attributes.cpp"
    "core/program_attributes.hpp"
    "core/renderer.cpp"
    "core/shader_library.cpp"
    "core/shader_library.hpp"
    "core/timer.cpp"
    "core/window.cpp"
    "core/window_impl.cpp"
    "core/window_impl.hpp"
    "geometries/box_geometry.cpp"
    "geometries/cylinder_geometry.cpp"
    "geometries/plane_geometry.cpp"
    "geometries/sphere_geometry.cpp"
    "lights/directional_light.cpp"
    "lights/point_light.cpp"
    "lights/spot_light.cpp"
    "loaders/image_loader.cpp"
    "loaders/image_loader.hpp"
    "math/euler.cpp"
    "math/matrix3.cpp"
    "math/matrix4.cpp"
    "math/transform_2d.cpp"
    "math/transform.cpp"
    "math/utilities.cpp"
    "math/vector2.cpp"
    "math/vector3.cpp"
    "math/vector4.cpp"
    "renderer/gl/gl_buffers.cpp"
    "renderer/gl/gl_buffers.hpp"
    "renderer/gl/gl_program.cpp"
    "renderer/gl/gl_program.hpp"
    "renderer/gl/gl_programs.cpp"
    "renderer/gl/gl_programs.hpp"
    "renderer/gl/gl_renderer_impl.cpp"
    "renderer/gl/gl_renderer_impl.hpp"
    "renderer/gl/gl_textures.cpp"
    "renderer/gl/gl_textures.hpp"
    "renderer/gl/gl_uniform.cpp"
    "renderer/gl/gl_uniform.hpp"
    "resources/camera_orbit.cpp"
    "resources/grid.cpp"
    "nodes/camera.cpp"
    "nodes/camera.hpp"
    "nodes/camera_orthographic.cpp"
    "nodes/camera_perspective.cpp"
    "nodes/mesh.cpp"
    "nodes/node.cpp"
    "nodes/scene.cpp"
    "textures/texture_2d.cpp"
    "utilities/data_series.hpp"
    "utilities/logger.cpp"
    "utilities/logger.hpp"
)

set(PUBLIC_HEADERS
    "${PUBLIC_HEADERS_DIR}/core/application_context.hpp"
    "${PUBLIC_HEADERS_DIR}/core/geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/core/renderer.hpp"
    "${PUBLIC_HEADERS_DIR}/core/timer.hpp"
    "${PUBLIC_HEADERS_DIR}/core/window.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/box_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/cylinder_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/plane_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/sphere_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/ambient_light.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/directional_light.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/light.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/point_light.hpp"
    "${PUBLIC_HEADERS_DIR}/materials/flat_material.hpp"
    "${PUBLIC_HEADERS_DIR}/materials/material.hpp"
    "${PUBLIC_HEADERS_DIR}/materials/phong_material.hpp"
    "${PUBLIC_HEADERS_DIR}/math/color.hpp"
    "${PUBLIC_HEADERS_DIR}/math/euler.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix4.hpp"
    "${PUBLIC_HEADERS_DIR}/math/transform_2d.hpp"
    "${PUBLIC_HEADERS_DIR}/math/transform.hpp"
    "${PUBLIC_HEADERS_DIR}/math/utilities.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector2.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector4.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/camera_orbit.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/grid.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/camera_orthographic.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/camera_perspective.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/mesh.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/node.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/scene.hpp"
    "${PUBLIC_HEADERS_DIR}/textures/texture.hpp"
    "${PUBLIC_HEADERS_DIR}/textures/texture_2d.hpp"
)

set(HEADER_BUNDLES
    "${PUBLIC_HEADERS_DIR}/core.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries.hpp"
    "${PUBLIC_HEADERS_DIR}/lights.hpp"
    "${PUBLIC_HEADERS_DIR}/materials.hpp"
    "${PUBLIC_HEADERS_DIR}/math.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes.hpp"
    "${PUBLIC_HEADERS_DIR}/resources.hpp"
    "${PUBLIC_HEADERS_DIR}/textures.hpp"
)

set(EXTERNAL_SOURCES
    "${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/external/imgui/imgui_impl_opengl3.cpp"
)

include(ShaderProcessor)

add_library(
    ${PROJECT_NAME}
    ${PUBLIC_HEADERS}
    ${HEADER_BUNDLES}
    ${SOURCE_CODE}
    ${EXTERNAL_SOURCES}
)

find_package(OpenGL REQUIRED)
find_package(fmt REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(Stb REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/external>
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Stb_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    OpenGL::GL
    glad::glad
    glfw
PUBLIC
    fmt::fmt
    imgui::imgui
)

set_target_properties(${TARGET_NAME} PROPERTIES
    VERSION ${engine_VERSION_MAJOR}.${engine_VERSION_MINOR}.${engine_VERSION_PATCH}
    SOVERSION ${engine_VERSION_MAJOR}
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})