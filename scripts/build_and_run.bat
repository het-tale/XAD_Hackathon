@echo off

REM Create a build directory if it doesn't exist
if not exist "build" (
    mkdir build
)

REM Navigate to the build directory
cd build

REM Run CMake to generate build files
cmake ..

REM Build the project
cmake --build .

REM Check if compilation succeeded
IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful, running program...
    my_program.exe
) ELSE (
    echo Compilation failed.
)
