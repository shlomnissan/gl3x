set(PUBLIC_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include/gleam)

set(SOURCE_CODE
    "cameras/camera.cpp"
    "cameras/orthographic_camera.cpp"
    "cameras/perspective_camera.cpp"
    "core/application_context.cpp"
    "core/event_dispatcher.hpp"
    "core/geometry.cpp"
    "core/program_attributes.cpp"
    "core/program_attributes.hpp"
    "core/render_lists.cpp"
    "core/render_lists.hpp"
    "core/renderer.cpp"
    "core/shader_library.cpp"
    "core/shader_library.hpp"
    "core/timer.cpp"
    "core/window.cpp"
    "core/window_impl.cpp"
    "core/window_impl.hpp"
    "geometries/box_geometry.cpp"
    "geometries/cone_geometry.cpp"
    "geometries/cylinder_geometry.cpp"
    "geometries/plane_geometry.cpp"
    "geometries/sphere_geometry.cpp"
    "lights/directional_light.cpp"
    "lights/point_light.cpp"
    "lights/spot_light.cpp"
    "loaders/mesh_loader.cpp"
    "loaders/texture_loader.cpp"
    "math/box3.cpp"
    "math/euler.cpp"
    "math/frustum.cpp"
    "math/matrix3.cpp"
    "math/matrix4.cpp"
    "math/plane.cpp"
    "math/sphere.cpp"
    "math/transform2.cpp"
    "math/transform3.cpp"
    "math/utilities.cpp"
    "math/vector3.cpp"
    "math/vector4.cpp"
    "nodes/mesh.cpp"
    "nodes/node.cpp"
    "nodes/scene.cpp"
    "renderer/gl/gl_buffers.cpp"
    "renderer/gl/gl_buffers.hpp"
    "renderer/gl/gl_camera.hpp"
    "renderer/gl/gl_lights.cpp"
    "renderer/gl/gl_lights.hpp"
    "renderer/gl/gl_program.cpp"
    "renderer/gl/gl_program.hpp"
    "renderer/gl/gl_programs.cpp"
    "renderer/gl/gl_programs.hpp"
    "renderer/gl/gl_renderer_impl.cpp"
    "renderer/gl/gl_renderer_impl.hpp"
    "renderer/gl/gl_state.cpp"
    "renderer/gl/gl_state.hpp"
    "renderer/gl/gl_textures.cpp"
    "renderer/gl/gl_textures.hpp"
    "renderer/gl/gl_uniform_buffer.cpp"
    "renderer/gl/gl_uniform_buffer.hpp"
    "renderer/gl/gl_uniform.cpp"
    "renderer/gl/gl_uniform.hpp"
    "resources/arrow.cpp"
    "resources/bounding_box.cpp"
    "resources/bounding_plane.cpp"
    "resources/bounding_sphere.cpp"
    "resources/grid.cpp"
    "resources/orbit_controls.cpp"
    "utilities/data_series.hpp"
    "utilities/file.hpp"
    "utilities/logger.cpp"
    "utilities/logger.hpp"
    "utilities/performance_graph.cpp"
    "utilities/performance_graph.hpp"
    "utilities/scoped_timer.hpp"
)

set(PUBLIC_HEADERS
    "${PUBLIC_HEADERS_DIR}/cameras/camera.hpp"
    "${PUBLIC_HEADERS_DIR}/cameras/orthographic_camera.hpp"
    "${PUBLIC_HEADERS_DIR}/cameras/perspective_camera.hpp"
    "${PUBLIC_HEADERS_DIR}/core/application_context.hpp"
    "${PUBLIC_HEADERS_DIR}/core/disposable.hpp"
    "${PUBLIC_HEADERS_DIR}/core/events.hpp"
    "${PUBLIC_HEADERS_DIR}/core/geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/core/identity.hpp"
    "${PUBLIC_HEADERS_DIR}/core/renderer.hpp"
    "${PUBLIC_HEADERS_DIR}/core/shared_context.hpp"
    "${PUBLIC_HEADERS_DIR}/core/timer.hpp"
    "${PUBLIC_HEADERS_DIR}/core/window.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/box_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/cone_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/cylinder_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/plane_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries/sphere_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/ambient_light.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/directional_light.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/light.hpp"
    "${PUBLIC_HEADERS_DIR}/lights/point_light.hpp"
    "${PUBLIC_HEADERS_DIR}/loaders/loader.hpp"
    "${PUBLIC_HEADERS_DIR}/loaders/mesh_loader.hpp"
    "${PUBLIC_HEADERS_DIR}/loaders/texture_loader.hpp"
    "${PUBLIC_HEADERS_DIR}/materials/flat_material.hpp"
    "${PUBLIC_HEADERS_DIR}/materials/material.hpp"
    "${PUBLIC_HEADERS_DIR}/materials/phong_material.hpp"
    "${PUBLIC_HEADERS_DIR}/materials/shader_material.hpp"
    "${PUBLIC_HEADERS_DIR}/math/box3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/color.hpp"
    "${PUBLIC_HEADERS_DIR}/math/euler.hpp"
    "${PUBLIC_HEADERS_DIR}/math/frustum.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix4.hpp"
    "${PUBLIC_HEADERS_DIR}/math/plane.hpp"
    "${PUBLIC_HEADERS_DIR}/math/sphere.hpp"
    "${PUBLIC_HEADERS_DIR}/math/transform2.hpp"
    "${PUBLIC_HEADERS_DIR}/math/transform3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/utilities.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector2.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector4.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/mesh.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/node.hpp"
    "${PUBLIC_HEADERS_DIR}/nodes/scene.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/arrow.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/bounding_box.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/bounding_plane.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/bounding_sphere.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/grid.hpp"
    "${PUBLIC_HEADERS_DIR}/resources/orbit_controls.hpp"
    "${PUBLIC_HEADERS_DIR}/textures/texture.hpp"
    "${PUBLIC_HEADERS_DIR}/textures/texture_2d.hpp"
)

set(HEADER_BUNDLES
    "${PUBLIC_HEADERS_DIR}/cameras.hpp"
    "${PUBLIC_HEADERS_DIR}/core.hpp"
    "${PUBLIC_HEADERS_DIR}/geometries.hpp"
    "${PUBLIC_HEADERS_DIR}/lights.hpp"
    "${PUBLIC_HEADERS_DIR}/loaders.hpp"
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

if(NOT_APPLE)
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

add_library(
    ${PROJECT_NAME}
    ${PUBLIC_HEADERS}
    ${HEADER_BUNDLES}
    ${SOURCE_CODE}
    ${EXTERNAL_SOURCES}
)

find_package(OpenGL REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

# disable RTTI and exceptions
target_compile_options(gleam PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:Clang>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:AppleClang>:-fno-rtti -fno-exceptions>
    $<$<CXX_COMPILER_ID:MSVC>:/GR /EHsc>
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/external>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tools>
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    OpenGL::GL
    glad::glad
    glfw
    imgui::imgui
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${gleam_VERSION_MAJOR}.${gleam_VERSION_MINOR}.${gleam_VERSION_PATCH}
    SOVERSION ${gleam_VERSION_MAJOR}
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${gleam_VERSION_MAJOR}.${gleam_VERSION_MINOR}.${gleam_VERSION_PATCH}
    COMPATIBILITY SameMajorVersion
)

set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
)

install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT {PROJECT_NAME}_runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT {PROJECT_NAME}_runtime
        NAMELINK_COMPONENT {PROJECT_NAME}_development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY "${PUBLIC_HEADERS_DIR}/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
    FILES_MATCHING PATTERN "*.hpp"
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/gleam_export.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CONFIG_INSTALL_DIR}
)

install(
    EXPORT ${PROJECT_NAME}
    DESTINATION ${CONFIG_INSTALL_DIR}
    NAMESPACE ${PROJECT_NAME}::
)