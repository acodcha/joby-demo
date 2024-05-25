# Copyright © 2023-2024 Alexandre Coderre-Chabot
#
# This file is part of Joby Demonstration, a simple demonstration of C++ principles in the context
# of a vehicle fleet simulation.
#
# Joby Demonstration is hosted at:
#     https://github.com/acodcha/joby-demo
#
# This file is licensed under the MIT license (https://mit-license.org). Permission is hereby
# granted, free of charge, to any person obtaining a copy of this software and associated
# documentation files (the "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#   - The above copyright notice and this permission notice shall be included in all copies or
#     substantial portions of the Software.
#   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
#     BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#     NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
#     DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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

add_executable(test-aggregate-statistics ${PROJECT_SOURCE_DIR}/test/AggregateStatistics.cpp)
target_link_libraries(test-aggregate-statistics PhQ GTest::gtest_main)
gtest_discover_tests(test-aggregate-statistics)

add_executable(test-charging-station ${PROJECT_SOURCE_DIR}/test/ChargingStation.cpp)
target_link_libraries(test-charging-station PhQ GTest::gtest_main)
gtest_discover_tests(test-charging-station)

add_executable(test-charging-stations ${PROJECT_SOURCE_DIR}/test/ChargingStations.cpp)
target_link_libraries(test-charging-stations PhQ GTest::gtest_main)
gtest_discover_tests(test-charging-stations)

add_executable(test-results-file-writer ${PROJECT_SOURCE_DIR}/test/ResultsFileWriter.cpp)
target_link_libraries(test-results-file-writer PhQ GTest::gtest_main)
gtest_discover_tests(test-results-file-writer)

add_executable(test-settings ${PROJECT_SOURCE_DIR}/test/Settings.cpp)
target_link_libraries(test-settings PhQ GTest::gtest_main)
gtest_discover_tests(test-settings)

add_executable(test-simulation ${PROJECT_SOURCE_DIR}/test/Simulation.cpp)
target_link_libraries(test-simulation PhQ GTest::gtest_main)
gtest_discover_tests(test-simulation)

add_executable(test-statistics ${PROJECT_SOURCE_DIR}/test/Statistics.cpp)
target_link_libraries(test-statistics PhQ GTest::gtest_main)
gtest_discover_tests(test-statistics)

add_executable(test-string ${PROJECT_SOURCE_DIR}/test/String.cpp)
target_link_libraries(test-string PhQ GTest::gtest_main)
gtest_discover_tests(test-string)

add_executable(test-vehicle ${PROJECT_SOURCE_DIR}/test/Vehicle.cpp)
target_link_libraries(test-vehicle PhQ GTest::gtest_main)
gtest_discover_tests(test-vehicle)

add_executable(test-vehicles ${PROJECT_SOURCE_DIR}/test/Vehicles.cpp)
target_link_libraries(test-vehicles PhQ GTest::gtest_main)
gtest_discover_tests(test-vehicles)

add_executable(test-vehicle-model ${PROJECT_SOURCE_DIR}/test/VehicleModel.cpp)
target_link_libraries(test-vehicle-model PhQ GTest::gtest_main)
gtest_discover_tests(test-vehicle-model)

add_executable(test-vehicle-models ${PROJECT_SOURCE_DIR}/test/VehicleModels.cpp)
target_link_libraries(test-vehicle-models PhQ GTest::gtest_main)
gtest_discover_tests(test-vehicle-models)
