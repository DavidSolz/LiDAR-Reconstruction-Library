#!/bin/bash

set -e

BUILD_DIR="build"
GENERATOR="Unix Makefiles"

function usage {
    echo "Usage: $0 [clean]"
    echo "Options:"
    echo "  clean  Remove the build directory before building"
    exit 1
}

if [[ "$1" == "clean" ]]; then
    echo "Cleaning build directory..."
    rm -rf "$BUILD_DIR"
fi

if ! command -v cmake &> /dev/null; then
    echo "Error: CMake is not installed. Please install it and try again."
    exit 1
fi

echo "Configuring the project with CMake..."
cmake -G "$GENERATOR" -B "$BUILD_DIR" || {
    echo "Error: CMake configuration failed."
    exit 1
}

echo "Building the project..."
cmake --build "$BUILD_DIR" -j || {
    echo "Error: Build failed."
    exit 1
}

echo "Build completed successfully."
