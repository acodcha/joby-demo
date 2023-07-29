# Copyright © 2023 Alexandre Coderre-Chabot
#
# This file is licensed under the MIT license. For more information, visit:
#     https://mit-license.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#   - The above copyright notice and this permission notice shall be included in
#     all copies or substantial portions of the Software.
#   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#     FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#     DEALINGS IN THE SOFTWARE.
#
# This file was originally obtained from:
#     https://github.com/acodcha/joby-demo

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define the global settings.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -O3 -Wall -Wno-return-type")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)

# Define the project.
project(
  "JobyDemo" VERSION 1.0.0 LANGUAGES CXX
  DESCRIPTION "Simple demonstration of C++ principles in the context of a vehicle fleet simulation."
  HOMEPAGE_URL "https://github.com/acodcha/joby-demo"
)

# Download and setup the PhQ library.
include(FetchContent)
FetchContent_Declare(
  PhQ
  GIT_REPOSITORY https://github.com/acodcha/physical-quantities.git
  GIT_TAG main
)
FetchContent_MakeAvailable(PhQ)

# Define the main executable.
add_executable(joby-demo ${PROJECT_SOURCE_DIR}/source/Main.cpp)
target_link_libraries(joby-demo PUBLIC PhQ)

# Download the GoogleTest library.
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG main
)

# Do not override the parent project's compiler and linker settings on Windows.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include the GoogleTest library and enable testing.
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
enable_testing()

# Define tests.

add_executable(test-vehicle-model ${PROJECT_SOURCE_DIR}/test/VehicleModel.cpp)
target_link_libraries(test-vehicle-model PhQ GTest::gtest_main)
gtest_discover_tests(test-vehicle-model)
