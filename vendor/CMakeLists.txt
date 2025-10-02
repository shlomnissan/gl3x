add_subdirectory("glad")
add_subdirectory("glfw")

if (GL3X_BUILD_IMGUI)
    add_subdirectory("imgui")
endif()