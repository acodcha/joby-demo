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

# Define a simple test.
add_executable(test-simple ${PROJECT_SOURCE_DIR}/test/Simple.cpp)
target_link_libraries(test-simple PhQ GTest::gtest_main)
gtest_discover_tests(test-simple)
