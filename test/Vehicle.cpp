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
  EXPECT_EQ(vehicle.ChargingStationId(), std::nullopt);
  EXPECT_EQ(vehicle.Battery(), PhQ::Energy::Zero());
  EXPECT_EQ(vehicle.Statistics(), Statistics());
  EXPECT_EQ(vehicle.Range(), PhQ::Length::Zero());
  EXPECT_EQ(vehicle.Endurance(), PhQ::Time::Zero());
  EXPECT_EQ(vehicle.DurationToFullCharge(), PhQ::Time::Zero());
  EXPECT_EQ(vehicle.DurationToNextStatusChange(), PhQ::Time::Zero());
}

TEST(Vehicle, MainConstructor) {
  const VehicleId id = 222;

  const std::shared_ptr<const VehicleModel> vehicle_model = std::make_shared<
      const VehicleModel>(
      /*id=*/111,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model A",
      /*passenger_count=*/5,
      /*cruise_speed=*/PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour),
      /*battery_capacity=*/PhQ::Energy(100.0, PhQ::Unit::Energy::KilowattHour),
      /*charging_duration=*/PhQ::Time(0.2, PhQ::Unit::Time::Hour),
      /*fault_rate=*/PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(
          1.5, PhQ::Unit::Force::KilowattHourPerMile));

  const Vehicle vehicle = {id, vehicle_model};

  EXPECT_EQ(vehicle.Id(), id);
  EXPECT_EQ(vehicle.Model(), vehicle_model);
  EXPECT_EQ(vehicle.Status(), VehicleStatus::OnStandby);
  EXPECT_EQ(vehicle.ChargingStationId(), std::nullopt);
  EXPECT_EQ(vehicle.Battery(), vehicle_model->BatteryCapacity());
  EXPECT_EQ(vehicle.Statistics(), Statistics());
  EXPECT_EQ(vehicle.Range(), vehicle_model->RangeLimit());
  EXPECT_EQ(vehicle.Endurance(), vehicle_model->EnduranceLimit());
  EXPECT_EQ(vehicle.DurationToFullCharge(), PhQ::Time::Zero());
  EXPECT_EQ(
      vehicle.DurationToNextStatusChange(), vehicle_model->EnduranceLimit());
}

TEST(Vehicle, TimeStep) {
  const VehicleId id = 222;

  const std::shared_ptr<const VehicleModel> vehicle_model =
      std::make_shared<const VehicleModel>(
          /*id=*/111,
          /*manufacturer_name_english=*/"Manufacturer A",
          /*model_name_english=*/"Model A",
          /*passenger_count=*/4,
          /*cruise_speed=*/PhQ::Speed(1.0, PhQ::Unit::Speed::MetrePerSecond),
          /*battery_capacity=*/PhQ::Energy(2.0, PhQ::Unit::Energy::Joule),
          /*charging_duration=*/PhQ::Time(1.0, PhQ::Unit::Time::Second),
          /*fault_rate=*/PhQ::Frequency(1.0, PhQ::Unit::Frequency::Hertz),
          /*transport_energy_consumption=*/
          PhQ::TransportEnergyConsumption(1.0, PhQ::Unit::Force::Newton));

  Vehicle vehicle = {id, vehicle_model};

  ChargingStations charging_stations;
  const std::shared_ptr<ChargingStation> charging_station =
      std::make_shared<ChargingStation>(789);
  ASSERT_NE(charging_station, nullptr);
  charging_stations.Insert(charging_station);

  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());
  random_generator.seed(0);

  const PhQ::Time step_duration = {1.0, PhQ::Unit::Time::Second};

  // Simulate a first time step.

  vehicle.Update(charging_stations);
  vehicle.PerformTimeStep(step_duration, charging_stations, random_generator);
  vehicle.Update(charging_stations);

  EXPECT_EQ(vehicle.Status(), VehicleStatus::Flying);
  EXPECT_EQ(vehicle.ChargingStationId(), std::nullopt);
  EXPECT_EQ(vehicle.Battery(), PhQ::Energy(1.0, PhQ::Unit::Energy::Joule));
  EXPECT_EQ(vehicle.Range(), PhQ::Length(1.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Endurance(), PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(
      vehicle.DurationToFullCharge(), PhQ::Time(0.5, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.DurationToNextStatusChange(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightCount(), 1);
  EXPECT_EQ(vehicle.Statistics().TotalFlightDuration(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightDistance(),
            PhQ::Length(1.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalFlightPassengerDistance(),
            PhQ::Length(4.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDuration(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDistance(),
            PhQ::Length(1.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalChargingSessionCount(), 0);
  EXPECT_EQ(vehicle.Statistics().TotalChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(vehicle.Statistics().MeanChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(charging_station->Count(), 0);

  // Simulate a second time step.

  vehicle.Update(charging_stations);
  vehicle.PerformTimeStep(step_duration, charging_stations, random_generator);
  vehicle.Update(charging_stations);

  EXPECT_EQ(vehicle.Status(), VehicleStatus::WaitingToCharge);
  ASSERT_TRUE(vehicle.ChargingStationId().has_value());
  EXPECT_EQ(vehicle.ChargingStationId().value(), 789);
  EXPECT_EQ(vehicle.Battery(), PhQ::Energy::Zero());
  EXPECT_EQ(vehicle.Range(), PhQ::Length::Zero());
  EXPECT_EQ(vehicle.Endurance(), PhQ::Time::Zero());
  EXPECT_EQ(
      vehicle.DurationToFullCharge(), PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.DurationToNextStatusChange(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightCount(), 1);
  EXPECT_EQ(vehicle.Statistics().TotalFlightDuration(),
            PhQ::Time(2.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightDistance(),
            PhQ::Length(2.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalFlightPassengerDistance(),
            PhQ::Length(8.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDuration(),
            PhQ::Time(2.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDistance(),
            PhQ::Length(2.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalChargingSessionCount(), 0);
  EXPECT_EQ(vehicle.Statistics().TotalChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(vehicle.Statistics().MeanChargingDuration(), PhQ::Time::Zero());
  EXPECT_EQ(charging_station->Count(), 1);

  // Simulate a third time step.

  vehicle.Update(charging_stations);
  vehicle.PerformTimeStep(step_duration, charging_stations, random_generator);
  vehicle.Update(charging_stations);

  EXPECT_EQ(vehicle.Status(), VehicleStatus::Flying);
  EXPECT_EQ(vehicle.ChargingStationId(), std::nullopt);
  EXPECT_EQ(vehicle.Battery(), PhQ::Energy(2.0, PhQ::Unit::Energy::Joule));
  EXPECT_EQ(vehicle.Range(), PhQ::Length(2.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Endurance(), PhQ::Time(2.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(
      vehicle.DurationToFullCharge(), PhQ::Time(0.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.DurationToNextStatusChange(),
            PhQ::Time(2.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightCount(), 2);
  EXPECT_EQ(vehicle.Statistics().TotalFlightDuration(),
            PhQ::Time(2.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightDistance(),
            PhQ::Length(2.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalFlightPassengerDistance(),
            PhQ::Length(8.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDuration(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDistance(),
            PhQ::Length(1.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalChargingSessionCount(), 1);
  EXPECT_EQ(vehicle.Statistics().TotalChargingDuration(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().MeanChargingDuration(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(charging_station->Count(), 0);

  // Simulate a fourth time step.

  vehicle.Update(charging_stations);
  vehicle.PerformTimeStep(step_duration, charging_stations, random_generator);
  vehicle.Update(charging_stations);

  EXPECT_EQ(vehicle.Status(), VehicleStatus::Flying);
  EXPECT_EQ(vehicle.ChargingStationId(), std::nullopt);
  EXPECT_EQ(vehicle.Battery(), PhQ::Energy(1.0, PhQ::Unit::Energy::Joule));
  EXPECT_EQ(vehicle.Range(), PhQ::Length(1.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Endurance(), PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(
      vehicle.DurationToFullCharge(), PhQ::Time(0.5, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.DurationToNextStatusChange(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightCount(), 2);
  EXPECT_EQ(vehicle.Statistics().TotalFlightDuration(),
            PhQ::Time(3.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().TotalFlightDistance(),
            PhQ::Length(3.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalFlightPassengerDistance(),
            PhQ::Length(12.0, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDuration(),
            PhQ::Time(1.5, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().MeanFlightDistance(),
            PhQ::Length(1.5, PhQ::Unit::Length::Metre));
  EXPECT_EQ(vehicle.Statistics().TotalChargingSessionCount(), 1);
  EXPECT_EQ(vehicle.Statistics().TotalChargingDuration(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(vehicle.Statistics().MeanChargingDuration(),
            PhQ::Time(1.0, PhQ::Unit::Time::Second));
  EXPECT_EQ(charging_station->Count(), 0);
}

}  // namespace

}  // namespace Demo
