# Joby Demonstration

Simple demonstration of C++ principles in the context of a vehicle fleet simulation.

The following packages are required:

- **C++17 Compiler:** Any C++17 compiler will do, such as GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** On Ubuntu, install with `sudo apt install cmake`.

Clone this repository with:

```bash
git clone git@github.com:acodcha/joby-demo.git
cd joby-demo
```

Build the main executable with:

```bash
mkdir build
cd build
cmake ..
make --jobs=16
```

This builds the `build/bin/joby-demo` executable.

Run the main executable from the `build` directory with:

```bash
bin/joby-demo
```

You can optionally build and run tests from the `build` directory with:

```bash
cmake .. -DBUILD_TESTING=ON
make --jobs=16
make test
```

This builds and runs the unit tests. The GoogleTest library (<https://github.com/google/googletest>) is used for testing. When testing is enabled, the GoogleTest library is downloaded, compiled, and linked to this project.

This work is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT License. For more details, see the [LICENSE](LICENSE) file or <https://mit-license.org/>.
