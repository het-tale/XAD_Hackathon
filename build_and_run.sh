#!/bin/bash

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Navigate to the build directory
cd build

# Run CMake to generate build files
cmake -S .. -B . 

# Build the project
cmake --build .

TEST_MODE=false
if [[ "$#" -gt 0 ]]; then
    case $1 in
    --test)
        TEST_MODE=true
        ;;
    esac
fi
# Check if compilation succeeded
if [ "$TEST_MODE" = false ]; then
    if [ $? -eq 0 ]; then
        echo "Compilation successful, running program..."
        ./my_program
    else
        echo "Compilation failed."
    fi
else
    echo "test activated..."
    ctest
fi
