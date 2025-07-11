#!/bin/bash

# Determine the script's location
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$script_dir/.." || exit 1

# Remove old install directory
if [ -d "out/install-release" ]; then
    echo "Cleaning previous install builds..."
    rm -rf "out/install-release" || { echo "Failed to remove old install dir"; exit 1; }
fi

# Install release build
echo "Building Release (install-release)"

cmake --preset install-release || {
    echo "CMake configuration failed"
    exit 1
}

cmake --build out/install-release || {
    echo "CMake build failed"
    exit 1
}

cmake --install out/install-release || {
    echo "CMake install failed"
    exit 1
}

# Done
echo "Installation complete"