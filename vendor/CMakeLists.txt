add_subdirectory("glad")
add_subdirectory("glfw")

if (VGLX_BUILD_IMGUI)
    add_subdirectory("imgui")
endif()