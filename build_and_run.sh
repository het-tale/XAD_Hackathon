#!/bin/bash

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Navigate to the build directory
cd build

# Run CMake to generate build files
cmake ..

# Build the project
cmake --build .

# Check if compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful, running program..."
    ./my_program
else
    echo "Compilation failed."
fi
