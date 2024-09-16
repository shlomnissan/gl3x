set(PUBLIC_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include)

set(SOURCE_CODE
    "core/disposable.hpp"
    "core/disposable.cpp"
    "core/geometry.cpp"
    "core/renderer.cpp"
    "core/timer.cpp"
    "core/window.cpp"
    "core/window_impl.cpp"
    "core/window_impl.hpp"
    "geometry/plane_geometry.cpp"
    "geometry/box_geometry.cpp"
    "math/euler.cpp"
    "math/utilities.cpp"
    "math/matrix3.cpp"
    "math/matrix4.cpp"
    "math/transform.cpp"
    "math/transformations.cpp"
    "math/vector3.cpp"
    "math/vector4.cpp"
    "renderer/gl/gl_bindings.cpp"
    "renderer/gl/gl_bindings.hpp"
    "renderer/gl/gl_program.cpp"
    "renderer/gl/gl_program.hpp"
    "renderer/gl/gl_renderer_impl.cpp"
    "renderer/gl/gl_renderer_impl.hpp"
    "scene/camera.cpp"
    "scene/camera_orthographic.cpp"
    "scene/camera_perspective.cpp"
    "scene/mesh.cpp"
    "scene/node.cpp"
    "scene/scene.cpp"
)

set(PUBLIC_HEADERS
    "${PUBLIC_HEADERS_DIR}/core/geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/core/renderer.hpp"
    "${PUBLIC_HEADERS_DIR}/core/timer.hpp"
    "${PUBLIC_HEADERS_DIR}/core/window.hpp"
    "${PUBLIC_HEADERS_DIR}/geometry/plane_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/geometry/box_geometry.hpp"
    "${PUBLIC_HEADERS_DIR}/math/euler.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix4.hpp"
    "${PUBLIC_HEADERS_DIR}/math/transform.hpp"
    "${PUBLIC_HEADERS_DIR}/math/transformations.hpp"
    "${PUBLIC_HEADERS_DIR}/math/utilities.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector4.hpp"
    "${PUBLIC_HEADERS_DIR}/scene/camera.hpp"
    "${PUBLIC_HEADERS_DIR}/scene/camera_orthographic.hpp"
    "${PUBLIC_HEADERS_DIR}/scene/camera_perspective.hpp"
    "${PUBLIC_HEADERS_DIR}/scene/mesh.hpp"
    "${PUBLIC_HEADERS_DIR}/scene/node.hpp"
    "${PUBLIC_HEADERS_DIR}/scene/scene.hpp"
)

include(ShaderString)

add_library(${PROJECT_NAME} ${SOURCE_CODE})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    fmt::fmt
    glad::glad
    glfw
)

if (BUILD_SHARED_LIBS)
    set_target_properties(${TARGET_NAME} PROPERTIES
        VERSION ${engine_VERSION_MAJOR}.${engine_VERSION_MINOR}.${engine_VERSION_PATCH}
        SOVERSION ${engine_VERSION_MAJOR}
    )
endif()

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})