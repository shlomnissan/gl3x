set(PUBLIC_HEADERS_DIR ${CMAKE_SOURCE_DIR}/include)

set(SOURCE_CODE
    "core/window.cpp"
    "math/matrix3.cpp"
    "math/matrix4.cpp"
    "math/matrix_transform.cpp"
    "math/projection.cpp"
    "math/vector3.cpp"
    "math/vector4.cpp"
)

set(PUBLIC_HEADERS
    "${PUBLIC_HEADERS_DIR}/core/window.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix4.hpp"
    "${PUBLIC_HEADERS_DIR}/math/matrix_transform.hpp"
    "${PUBLIC_HEADERS_DIR}/math/projection.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector3.hpp"
    "${PUBLIC_HEADERS_DIR}/math/vector4.hpp"
)

add_library(${PROJECT_NAME} ${SOURCE_CODE})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
)

if (BUILD_SHARED_LIBS)
    set_target_properties(${TARGET_NAME} PROPERTIES
        VERSION ${engine_VERSION_MAJOR}.${engine_VERSION_MINOR}.${engine_VERSION_PATCH}
        SOVERSION ${engine_VERSION_MAJOR}
    )
endif()

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})