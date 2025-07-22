# Gleam

![ubuntu-badge](https://github.com/shlomnissan/gleam/actions/workflows/ubuntu.yml/badge.svg)
![windows-badge](https://github.com/shlomnissan/gleam/actions/workflows/windows.yml/badge.svg)
![macos-badge](https://github.com/shlomnissan/gleam/actions/workflows/macos.yml/badge.svg)
[![docs-badge](https://img.shields.io/badge/docs-online-blue.svg)](https://shlomnissan.github.io/gleam/)

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