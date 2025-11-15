# Installation

This page covers how to build VGLX, install it, and use it in your own project. The goal is to keep things simple. All dependencies are included in the repository, and you do not need to install anything system-wide beyond a compiler, CMake and an OpenGL driver.

## Requirements


VGLX builds with a C++23-capable toolchain, [CMake](https://cmake.org/) 3.20 or newer, and an OpenGL 4.1+ context. It is regularly tested on the major platforms:

<div class="system-list">

- ![Ubuntu](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/UBT.png) Ubuntu 24.04 (GCC 11.3.0)
- ![macOS](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/MAC.png) macOS 14 (Clang 15.0.0)
- ![Windows](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/WIN.png) Windows 10 and MSVC 19.44

</div>

#### Dependencies

VGLX vendors everything it needs directly into the repository. There is no package manager setup and no extra system installs. The only runtime pieces are:

| Dependency | Version  | Location        | Description |
|------------|----------|----------------|-------------|
| [Glad](https://glad.dav1d.de/)   | 0.1.36   | `vendor/glad`  | OpenGL function loader generated from [glad.dav1d.de](https://glad.dav1d.de/). |
| [GLFW](https://glfw.org/)   | 3.5.0    | `vendor/glfw`  | Cross-platform window/input/context management (with minor internal modifications). |
| [ImGui](https://github.com/ocornut/imgui)  | 1.92.1   | `vendor/imgui` | **Optional** immediate-mode UI library for in-engine tools and examples. |

Each dependency includes its license inside the `vendor/` directory.

## VGLX Installer

#### Verify Installation

## Build Instructions

VGLX uses CMake for configuration. You can build it however you prefer, but the presets included with the project make things easier.

A few common CMake presets are provided:
- `dev-debug` – Debug build with everything enabled
- `dev-release` – Optimized build with examples and tools
- `install-debug` – Debug install target (MSVC)
- `install-release` – Release install target

```bash [bash]
# clone the repository
git clone --recursive https://github.com/shlomnissan/vglx.git
cd vglx

# optional but recommended
mkdir build
cd build

# configure with a preset
cmake .. --preset dev-debug --config Debug

# build the engine
cmake --build . --config Debug
```
#### Configuration Options

VGLX includes several optional build components. If you want to customize what gets built, you can enable or disable features using CMake options:

| Option                      | Description                                              |
|-----------------------------|----------------------------------------------------------|
| `VGLX_BUILD_DOCS`           | Build Doxygen documentation.                             |
| `VGLX_BUILD_EXAMPLES`       | Build example applications.                              |
| `VGLX_BUILD_IMGUI`          | Enable ImGui support for debug UI/tools.                 |
| `VGLX_BUILD_TESTS`          | Build unit tests.                                        |
| `VGLX_BUILD_ASSET_BUILDER`  | Build asset builder CLI tool                             |

VGLX builds and installs as a shared library by default which keeps the API boundary clean and prevents leaking internal symbols. If you want to build a static library use the built-in CMake option `BUILD_SHARED_LIBS=OFF`.