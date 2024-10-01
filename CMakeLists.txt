# Require CMake version 3.16 or higher
cmake_minimum_required(VERSION 3.16)

# Define the project name, version, and programming language (C++)
project(MatricesAndViewsChallenge VERSION 1.0 LANGUAGES CXX)

# Specify source files for the executable
set(SOURCES main.cpp Matrix.cpp)

# Set C++ standard to C++17 and require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create an executable named "myapp" from the source files
add_executable(my_program ${SOURCES})
