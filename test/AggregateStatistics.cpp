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

#include "../source/AggregateStatistics.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(AggregateStatistics, Empty) {
  const std::shared_ptr<const VehicleModel> vehicle_model = std::make_shared<const VehicleModel>(
      /*id=*/111,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model A",
      /*passenger_count=*/4,
      /*cruise_speed=*/PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.6, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.25, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile));

  const AggregateStatistics aggregate_statistics_0;
  EXPECT_TRUE(aggregate_statistics_0.Empty());

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/222, vehicle_model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/333, vehicle_model));

  const AggregateStatistics aggregate_statistics_1{vehicles};
  EXPECT_FALSE(aggregate_statistics_1.Empty());
}

TEST(AggregateStatistics, Size) {
  const std::shared_ptr<const VehicleModel> vehicle_model = std::make_shared<const VehicleModel>(
      /*id=*/111,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model A",
      /*passenger_count=*/4,
      /*cruise_speed=*/PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.6, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.25, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile));

  const AggregateStatistics aggregate_statistics_0;
  EXPECT_EQ(aggregate_statistics_0.Size(), 0);

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/222, vehicle_model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/333, vehicle_model));

  const AggregateStatistics aggregate_statistics_1{vehicles};
  EXPECT_EQ(aggregate_statistics_1.Size(), 1);
}

TEST(AggregateStatistics, At) {
  const std::shared_ptr<const VehicleModel> vehicle_model = std::make_shared<const VehicleModel>(
      /*id=*/111,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model A",
      /*passenger_count=*/4,
      /*cruise_speed=*/PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.6, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.25, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile));

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/222, vehicle_model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/333, vehicle_model));

  const AggregateStatistics aggregate_statistics{vehicles};
  EXPECT_TRUE(aggregate_statistics.At(111).has_value());
  EXPECT_EQ(aggregate_statistics.At(222), std::nullopt);
  EXPECT_EQ(aggregate_statistics.At(333), std::nullopt);
}

TEST(AggregateStatistics, Iterator) {
  const std::shared_ptr<const VehicleModel> vehicle_model = std::make_shared<const VehicleModel>(
      /*id=*/111,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model A",
      /*passenger_count=*/4,
      /*cruise_speed=*/PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.6, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.25, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile));

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/222, vehicle_model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/333, vehicle_model));

  const AggregateStatistics aggregate_statistics{vehicles};
  for (const std::pair<const VehicleModelId, Statistics>& vehicle_model_id_and_statistics :
       aggregate_statistics) {
    EXPECT_EQ(vehicle_model_id_and_statistics.first, 111);
  }
}

}  // namespace

}  // namespace Demo
