# Joby Demonstration

[![build and test](https://github.com/acodcha/joby-demo/actions/workflows/build_and_test.yaml/badge.svg?branch=main)](https://github.com/acodcha/joby-demo/actions/workflows/build_and_test.yaml)

Simple demonstration of C++ principles in the context of a vehicle fleet simulation.

- [Configuration](#configuration)
- [Usage](#usage)
- [Results](#results)
- [Testing](#testing)
- [License](#license)

## Configuration

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

This builds the `build/bin/joby-demo` executable and the tests.

## Usage

Print usage information to the console by running the main executable from the `build` directory with:

```bash
bin/joby-demo --help
```

Run a simulation by running the main executable from the `build` directory with:

```bash
bin/joby-demo --vehicles <number> --charging-stations <number> --duration-hours <number> [--results <path>] [--random-seed <number>]
```

The command-line arguments are:

- `--vehicles <number>`: Number of vehicles in the simulation. Required.
- `--charging-stations <number>`: Number of charging stations in the simulation. Required.
- `--duration-hours <number>`: Time duration of the simulation in hours. Required.
- `--results <path>`: Path to the results file to be written. Optional. If omitted, simulation results are not written.
- `--random-seed <number>`: Seed value for pseudo-random number generation. Optional. If omitted, the seed value is randomized.

## Results

The following command runs a simulation that contains 20 vehicles, features 3 charging stations, lasts 3.0 hours, writes to `results.dat`, and uses a random seed value:

```bash
bin/joby-demo --vehicles 20 --charging-stations 3 --duration-hours 3.0 --results results.dat
```

A sample console log and results file from such a run are located in the `results` directory:

- [results/results.dat](results/results.dat)
- [results/log.txt](results/log.txt)

Note that rerunning this command produces different results each time due to the random seed value.

## Testing

This project's tests can be optionally run from the `build` directory with:

```bash
make test
```

This runs the tests.

## License

This project is maintained by Alexandre Coderre-Chabot (<https://github.com/acodcha>) and licensed under the MIT License. For more details, see the [LICENSE](LICENSE) file or <https://mit-license.org/>.
