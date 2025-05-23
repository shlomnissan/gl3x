# Asset Compiler

**asset_compiler** is a command-line tool for converting raw asset files into engine-optimized formats like `.texture` and `.mesh`. It’s designed for integration into asset pipelines, supporting both manual and automated workflows.

## Features

- ✅ Converts `.png` and `.jpg` images into `.texture` files
- 🔜 Extendable to support additional asset types and conversion options
- 🔒 Consistent output format for fast, runtime-friendly loading

## Usage

```bash
asset_compiler <input_file> <output_file>
```

## Supported Formats

| Input Extension | Output Extension | Asset Type | Description                      |
|-----------------|------------------|------------|----------------------------------|
| `.png`, `.jpg`          | `.texture`       | Texture    | Converts 2D images into GPU-ready texture format |

## Building

```bash
git clone https://github.com/shlomnissan/engine
cd engine\tools\asset_compiler
mkdir release
cd release
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release --target install
```

> Requires CMake 3.20+ and a C++23-compatible compiler.

## Integration
Once installed, ensure the executable is available in your `PATH`:

```bash
# Example on Windows PowerShell
$env:PATH += ";C:\path\to\asset_compiler\bin"
```

This allows `asset_compiler` to be invoked from PowerShell, build scripts, or GUI tools.
