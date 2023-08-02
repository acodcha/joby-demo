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

#include <iostream>

#include "SampleVehicleModels.hpp"
#include "SimulationSettings.hpp"
#include "Vehicles.hpp"

int main(int argc, char* argv[]) {
  std::cout << "Start of program." << std::endl;

  const Demo::SimulationSettings settings{
      /*duration=*/PhQ::Time(3.0, PhQ::Unit::Time::Hour),
      /*vehicle_count=*/20,
      /*charging_station_count=*/3,
  };

  const Demo::VehicleModels vehicle_models =
      Demo::GenerateSampleVehicleModels();

  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());

  Demo::Vehicles vehicles{20, vehicle_models, random_generator};

  std::cout << "End of program." << std::endl;

  return EXIT_SUCCESS;
}
