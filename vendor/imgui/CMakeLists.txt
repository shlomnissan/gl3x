set(IMGUI_SOURCES
    "imgui_draw.cpp"
    "imgui_tables.cpp"
    "imgui_widgets.cpp"
    "imgui.cpp"
)

set(IMGUI_HEADERS
    "imconfig.h"
    "imgui_internal.h"
    "imgui.h"
    "imstb_rectpack.h"
    "imstb_textedit.h"
    "imstb_truetype.h"
)

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})

target_include_directories(imgui PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(imgui PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

install(TARGETS imgui EXPORT gl3x)