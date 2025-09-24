#!/usr/bin/env sh

set -e  # Exit on error

BUILD_DIR=${1:-build}
DOCS_DIR="$BUILD_DIR/docs/html"

echo "Generating Doxygen documentation"

# Ensure build directory exists and CMake is configured
if [ ! -f "$BUILD_DIR/Makefile" ] && [ ! -f "$BUILD_DIR/build.ninja" ]; then
    echo "Configuring CMake"
    cmake -S . -B "$BUILD_DIR"
fi

# Build the Doxygen target
cmake --build "$BUILD_DIR" --target doxygen
python3 -m tools.doxy_press.main build/docs/xml docs/

# Verify output
if [ -f "$DOCS_DIR/index.html" ]; then
    echo "✅ Documentation generated at: $DOCS_DIR/index.html"
else
    echo "❌ Documentation generation failed: $DOCS_DIR/index.html not found."
    exit 1
fi