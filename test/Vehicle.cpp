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

#include "../source/Vehicle.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(Vehicle, DefaultConstructor) {
  const Vehicle vehicle;
  EXPECT_EQ(vehicle.Id(), 0);
  EXPECT_EQ(vehicle.Model(), nullptr);
  EXPECT_EQ(vehicle.Status(), VehicleStatus::OnStandby);
}

TEST(Vehicle, MainConstructor) {
  const VehicleId id = 456;

  const std::shared_ptr<const VehicleModel> model =
      std::make_shared<const VehicleModel>(
          123, "Manufacturer A", "Model B", 4,
          PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour),
          PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour),
          PhQ::Time(0.8, PhQ::Unit::Time::Hour),
          PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour),
          PhQ::TransportEnergyConsumption(
              2.0, PhQ::Unit::Force::KilowattHourPerMile));

  const Vehicle vehicle = {id, model};

  EXPECT_EQ(vehicle.Id(), 456);
  EXPECT_EQ(vehicle.Model(), model);
  EXPECT_EQ(vehicle.Status(), VehicleStatus::OnStandby);
}

}  // namespace

}  // namespace Demo
