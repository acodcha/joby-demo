# Joby Demonstration

Simple demonstration of C++ principles in the context of a vehicle fleet simulation.

The following packages are required:

- **C++ Compiler:** Any C++ compiler with support for the C++17 standard will do, such as recent versions of GCC or Clang. On Ubuntu, install GCC with `sudo apt install g++` or Clang with `sudo apt install clang`.
- **CMake:** Any sufficiently-recent version of CMake will do. On Ubuntu, install CMake with `sudo apt install cmake`.

This project makes use of the GoogleTest library (<https://github.com/google/googletest>) and the Physical Quantities library (<https://github.com/acodcha/physical-quantities>). These libraries are automatically downloaded, built, and linked to this project whenever this project is built.

Clone this repository and build this project with:

```bash
git clone git@github.com:acodcha/joby-demo.git
cd joby-demo
mkdir build
cd build
cmake ..
make --jobs=16
```

This builds the `build/bin/joby-demo` main executable and the testing executables.

Run the main executable from the `build` directory with:

```bash
bin/joby-demo
```

You can also optionally run this project's tests from the `build` directory with:

```bash
make test
```

This builds and runs the tests.

This project is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT License. For more details, see the [LICENSE](LICENSE) file or <https://mit-license.org/>.
