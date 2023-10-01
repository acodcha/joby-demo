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

#include "../source/Simulation.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(Simulation, Regular) {
  const PhQ::Time duration{5.0, PhQ::Unit::Time::Second};

  const std::shared_ptr<const VehicleModel> vehicle_model =
      std::make_shared<const VehicleModel>(
          /*id=*/111,
          /*manufacturer_name_english=*/"Manufacturer A",
          /*model_name_english=*/"Model B",
          /*passenger_count=*/4,
          /*cruise_speed=*/PhQ::Speed(1.0, PhQ::Unit::Speed::MetrePerSecond),
          /*battery_capacity=*/PhQ::Energy(1.0, PhQ::Unit::Energy::Joule),
          /*charging_duration=*/PhQ::Time(1.0, PhQ::Unit::Time::Second),
          /*fault_rate=*/PhQ::Frequency(1.0, PhQ::Unit::Frequency::Hertz),
          /*transport_energy_consumption=*/
          PhQ::TransportEnergyConsumption(
              1.0, PhQ::Unit::TransportEnergyConsumption::JoulePerMetre));

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/222, vehicle_model));

  ChargingStations charging_stations{1};

  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());
  random_generator.seed(0);

  const Simulation simulation{
      duration, vehicles, charging_stations, random_generator};
}

}  // namespace

}  // namespace Demo
