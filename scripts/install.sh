#!/bin/bash

# Set default triplet value
triplet="x64-linux-release"

# Check if a triplet is provided as an argument
if [ "$1" != "" ]; then
    triplet="$1"
fi

# Determine the script's location
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Move to the root directory (parent of the "scripts" folder)
cd "$script_dir/.." || exit 1

# Check if the "release" folder exists, and remove it if it does
if [ -d "release" ]; then
    echo "Removing existing 'release' folder"
    rm -rf release || { echo "Failed to remove 'release' folder"; exit 1; }
fi

# Create the "release" folder
echo "Creating 'release' folder"
mkdir release || { echo "Failed to create 'release' folder"; exit 1; }
cd release

# Configure the project
echo "Running CMake configuration with triplet: $triplet"
cmake .. --preset "release" -DVCPKG_TARGET_TRIPLET="$triplet" || {
    echo "CMake configuration failed";
    exit 1;
}

# Build the project
echo "Building the project"
cmake --build . --config Release || { echo "Build failed"; exit 1; }

# Install the project
echo "Installing the project"
sudo cmake --install . || { echo "Installation failed"; exit 1; }

# Completion message
echo "Installation complete!"