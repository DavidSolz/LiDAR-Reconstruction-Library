#!/bin/bash

if [ ! -d build ]; then
    echo "Error: Build directory does not exist. Please build the project before running tests."
    exit 1
fi

if ! command -v ctest &> /dev/null; then
    echo "Error: ctest command not found. Please install CMake to use ctest."
    exit 1
fi

TEST_DIR="./build/tests"
if [ ! -d "$TEST_DIR" ]; then
    echo "Error: Test directory '$TEST_DIR' not found. Ensure tests are properly configured and built."
    exit 1
fi

echo "Running tests from '$TEST_DIR'..."
ctest --test-dir "$TEST_DIR" --output-on-failure -- -s

if [ $? -ne 0 ]; then
    echo "Error: Some tests failed. Check the output above for details."
    exit 1
fi

echo "All tests passed successfully."
