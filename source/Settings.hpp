// Copyright 2023 Alexandre Coderre-Chabot
//
// This file is licensed under the MIT license. For more information, visit:
//     https://mit-license.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included
//     in all copies or substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//     OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
//     NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//     DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
//     OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
//     USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This file was originally obtained from:
//     https://github.com/acodcha/joby-demo

#ifndef DEMO_INCLUDE_SETTINGS_HPP
#define DEMO_INCLUDE_SETTINGS_HPP

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <optional>
#include <PhQ/Time.hpp>
#include <string>
#include <vector>

#include "Arguments.hpp"
#include "Program.hpp"
#include "String.hpp"

namespace Demo {

// Settings of a vehicle fleet simulation.
class Settings {
public:
  // Constructs settings with all parameters initialized to zero.
  Settings() noexcept = default;

  // Constructs settings from command-line arguments.
  Settings(const int argc, char* argv[]) noexcept : executable_name_(argv[0]) {
    ParseArguments(argc, argv);
    PrintHeader();
    PrintCommand();
    PrintSettings();
  }

  // Number of vehicles in the simulation.
  constexpr int32_t Vehicles() const noexcept { return vehicles_; }

  // Number of charging stations in the simulation.
  constexpr int32_t ChargingStations() const noexcept {
    return charging_stations_;
  }

  // Time duration of the simulation.
  constexpr const PhQ::Time& Duration() const noexcept { return duration_; }

  const std::filesystem::path& Results() const noexcept { return results_; }

  // Random seed used to generate pseudo-random numbers in the simulation, or
  // std::nullopt, in which case random numbers generated in the simulation are
  // truly random.
  constexpr const std::optional<int64_t>& Seed() const noexcept {
    return seed_;
  }

private:
  // Prints the program header information to the console.
  void PrintHeader() const noexcept {
    std::cout << Program::Title << std::endl;
    std::cout << Program::Description << std::endl;
    std::cout << "Version: " << Program::CompilationDateAndTime << std::endl;
  }

  // Prints the program usage information to the console.
  void PrintUsage() const noexcept {
    const std::string indent{"  "};

    std::cout << "Usage:" << std::endl;

    std::cout << indent << executable_name_ << " " << Arguments::VehiclesPattern
              << " " << Arguments::ChargingStationsPattern << " "
              << Arguments::DurationPattern << " [" << Arguments::ResultsPattern
              << "] [" << Arguments::SeedPattern << "]" << std::endl;

    // Compute the padding length of the argument patterns.
    const std::size_t length{std::max({
        Arguments::Help.length(),
        Arguments::VehiclesPattern.length(),
        Arguments::ChargingStationsPattern.length(),
        Arguments::DurationPattern.length(),
        Arguments::ResultsPattern.length(),
        Arguments::SeedPattern.length(),
    })};

    std::cout << "Arguments:" << std::endl;

    std::cout << indent << PadToLength(Arguments::Help, length) << indent
              << "Displays this information and exits." << std::endl;

    std::cout
        << indent << PadToLength(Arguments::VehiclesPattern, length) << indent
        << "Number of vehicles in the simulation. Required." << std::endl;

    std::cout
        << indent << PadToLength(Arguments::ChargingStationsPattern, length)
        << indent << "Number of charging stations in the simulation. Required."
        << std::endl;

    std::cout
        << indent << PadToLength(Arguments::DurationPattern, length) << indent
        << "Time duration of the simulation in hours. Required." << std::endl;

    std::cout
        << indent << PadToLength(Arguments::ResultsPattern, length) << indent
        << "Path to the results file to be written. Optional." << std::endl;

    std::cout << indent << PadToLength(Arguments::SeedPattern, length) << indent
              << "Seed value for pseudo-random number generation. Optional."
              << std::endl;
  }

  // Parses the command-line arguments.
  void ParseArguments(const int argc, char* argv[]) noexcept {
    if (argc <= 1) {
      PrintHeader();
      PrintUsage();
      exit(EXIT_SUCCESS);
    }

    // Iterate over the command-line arguments. Skip the first argument because
    // it is the name of the executable.
    for (int index = 1; index < argc; ++index) {
      if (argv[index] == Arguments::Help) {
        PrintHeader();
        PrintUsage();
        exit(EXIT_SUCCESS);
      } else if (argv[index] == Arguments::VehiclesKey
                 && AtLeastOneMoreArgument(index, argc)) {
        vehicles_ = std::max(std::atoi(argv[index + 1]), 0);
        ++index;
      } else if (argv[index] == Arguments::ChargingStationsKey
                 && AtLeastOneMoreArgument(index, argc)) {
        charging_stations_ = std::max(std::atoi(argv[index + 1]), 0);
        ++index;
      } else if (argv[index] == Arguments::DurationKey
                 && AtLeastOneMoreArgument(index, argc)) {
        duration_ = {
            std::max(std::atof(argv[index + 1]), 0.0), PhQ::Unit::Time::Hour};
        ++index;
      } else if (argv[index] == Arguments::ResultsKey
                 && AtLeastOneMoreArgument(index, argc)) {
        results_ = argv[index + 1];
        ++index;
      } else if (argv[index] == Arguments::SeedKey
                 && AtLeastOneMoreArgument(index, argc)) {
        seed_ = std::atoi(argv[index + 1]);
        ++index;
      } else {
        PrintHeader();
        std::cout << "Unrecognized argument: " << argv[index] << std::endl;
        PrintUsage();
        exit(EXIT_FAILURE);
      }
    }
  }

  // Returns whether there is at least one more argument after the given
  // argument index.
  bool AtLeastOneMoreArgument(
      const int index, const int argument_count) const noexcept {
    return index + 1 < argument_count;
  }

  // Prints the command to the console.
  void PrintCommand() const noexcept {
    std::cout
        << "Command: " << executable_name_ << " " << Arguments::VehiclesKey
        << " " << vehicles_ << " " << Arguments::ChargingStationsKey << " "
        << charging_stations_ << " " << Arguments::DurationKey << " "
        << duration_.Value(PhQ::Unit::Time::Hour)
        << (!results_.empty() ?
                " " + Arguments::ResultsKey + " " + results_.string() :
                "")
        << (seed_.has_value() ?
                " " + Arguments::SeedKey + " " + std::to_string(seed_.value()) :
                "")
        << std::endl;
  }

  // Prints the settings to the console.
  void PrintSettings() const noexcept {
    std::cout << "- The number of vehicles in the simulation is: " << vehicles_
              << std::endl;
    std::cout << "- The number of charging stations in the simulation is: "
              << charging_stations_ << std::endl;
    std::cout << "- The time duration of the simulation is: "
              << duration_.Print(PhQ::Unit::Time::Hour) << std::endl;
    if (results_.empty()) {
      std::cout << "- The simulation results will not be written to a file."
                << std::endl;
    } else {
      std::cout << "- The simulation results will be written to: " << results_
                << std::endl;
    }
    if (seed_.has_value()) {
      std::cout << "- The seed value for pseudo-random number generation is : "
                << seed_.value() << std::endl;
    } else {
      std::cout << "- The seed value for random number generation will be "
                   "randomized."
                << std::endl;
    }
  }

  std::string executable_name_;

  int32_t vehicles_ = 0;

  int32_t charging_stations_ = 0;

  PhQ::Time duration_ = PhQ::Time::Zero();

  std::filesystem::path results_;

  std::optional<int64_t> seed_;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_SETTINGS_HPP
