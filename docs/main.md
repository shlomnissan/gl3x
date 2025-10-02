# GL3X

A fast real-time 3D rendering engine built with modern C++.

![ubuntu-badge](https://github.com/shlomnissan/gl3x/actions/workflows/ubuntu.yml/badge.svg)
![windows-badge](https://github.com/shlomnissan/gl3x/actions/workflows/windows.yml/badge.svg)
![macos-badge](https://github.com/shlomnissan/gl3x/actions/workflows/macos.yml/badge.svg)
[![docs-badge](https://img.shields.io/badge/docs-online-blue.svg)](https://shlomnissan.github.io/gl3x/)

GL3X is a lightweight, high-performance 3D rendering engine written in modern C++. It follows a clean, scene-oriented architecture that provides fine-grained control over rendering, lighting, and assets through a minimal and expressive API. Built for native performance and modularity, GL3X is ideal for interactive tools, visualization applications, and real-time rendering workflows that don't need the weight of a full game engine.

## Features

- Real-time forward renderer – Cameras, meshes, lighting, and materials supported out of the box.
- Cross-platform – Runs on Windows, macOS, and Linux with consistent behavior.
- Modern C++ architecture – Written in C++23 with strong typing and minimal overhead.
- Windowing and event system – Built-in support for input and context management.
- Flexible lighting system – Directional, point, and spot lights with attenuation support.
- Rich material system – Supports multiple shading models and user-defined shaders.
- Precompiled asset pipeline – Converts raw assets into optimized GPU-ready formats.
- Constexpr-first math – Header-only types and math utilities designed for compile-time use.
- Strong API boundaries – Internal symbols are hidden; public interface is clearly scoped.
- Comprehensive documentation – Grouped, consistent, and cross-linked via [Doxygen](https://doxygen.nl/).

## Getting Started

This section covers how to build GL3X, install it, and integrate it into your own project. GL3X is easy to consume: all dependencies are vendored, and no global packages are required.

### Requirements

GL3X requires a C++23-compatible toolchain, CMake 3.20 or newer, and an OpenGL 4.1+ context. It is actively tested on:

- ![Ubuntu](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/UBT.png) 24.04 and GCC 11.3.0
- ![macOS](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/MAC.png) macOS 14 and Clang 15.0.0
- ![Windows](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/WIN.png) Windows 10 and MSVC 19.44

### Dependencies

GL3X vendors all required libraries directly into the repository. The only runtime dependencies are:

| Dependency | Version  | Location        | Description |
|------------|----------|----------------|-------------|
| Glad   | 0.1.36   | `vendor/glad`  | OpenGL function loader generated from [glad.dav1d.de](https://glad.dav1d.de/). |
| GLFW   | 3.5.0    | `vendor/glfw`  | Cross-platform window/input/context management (with minor internal modifications). |
| ImGui  | 1.92.1   | `vendor/imgui` | Optional immediate-mode UI library for in-engine tools and examples. |

Each dependency includes license information in its respective `vendor/` folder. Additional libraries may be used in asset tooling but are not part of the engine runtime.

### Building GL3X

GL3X uses [CMake](https://cmake.org/download/) to configure and build the project. You can toggle build components using options or presets.

#### CMake Options

The following options control which components are built:

| Option                 | Description                                              |
|------------------------|----------------------------------------------------------|
| `GL3X_BUILD_DOCS`     | Build Doxygen documentation.                             |
| `GL3X_BUILD_EXAMPLES` | Build example applications.                              |
| `GL3X_BUILD_IMGUI`    | Enable ImGui support for debug UI/tools.                 |
| `GL3X_BUILD_TESTS`    | Build unit tests.                                        |
| `GL3X_BUILD_TOOLS`    | Build command-line.                                      |

Defaults are preset-dependent.

#### CMake Presets

To streamline the build process, GL3X provides a set of [CMake presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) with common configurations:

- `dev-debug` – Debug build with all features enabled.
- `dev-release` – Optimized build with tools and examples.
- `install-debug` – Debug build for install (used by MSVC).
- `install-release` – Optimized release build for install.

#### Build Instructions

```bash
# Clone the repository
git clone --recursive https://github.com/shlomnissan/gl3x.git
cd gl3x

# Create output directory
mkdir build
cd build

# Configure with a preset
cmake .. --preset dev-debug --config Debug

# Build the engine
cmake --build . --config Debug
```

If examples are enabled, you can run them to verify that everything is working as expected.

### Installation and Usage

GL3X can be installed via the provided script and integrated into your project using CMake’s standard `find_package` and `target_link_libraries` pattern. Alternatively, you can link GL3X manually by including headers and linking the compiled library directly.

#### Install Script

- macOS/Linux: `sudo scripts/install.sh`
- Windows (PowerShell as Admin): `scripts\install.bat`

The script uses the `install-release` preset on Unix. On MSVC, both `install-debug` and `install-release` are installed due to ABI differences. Elevated privileges are required in both cases. By default, GL3X is installed as a **shared library**. This enforces a clean API boundary and hides internal symbols using platform-specific visibility controls.

#### CMake Integration

```cmake
find_package(gl3x REQUIRED)
target_link_libraries(MyApp PRIVATE gl3x::gl3x)
```

CMake automatically selects the correct configuration (Debug/Release) based on your project settings.

#### Platform Notes

- GL3X disables RTTI by default. You can match this in your project:
  ```cmake
  target_compile_options(MyApp PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fno-rtti>
    $<$<CXX_COMPILER_ID:Clang>:-fno-rtti>
    $<$<CXX_COMPILER_ID:AppleClang>:-fno-rtti>
    $<$<CXX_COMPILER_ID:MSVC>:/GR->
  )
  ```
- On MSVC: You may need to copy the GL3X DLL next to your executable. Automate this with:
  ```cmake
  if(WIN32)
    add_custom_command(TARGET MyApp POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:gl3x::gl3x>
      $<TARGET_FILE_DIR:MyApp>
    )
  endif()
  ```

## Asset Generation Pipeline

GL3X does not parse raw assets at runtime. Instead, assets are preprocessed using asset_builder, a command-line tool built with `GL3X_BUILD_TOOLS`. It converts raw asset formats into compact, runtime-ready formats.

#### Supported Formats

| Input          | Output | Type    | Description |
|----------------|--------|---------|-------------|
| `.png`, `.jpg` | `.tex` | Texture | Converts 2D images into a GPU-ready format |
| `.obj`         | `.msh` | Mesh    | Converts geometry and material files for runtime loading |

#### Usage

```bash
asset_builder --input model.obj
asset_builder --input texture.png --output texture.tex
```

#### Building `asset_builder`

`asset_builder` is built by default with any CMake preset. If installed with GL3X, it will be available on the system `PATH` by default on Unix systems. On Windows, you may need to add it manually, for example: `$env:PATH += ";C:\path\to\gl3x\bin"` in PowerShell.

## License
```
 ________  ___      ________     ___    ___
|\   ____\|\  \    |\_____  \   |\  \  /  /|
\ \  \___|\ \  \   \|____|\ /_  \ \  \/  / /
 \ \  \  __\ \  \        \|\  \  \ \    / /
  \ \  \|\  \ \  \____  __\_\  \  /     \/
   \ \_______\ \_______\\_______\/  /\   \
    \|_______|\|_______\|_______/__/ /\ __\
                                |__|/ \|__|

Copyright (c) 2024–present Shlomi Nissan

The MIT License (MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```