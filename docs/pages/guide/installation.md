# Installation

This guide walks you through installing VGLX so you can start using it right away.

::: details Quick Start
If you just want to build and run VGLX quickly, you can use the following commands:

```bash
# Clone the repository
git clone --recursive https://github.com/shlomnissan/vglx.git
cd vglx && mkdir build && cd build

# Configure with the debug preset
cmake .. --preset dev-debug --config Debug

# Build the engine
cmake --build . --config Debug
```
:::

## Requirements

Before building VGLX, make sure your system meets the following requirements:
- **C++ compiler** with support for **C++23**
  - GCC 11+, Clang 14+, or MSVC 2022 recommended
- **CMake** version **3.20 or later**
- A supported operating system: **macOS**, **Linux**, or **Windows**

## Using CMake

VGLX depends on [CMake](https://cmake.org/) version 3.20 or later for configuration, building, and installation. You’ll also use CMake to integrate VGLX into your own applications.

Before continuing, make sure CMake is installed on your system:

- **macOS** — Install with [Homebrew](https://brew.sh/)
  ```bash
  brew install cmake
  ```
- **Linux** — Use your distribution’s package manager:
  ```bash
  sudo apt install cmake   # Ubuntu/Debian
  sudo dnf install cmake   # Fedora
  ```
- **Windows** — Download the latest installer from the [official CMake website](https://cmake.org/download/)
 and follow the setup wizard.

Once installed, verify your setup by running:

```bash
cmake --version
```
You should see the installed version number, which must be **3.20 or higher**.

> [!NOTE]
> If your package manager provides an older version, install from source or use a prebuilt release from [cmake.org](https://cmake.org/)

## Building VGLX

After installing the requirements, you’re ready to build the project. VGLX provides both CMake options to toggle features and CMake presets to streamline common configurations.

### Options

| Option                 | Description                                              |
|------------------------|----------------------------------------------------------|
| `VGLX_BUILD_DOCS`     | Build Doxygen documentation.                             |
| `VGLX_BUILD_EXAMPLES` | Build example applications.                              |
| `VGLX_BUILD_IMGUI`    | Enable ImGui support for debug UI/tools.                 |
| `VGLX_BUILD_TESTS`    | Build unit tests.                                        |
| `VGLX_BUILD_TOOLS`    | Build command-line tools.                                |

Default values depend on the selected preset.

### Presets

For convenience, VGLX includes presets with common build configurations:
- **dev-debug** — Debug build with all features enabled
- **dev-release** — Optimized build with tools and examples
- **install-debug** — Debug build prepared for installation (used by MSVC)
- **install-release** — Optimized release build prepared for installation

### Build Instructions

```bash
# Clone the repository
git clone --recursive https://github.com/shlomnissan/vglx.git
cd vglx

# Create a build directory
mkdir build
cd build

# Configure with a preset
cmake .. --preset dev-debug --config Debug

# Build the engine
cmake --build . --config Debug
```
If you built with examples enabled, try running them to make sure everything works. You should see the examples application launch.

![Examples application screenshot](/examples-screenshot.png "Examples running with VGLX")

> [!TIP]
> If everything built correctly, the examples application window should appear.

### Custom Builds

You can also configure the project manually by passing options directly to CMake:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DVGLX_BUILD_TESTS=OFF
cmake --build .
```
This approach is useful if you want full control over which components are enabled, or if you’re not using the provided presets.

## Installing VGLX

Once you’ve built VGLX, you can install it system-wide and integrate it into your own projects. Installation can be done using the provided scripts, after which VGLX is discoverable through CMake’s standard `find_package` and `target_link_libraries` workflow. If you prefer, you can also integrate VGLX manually by adding its headers and linking the compiled library directly.

### Install scripts
Run the install script for your platform:
- **macOS / Linux**
  ```bash
  sudo scripts/install.sh
  ```
- **Windows (PowerShell as Administrator)**
  ```powershell
  scripts\install.bat
  ```

On Unix systems, the script uses the `install-release` preset. On MSVC, both `install-debug` and `install-release` are installed to handle ABI differences. Elevated privileges are required in both cases.

By default, VGLX installs as a shared library, which enforces a clean API boundary and hides internal symbols using platform-specific visibility controls.

## Using VGLX in your project

Once installed, you can use VGLX in your own project with:

```cmake
find_package(vglx REQUIRED)
target_link_libraries(MyApp PRIVATE vglx::vglx)
```

CMake automatically selects the correct configuration (Debug or Release) based on your project’s build settings.

### Manual integration (without CMake)

You can also integrate VGLX manually if you compile your projects from the command line (or outside of CMake). For example, using **g++**:

```bash
g++ -std=c++23 -O2 main.cpp -o MyApp -lvglx
```

If you installed VGLX using the provided CMake install script, its headers and libraries are already placed on your system paths, so no extra `-I` or `-L` flags are required.

## Platform Notes

- **RTTI**
  VGLX disables [RTTI](https://en.cppreference.com/w/cpp/utility/rtti.html) by default. To match this setting in your CMake project, add:
  ```cmake
  target_compile_options(MyApp PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-fno-rtti>
    $<$<CXX_COMPILER_ID:Clang>:-fno-rtti>
    $<$<CXX_COMPILER_ID:AppleClang>:-fno-rtti>
    $<$<CXX_COMPILER_ID:MSVC>:/GR->
  )
  ```
- **Windows DLLs**
  On MSVC, you may need to copy the VGLX DLL next to your executable. Automate this with:
  ```cmake
  if(WIN32)
    add_custom_command(TARGET MyApp POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_FILE:vglx::vglx>
      $<TARGET_FILE_DIR:MyApp>
    )
  endif()
  ```