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

#include "../source/VehicleModel.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(VehicleModel, DefaultConstructor) {
  const VehicleModel model;
  EXPECT_EQ(model.id, 0);
  EXPECT_EQ(model.manufacturer_name_english, "");
  EXPECT_EQ(model.model_name_english, "");
  EXPECT_EQ(model.passenger_count, 0);
  EXPECT_EQ(model.cruise_speed, PhQ::Speed::Zero());
  EXPECT_EQ(model.battery_capacity, PhQ::Energy::Zero());
  EXPECT_EQ(model.charging_duration, PhQ::Time::Zero());
  EXPECT_EQ(model.fault_rate, PhQ::Frequency::Zero());
  EXPECT_EQ(model.transport_energy_consumption,
            PhQ::TransportEnergyConsumption::Zero());
}

TEST(VehicleModel, InitializerListConstructor) {
  const VehicleModel model = {
      123,
      "Manufacturer A",
      "Model B",
      4,
      PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour),
      PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour),
      PhQ::Time(0.8, PhQ::Unit::Time::Hour),
      PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour),
      PhQ::TransportEnergyConsumption(
          2.0, PhQ::Unit::Force::KilowattHourPerMile),
  };

  EXPECT_EQ(model.id, 123);

  EXPECT_EQ(model.manufacturer_name_english, "Manufacturer A");

  EXPECT_EQ(model.model_name_english, "Model B");

  EXPECT_EQ(model.passenger_count, 4);

  EXPECT_EQ(
      model.cruise_speed, PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour));

  EXPECT_EQ(model.battery_capacity,
            PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour));

  EXPECT_EQ(model.charging_duration, PhQ::Time(0.8, PhQ::Unit::Time::Hour));

  EXPECT_EQ(
      model.fault_rate, PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour));

  EXPECT_EQ(model.transport_energy_consumption,
            PhQ::TransportEnergyConsumption(
                2.0, PhQ::Unit::Force::KilowattHourPerMile));
}

}  // namespace

}  // namespace Demo