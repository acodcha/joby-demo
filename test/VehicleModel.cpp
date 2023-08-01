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
  EXPECT_EQ(model.Id(), 0);
  EXPECT_EQ(model.ManufacturerNameEnglish(), "");
  EXPECT_EQ(model.ModelNameEnglish(), "");
  EXPECT_EQ(model.PassengerCount(), 0);
  EXPECT_EQ(model.CruiseSpeed(), PhQ::Speed::Zero());
  EXPECT_EQ(model.BatteryCapacity(), PhQ::Energy::Zero());
  EXPECT_EQ(model.ChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(model.FaultRate(), PhQ::Frequency::Zero());
  EXPECT_EQ(model.TransportEnergyConsumption(),
            PhQ::TransportEnergyConsumption::Zero());
  EXPECT_EQ(model.TransportPowerUsage(), PhQ::Power::Zero());
  EXPECT_EQ(model.ChargingRate(), PhQ::Power::Zero());
  EXPECT_EQ(model.RangeLimit(), PhQ::Length::Zero());
  EXPECT_EQ(model.EnduranceLimit(), PhQ::Time::Zero());
}

TEST(VehicleModel, MainConstructor) {
  const VehicleModel model{
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
          2.0, PhQ::Unit::Force::KilowattHourPerMile),
  };
  EXPECT_EQ(model.Id(), 123);
  EXPECT_EQ(model.ManufacturerNameEnglish(), "Manufacturer A");
  EXPECT_EQ(model.ModelNameEnglish(), "Model B");
  EXPECT_EQ(model.PassengerCount(), 4);
  EXPECT_EQ(
      model.CruiseSpeed(), PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour));
  EXPECT_EQ(model.BatteryCapacity(),
            PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour));

  EXPECT_EQ(model.ChargingDuration(), PhQ::Time(0.8, PhQ::Unit::Time::Hour));
  EXPECT_EQ(
      model.FaultRate(), PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour));
  EXPECT_EQ(model.TransportEnergyConsumption(),
            PhQ::TransportEnergyConsumption(
                2.0, PhQ::Unit::Force::KilowattHourPerMile));
  EXPECT_EQ(model.TransportPowerUsage(),
            PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour)
                * PhQ::TransportEnergyConsumption(
                    2.0, PhQ::Unit::Force::KilowattHourPerMile));
  EXPECT_EQ(model.ChargingRate(),
            PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour)
                / PhQ::Time(0.8, PhQ::Unit::Time::Hour));
  EXPECT_EQ(model.RangeLimit(),
            PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour)
                / PhQ::TransportEnergyConsumption(
                    2.0, PhQ::Unit::Force::KilowattHourPerMile));
  EXPECT_EQ(model.EnduranceLimit(),
            (PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour)
             / PhQ::TransportEnergyConsumption(
                 2.0, PhQ::Unit::Force::KilowattHourPerMile))
                / PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour));
}

TEST(VehicleModel, NegativeValues) {
  const VehicleModel model{
      /*id=*/123,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model B",
      /*passenger_count=*/-4,
      /*cruise_speed=*/PhQ::Speed(-100.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(-200.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(-0.8, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(-0.1, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          -2.0, PhQ::Unit::Force::KilowattHourPerMile),
  };
  EXPECT_EQ(model.Id(), 123);
  EXPECT_EQ(model.ManufacturerNameEnglish(), "Manufacturer A");
  EXPECT_EQ(model.ModelNameEnglish(), "Model B");
  EXPECT_EQ(model.PassengerCount(), 0);
  EXPECT_EQ(model.CruiseSpeed(), PhQ::Speed::Zero());
  EXPECT_EQ(model.BatteryCapacity(), PhQ::Energy::Zero());
  EXPECT_EQ(model.ChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(model.FaultRate(), PhQ::Frequency::Zero());
  EXPECT_EQ(model.TransportEnergyConsumption(),
            PhQ::TransportEnergyConsumption::Zero());
  EXPECT_EQ(model.TransportPowerUsage(), PhQ::Power::Zero());
  EXPECT_EQ(model.ChargingRate(), PhQ::Power::Zero());
  EXPECT_EQ(model.RangeLimit(), PhQ::Length::Zero());
  EXPECT_EQ(model.EnduranceLimit(), PhQ::Time::Zero());
}

}  // namespace

}  // namespace Demo
