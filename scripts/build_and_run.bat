@echo off

REM Create a build directory if it doesn't exist
if not exist "build" (
    mkdir build
)

REM Navigate to the build directory
cd build

REM Run CMake to generate build files
cmake -S .. -B .

REM Build the project
cmake --build .

SET TEST_MODE=false
IF "%1"=="--test" SET TEST_MODE=true

REM Check if compilation succeeded
IF %ERRORLEVEL% EQU 0 (
    IF "%TEST_MODE%"=="false" (
        echo Compilation successful, running program...
        my_program.exe
    ) ELSE (
        echo Test mode activated...
        ctest
    )
) ELSE (
    echo Compilation failed.
)
