set(GLAD_SOURCES
    "glad.c"
)

set(GLAD_HEADERS
    "glad/glad.h"
    "KHR/khrplatform.h"
)

add_library(glad STATIC ${GLAD_SOURCES} ${GLAD_HEADERS})

target_include_directories(glad PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(TARGETS glad EXPORT gleam)