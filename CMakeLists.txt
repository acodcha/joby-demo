cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Define the C++ and build settings.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math -O3 -Wall -Wno-return-type")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_BUILD_TYPE Release)

# Define the CMake project and its options.
project(
  "joby-demo" VERSION 1.0.0 LANGUAGES CXX
  DESCRIPTION "Simple demonstration of C++ principles in the context of a vehicle fleet simulation."
  HOMEPAGE_URL "https://github.com/acodcha/joby-demo"
)
option(BUILD_TESTING "Build the tests." OFF)

# Build the main executable.
set(JOBY_DEMO_EXECUTABLE_NAME "joby-demo")
add_executable(${JOBY_DEMO_EXECUTABLE_NAME} source/Main.cpp)
target_link_libraries(${JOBY_DEMO_EXECUTABLE_NAME})

# Build the tests.
if(BUILD_TESTING)
  # Download the GoogleTest library.
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
  )

  # Do not override the parent project's compiler and linker settings on Windows.
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  # Include the GoogleTest library and enable testing.
  FetchContent_MakeAvailable(googletest)
  include(GoogleTest)
  enable_testing()

  add_executable(test-simple ${PROJECT_SOURCE_DIR}/test/Simple.cpp)
  target_link_libraries(test-simple GTest::gtest_main)
  gtest_discover_tests(test-simple)

  message(STATUS "Testing was configured. Build the testing executables with \"make --jobs=16\" and run them with \"make test\"")
else()
  message(STATUS "Testing was not configured. Run \"cmake .. -DBUILD_TESTING=ON\" to configure testing.")
endif()
