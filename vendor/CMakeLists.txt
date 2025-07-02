add_subdirectory("glad")
add_subdirectory("glfw")

if (GLEAM_BUILD_IMGUI)
    add_subdirectory("imgui")
endif()