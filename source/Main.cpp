// Copyright © 2023-2024 Alexandre Coderre-Chabot
//
// This file is part of Joby Demonstration, a simple demonstration of C++ principles in the context
// of a vehicle fleet simulation.
//
// Joby Demonstration is hosted at:
//     https://github.com/acodcha/joby-demo
//
// This file is licensed under the MIT license (https://mit-license.org). Permission is hereby
// granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included in all copies or
//     substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//     BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//     NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//     DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//     FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <iostream>
#include <random>

#include "AggregateStatistics.hpp"
#include "ChargingStations.hpp"
#include "ResultsFileWriter.hpp"
#include "SampleVehicleModels.hpp"
#include "Settings.hpp"
#include "Simulation.hpp"
#include "Vehicles.hpp"

int main(int argc, char* argv[]) {
  const Demo::Settings settings{argc, argv};

  const Demo::VehicleModels vehicle_models = Demo::GenerateSampleVehicleModels();

  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());
  if (settings.Seed().has_value()) {
    random_generator.seed(settings.Seed().value());
  }

  Demo::Vehicles vehicles{settings.Vehicles(), vehicle_models, random_generator};

  Demo::ChargingStations charging_stations{settings.ChargingStations()};

  const Demo::Simulation simulation{
      settings.Duration(), vehicles, charging_stations, random_generator};

  const Demo::AggregateStatistics aggregate_statistics{vehicles};

  const Demo::ResultsFileWriter results_file_writer{
      settings.Results(), vehicle_models, aggregate_statistics};

  std::cout << "End of " << Demo::Program::Title << "." << std::endl;

  return EXIT_SUCCESS;
}
