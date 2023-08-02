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

#include "../source/AggregateStatistics.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

const std::shared_ptr<const VehicleModel> model =
    std::make_shared<const VehicleModel>(
        /*id=*/123,
        /*manufacturer_name_english=*/"Manufacturer A",
        /*model_name_english=*/"Model B",
        /*passenger_count=*/4,
        /*cruise_speed=*/PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour),
        /*battery_capacity=*/PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour),
        /*charging_duration=*/PhQ::Time(0.8, PhQ::Unit::Time::Hour),
        /*fault_rate=*/PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour),
        /*transport_energy_consumption=*/
        PhQ::TransportEnergyConsumption(
            2.0, PhQ::Unit::Force::KilowattHourPerMile));

TEST(AggregateStatistics, Empty) {
  const AggregateStatistics empty;
  EXPECT_TRUE(empty.Empty());

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/456, model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/789, model));

  const AggregateStatistics aggregate_statistics{vehicles};
  EXPECT_FALSE(aggregate_statistics.Empty());
}

TEST(AggregateStatistics, Size) {
  const AggregateStatistics empty;
  EXPECT_EQ(empty.Size(), 0);

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/456, model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/789, model));

  const AggregateStatistics aggregate_statistics{vehicles};
  EXPECT_EQ(aggregate_statistics.Size(), 1);
}

TEST(AggregateStatistics, At) {
  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/456, model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/789, model));

  const AggregateStatistics aggregate_statistics{vehicles};
  EXPECT_TRUE(aggregate_statistics.At(123).has_value());
  EXPECT_EQ(aggregate_statistics.At(456), std::nullopt);
  EXPECT_EQ(aggregate_statistics.At(789), std::nullopt);
}

TEST(AggregateStatistics, Iterator) {
  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/456, model));
  vehicles.Insert(std::make_shared<Vehicle>(/*id=*/789, model));

  const AggregateStatistics aggregate_statistics{vehicles};
  for (const std::pair<const VehicleModelId, Statistics>&
           vehicle_model_id_and_statistics : aggregate_statistics) {
    EXPECT_EQ(vehicle_model_id_and_statistics.first, 123);
  }
}

}  // namespace

}  // namespace Demo
