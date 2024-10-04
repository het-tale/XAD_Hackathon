# Require CMake version 3.16 or higher
cmake_minimum_required(VERSION 3.16)

# Define the project name, version, and programming language (C++)
project(MatricesAndViewsChallenge VERSION 1.0 LANGUAGES CXX)

# Specify source files for the executable
set(SOURCES Matrix.cpp benchmark\ code/Listing_1.cpp benchmark\ code/Listing_2.cpp benchmark\ code/Listing_3.cpp main.cpp MatrixView.cpp fornebius.cpp)

# Set C++ standard to C++17 and require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create an executable named "myapp" from the source files
add_executable(my_program ${SOURCES})

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES src/matrix_test.cpp src/Matrix.cpp)
add_executable(
  all_tests
  ${TEST_SOURCES}
)
target_link_libraries(
  all_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(all_tests)
