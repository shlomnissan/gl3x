# Making a Scene

If you followed the [installation guide](/manual/installation) and verified your setup you are ready to build your first scene. This page walks you through writing a minimal VGLX application and assembling a simple world from a few core pieces. The example is small on purpose. It introduces the fundamentals without burying you in details.

By the end you’ll have a working scene and a clear sense of how the engine fits together, enough to [start exploring](/reference/core/application) and building on your own.

## Creating a Project

VGLX works best with [CMake](https://cmake.org/). In this section we create a small project so it can build cleanly on all platforms. To keep things simple we use a flat directory with just two files:

```text
➜ hello-vglx
.
├── CMakeLists.txt
└── main.cpp
```

`CMakeLists.txt` holds a small build configuration:

```cmake
cmake_minimum_required(VERSION 3.20)

project(hello-vglx)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello-vglx main.cpp)

find_package(vglx REQUIRED)

target_link_libraries(hello-vglx PRIVATE vglx::vglx)

if (WIN32)
    add_custom_command(TARGET hello-vglx POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:vglx::vglx>
        $<TARGET_FILE_DIR:hello-vglx>
    )
endif()
```

The file starts by declaring the minimum CMake version, the project name and the language standard. We then create an executable and give it a single source file.

If you followed the installation guide you can import VGLX with two commands. `find_package(vglx REQUIRED)` asks CMake to locate the library. If it is missing or incorrectly installed, configuration fails. `target_link_libraries` links our application to the VGLX binaries.

The Windows block copies the VGLX DLL next to the executable after the build step. CMake selects the correct binary automatically based on your build type.

This looks simple but CMake is doing a lot behind the scenes. It checks the installation, pulls in the right configuration, and takes care of platform quirks for us.

Our only source file stays true to the K&R tradition:

```cpp
#include <print>
#include <vglx/vglx.hpp>

auto main() -> int {
    std::println("hello, world");
    return 0;
}
```

With `CMakeLists.txt` and `main.cpp` in place you can configure and build the project.

From the project root:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

After the build completes you should see the executable in the build directory.
- Linux/macOS: `build/hello-vglx`
- Windows: `build/Debug/hello-vglx.exe`

Run it and you should be greeted by your application.

If CMake reports that it cannot find `vglx`, return to the installation guide and verify that the library was installed to a prefix CMake can locate.

## Application Entrypoint