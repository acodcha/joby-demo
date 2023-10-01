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
  const VehicleModel vehicle_model;
  EXPECT_EQ(vehicle_model.Id(), 0);
  EXPECT_EQ(vehicle_model.ManufacturerNameEnglish(), "");
  EXPECT_EQ(vehicle_model.ModelNameEnglish(), "");
  EXPECT_EQ(vehicle_model.PassengerCount(), 0);
  EXPECT_EQ(vehicle_model.CruiseSpeed(), PhQ::Speed::Zero());
  EXPECT_EQ(vehicle_model.BatteryCapacity(), PhQ::Energy::Zero());
  EXPECT_EQ(vehicle_model.ChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(vehicle_model.MeanFaultRate(), PhQ::Frequency::Zero());
  EXPECT_EQ(vehicle_model.TransportEnergyConsumption(),
            PhQ::TransportEnergyConsumption::Zero());
  EXPECT_EQ(vehicle_model.TransportPowerUsage(), PhQ::Power::Zero());
  EXPECT_EQ(vehicle_model.ChargingRate(), PhQ::Power::Zero());
  EXPECT_EQ(vehicle_model.RangeLimit(), PhQ::Length::Zero());
  EXPECT_EQ(vehicle_model.EnduranceLimit(), PhQ::Time::Zero());
}

TEST(VehicleModel, MainConstructor) {
  const VehicleModel vehicle_model{
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
          1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile)};

  EXPECT_EQ(vehicle_model.Id(), 111);

  EXPECT_EQ(vehicle_model.ManufacturerNameEnglish(), "Manufacturer A");

  EXPECT_EQ(vehicle_model.ModelNameEnglish(), "Model A");

  EXPECT_EQ(vehicle_model.PassengerCount(), 4);

  EXPECT_EQ(vehicle_model.CruiseSpeed(),
            PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour));

  EXPECT_EQ(vehicle_model.BatteryCapacity(),
            PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour));

  EXPECT_EQ(
      vehicle_model.ChargingDuration(), PhQ::Time(0.6, PhQ::Unit::Time::Hour));

  EXPECT_EQ(vehicle_model.MeanFaultRate(),
            PhQ::Frequency(0.25, PhQ::Unit::Frequency::PerHour));

  EXPECT_EQ(
      vehicle_model.TransportEnergyConsumption(),
      PhQ::TransportEnergyConsumption(
          1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile));

  EXPECT_EQ(
      vehicle_model.TransportPowerUsage(),
      PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour)
          * PhQ::TransportEnergyConsumption(
              1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile));

  EXPECT_EQ(vehicle_model.ChargingRate(),
            PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour)
                / PhQ::Time(0.6, PhQ::Unit::Time::Hour));

  EXPECT_EQ(
      vehicle_model.RangeLimit(),
      PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour)
          / PhQ::TransportEnergyConsumption(
              1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile));

  EXPECT_EQ(
      vehicle_model.EnduranceLimit(),
      (PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour)
       / PhQ::TransportEnergyConsumption(
           1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile))
          / PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour));
}

TEST(VehicleModel, NegativeValues) {
  const VehicleModel vehicle_model{
      /*id=*/111,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model A",
      /*passenger_count=*/-4,
      /*cruise_speed=*/PhQ::Speed(-120.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(-320.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(-0.6, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(-0.25, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          -1.6, PhQ::Unit::TransportEnergyConsumption::KilowattHourPerMile)};

  EXPECT_EQ(vehicle_model.Id(), 111);
  EXPECT_EQ(vehicle_model.ManufacturerNameEnglish(), "Manufacturer A");
  EXPECT_EQ(vehicle_model.ModelNameEnglish(), "Model A");
  EXPECT_EQ(vehicle_model.PassengerCount(), 0);
  EXPECT_EQ(vehicle_model.CruiseSpeed(), PhQ::Speed::Zero());
  EXPECT_EQ(vehicle_model.BatteryCapacity(), PhQ::Energy::Zero());
  EXPECT_EQ(vehicle_model.ChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(vehicle_model.MeanFaultRate(), PhQ::Frequency::Zero());
  EXPECT_EQ(vehicle_model.TransportEnergyConsumption(),
            PhQ::TransportEnergyConsumption::Zero());
  EXPECT_EQ(vehicle_model.TransportPowerUsage(), PhQ::Power::Zero());
  EXPECT_EQ(vehicle_model.ChargingRate(), PhQ::Power::Zero());
  EXPECT_EQ(vehicle_model.RangeLimit(), PhQ::Length::Zero());
  EXPECT_EQ(vehicle_model.EnduranceLimit(), PhQ::Time::Zero());
}

}  // namespace

}  // namespace Demo
