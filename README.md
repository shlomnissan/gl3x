# Gleam

![ubuntu-badge](https://github.com/shlomnissan/gleam/actions/workflows/ubuntu.yml/badge.svg)
![windows-badge](https://github.com/shlomnissan/gleam/actions/workflows/windows.yml/badge.svg)
![macos-badge](https://github.com/shlomnissan/gleam/actions/workflows/macos.yml/badge.svg)
[![docs-badge](https://img.shields.io/badge/docs-online-blue.svg)](https://shlomnissan.github.io/gleam/)

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Getting Started](#getting-started)
   - [Requirements](#requirements)
   - [Dependencies](#dependencies)
   - [Build for Development](#build-for-development)
   - [Install and Integrate](#install-and-integrate)
- [Example]()
- [Documentation](https://shlomnissan.github.io/gleam/)
- [Asset Generation Pipeline]()
- [License](#license)

---

## Overview

Gleam is a lightweight, high-performance 3D rendering engine built with modern C++. Designed around a clean, scene-oriented architecture, it gives you low-level control over rendering, lighting, and assets through an expressive and minimal C++ API.

Written for native performance and modularity, Gleam is ideal for building real-time visual applications, interactive tools, and custom rendering workflows without the overhead of a full game engine.

## Features

- Real-time forward renderer – Supports cameras, meshes, materials, and lighting out of the box.
- Cross-platform – Runs on Windows, macOS, and Linux with consistent behavior across platforms.
- Modern C++ architecture – Written in C++23 with minimal runtime overhead and strong typing.
- Windowing and event system – Handles input, resizing, and context management natively.
- Flexible lighting system – Directional, point, and spot lights with attenuation and intensity support.
- Rich material system – Supports multiple material types and customizable shader behavior.
- Precompiled asset pipeline – Converts external formats into optimized runtime formats.
- Constexpr-first math library – Header-only vector and matrix types designed for compile-time use.
- Strict API boundary – Clean separation between internal systems and public interfaces.
- Comprehensive documentation – Consistently formatted with grouped sections and related symbols.

## Getting Started

This section covers how to build Gleam from source, install it, and integrate it into your own project. Gleam is designed to be easy to consume: all dependencies are vendored, and no system-wide packages are required.

### Requirements

Gleam requires a C++23-compatible toolchain, CMake 3.20 or newer, and an OpenGL 4.1+ context, and currently supports both Windows and Unix-based systems, with active testing on the following platforms:

- ![Ubuntu](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/UBT.png) 24.04 and GCC 11.3.0
- ![macOS](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/MAC.png) macOS 14 and Clang 15.0.0
- ![Windows](https://raw.githubusercontent.com/EgoistDeveloper/operating-system-logos/master/src/16x16/WIN.png) Windows 10 and MSVC 19.44

Other combinations may work, but are not regularly tested.

### Dependencies

Gleam vendors all of its dependencies directly into the repository—there’s no need to download or install anything manually. At runtime, it relies on only a minimal set of libraries to provide cross-platform windowing, input, OpenGL loading, and optional UI rendering. The following runtime dependencies are used:

| Dependency | Version  | Location        | Description |
|------------|----------|----------------|-------------|
| GLAD   | 0.1.36   | `vendor/glad`  | OpenGL function loader generated from [glad.dav1d.de](https://glad.dav1d.de/), configured for OpenGL 4.1 Core. |
| GLFW   | 3.5.0    | `vendor/glfw`  | Cross-platform window creation, input handling, and OpenGL context management. Slightly modified for internal integration. |
| ImGui  | 1.92.1   | `vendor/imgui` | Immediate-mode GUI library for in-engine UI and debugging tools. Included conditionally via the `GLEAM_BUILD_IMGUI` CMake option. |

Each dependency includes license information in the root of its respective `vendor/` folder. Additional dependencies may be used in the asset pipeline, but these are not part of the core Gleam runtime or linked into the engine binaries.

### Build for Development

Gleam uses [CMake](https://cmake.org/download/) to configure and build the project on all platforms. You can enable optional features like documentation, examples, tools, and tests using CMake options or presets designed for development workflows.

#### CMake Options

The following options control which components are built:

| Option                | Default | Description                                              |
|-----------------------|---------|----------------------------------------------------------|
| `GLEAM_BUILD_DOCS`     | `ON`   | Builds Doxygen documentation.                           |
| `GLEAM_BUILD_EXAMPLES` | `ON`   | Builds example applications.                            |
| `GLEAM_BUILD_IMGUI`    | `ON`   | Enables ImGui support (required by some examples/tools). |
| `GLEAM_BUILD_TESTS`    | `ON`   | Builds unit tests.                                      |
| `GLEAM_BUILD_TOOLS`    | `ON`   | Builds command-line asset tools.                        |

#### Development Presets

To streamline development, Gleam provides a set of [CMake presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) with common configurations:

- `dev-debug` – Debug build with all features enabled (tests, tools, ImGui, examples)
- `dev-release` – Optimized build with tools and examples (useful for performance benchmarking)
- `install-debug` – Debug build for installation (used with MSVC for debug integration).
- `install-release` – Optimized build for installation (optimized release).

#### Build Instructions

1. Clone the repository:

<pre>
/$ git clone https://github.com/shlomnissan/gleam.git
/$ cd gleam
</pre>

2. Configure the project using a preset:

<pre>
/$ cmake --preset dev-debug
</pre>

3. Build the engine:

<pre>
/$ cmake --build out/dev-debug --config Debug
</pre>

If you use a development preset or enable `GLEAM_BUILD_EXAMPLES`, you can run the examples target application to verify that everything is working correctly.

### Install and Integrate

Gleam can be installed using the provided script and then integrated into your own CMake-based project using standard `find_package` and `target_link_libraries` semantics.

## License
```
      ___           ___       ___           ___           ___
     /\  \         /\__\     /\  \         /\  \         /\__\
    /::\  \       /:/  /    /::\  \       /::\  \       /::|  |
   /:/\:\  \     /:/  /    /:/\:\  \     /:/\:\  \     /:|:|  |
  /:/  \:\  \   /:/  /    /::\~\:\  \   /::\~\:\  \   /:/|:|__|__
 /:/__/_\:\__\ /:/__/    /:/\:\ \:\__\ /:/\:\ \:\__\ /:/ |::::\__\
 \:\  /\ \/__/ \:\  \    \:\~\:\ \/__/ \/__\:\/:/  / \/__/~~/:/  /
  \:\ \:\__\    \:\  \    \:\ \:\__\        \::/  /        /:/  /
   \:\/:/  /     \:\  \    \:\ \/__/        /:/  /        /:/  /
    \::/  /       \:\__\    \:\__\         /:/  /        /:/  /
     \/__/         \/__/     \/__/         \/__/         \/__/

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
