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

#ifndef DEMO_INCLUDE_SAMPLE_VEHICLE_MODELS_HPP
#define DEMO_INCLUDE_SAMPLE_VEHICLE_MODELS_HPP

#include <iostream>

#include "VehicleModels.hpp"

namespace Demo {

VehicleModels GenerateSampleVehicleModels() noexcept {
  VehicleModels vehicle_models;

  vehicle_models.Insert(std::make_shared<const VehicleModel>(
      /*id=*/0,
      /*manufacturer_name_english=*/"Alpha Company",
      /*model_name_english=*/"Alpha Model",
      /*passenger_count=*/4,
      /*cruise_speed=*/PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.6, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.25, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          1.6, PhQ::Unit::Force::KilowattHourPerMile)));

  vehicle_models.Insert(std::make_shared<const VehicleModel>(
      /*id=*/1,
      /*manufacturer_name_english=*/"Bravo Company",
      /*model_name_english=*/"Bravo Model",
      /*passenger_count=*/5,
      /*cruise_speed=*/PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(100.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.2, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          1.5, PhQ::Unit::Force::KilowattHourPerMile)));

  vehicle_models.Insert(std::make_shared<const VehicleModel>(
      /*id=*/2,
      /*manufacturer_name_english=*/"Charlie Company",
      /*model_name_english=*/"Charlie Model",
      /*passenger_count=*/3,
      /*cruise_speed=*/PhQ::Speed(160.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(220.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.8, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.05, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          2.2, PhQ::Unit::Force::KilowattHourPerMile)));

  vehicle_models.Insert(std::make_shared<const VehicleModel>(
      /*id=*/3,
      /*manufacturer_name_english=*/"Delta Company",
      /*model_name_english=*/"Delta Model",
      /*passenger_count=*/2,
      /*cruise_speed=*/PhQ::Speed(90.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(120.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.62, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.22, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          0.8, PhQ::Unit::Force::KilowattHourPerMile)));

  vehicle_models.Insert(std::make_shared<const VehicleModel>(
      /*id=*/4,
      /*manufacturer_name_english=*/"Echo Company",
      /*model_name_english=*/"Echo Model",
      /*passenger_count=*/2,
      /*cruise_speed=*/PhQ::Speed(30.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(150.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.3, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.61, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          5.8, PhQ::Unit::Force::KilowattHourPerMile)));

  std::cout << "Generated " << vehicle_models.Size()
            << " sample vehicle models." << std::endl;

  return vehicle_models;
}

}  // namespace Demo

#endif  // DEMO_INCLUDE_SAMPLE_VEHICLE_MODELS_HPP
