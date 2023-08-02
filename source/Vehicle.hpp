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

#ifndef DEMO_INCLUDE_VEHICLE_HPP
#define DEMO_INCLUDE_VEHICLE_HPP

#include <memory>
#include <optional>
#include <random>

#include "ChargingStations.hpp"
#include "Statistics.hpp"
#include "VehicleId.hpp"
#include "VehicleModel.hpp"
#include "VehicleStatus.hpp"

namespace Demo {

// An individual vehicle of a given vehicle model.
class Vehicle {
public:
  // Default constructor. Initializes all properties to zero.
  constexpr Vehicle() noexcept = default;

  // Constructs a vehicle with a given ID and vehicle model.
  Vehicle(const VehicleId& id,
          const std::shared_ptr<const VehicleModel> model) noexcept
    : id_(id), model_(model) {
    // Initialize the vehicle to a fully-charged battery.
    if (model != nullptr) {
      battery_ = model->BatteryCapacity();
    }
  }

  // Globally-unique identifier for this vehicle.
  constexpr const VehicleId& Id() const noexcept { return id_; }

  // Vehicle model of this vehicle.
  const std::shared_ptr<const VehicleModel>& Model() const noexcept {
    return model_;
  }

  // Current status of this vehicle.
  constexpr const VehicleStatus Status() const noexcept { return status_; }

  // Returns the charging station ID at which this vehicle is currently either
  // queued or charging, or std::nullopt if this vehicle is not currently at a
  // charging station.
  constexpr const std::optional<Demo::ChargingStationId>&
  ChargingStationId() const noexcept {
    return charging_station_id_;
  }

  // Current remaining energy in the battery of this vehicle.
  constexpr const PhQ::Energy& Battery() const noexcept { return battery_; }

  // Statistics of this vehicle.
  constexpr const Demo::Statistics& Statistics() const noexcept {
    return statistics_;
  }

  // Current range of this vehicle. This is the maximum distance that this
  // vehicle can travel given its current battery charge.
  PhQ::Length Range() const noexcept {
    if (model_ == nullptr) {
      return PhQ::Length::Zero();
    }
    if (model_->TransportEnergyConsumption()
        <= PhQ::TransportEnergyConsumption::Zero()) {
      return PhQ::Length::Zero();
    }
    return battery_ / model_->TransportEnergyConsumption();
  }

  // Current endurance of this vehicle. This is the maximum time duration that
  // this vehicle can remain in flight given its current battery charge.
  PhQ::Time Endurance() const noexcept {
    if (model_ == nullptr) {
      return PhQ::Time::Zero();
    }
    if (model_->CruiseSpeed() <= PhQ::Speed::Zero()) {
      return PhQ::Time::Zero();
    }
    return Range() / model_->CruiseSpeed();
  }

  // Current time duration to fully charge this vehicle's battery given its
  // current battery charge.
  PhQ::Time DurationToFullCharge() const noexcept {
    if (model_ == nullptr) {
      return PhQ::Time::Zero();
    }
    if (battery_ >= model_->BatteryCapacity()) {
      return PhQ::Time::Zero();
    }
    if (model_->ChargingRate() <= PhQ::Power::Zero()) {
      return PhQ::Time::Zero();
    }
    const PhQ::Energy energy_to_full_charge =
        model_->BatteryCapacity() - battery_;
    return energy_to_full_charge / model_->ChargingRate();
  }

  // Returns the time duration to the next status change of this vehicle.
  PhQ::Time DurationToNextStatusChange() const noexcept {
    switch (status_) {
      case VehicleStatus::OnStandby:
        if (battery_ > PhQ::Energy::Zero()) {
          return Endurance();
        } else {
          return DurationToFullCharge();
        }
      case VehicleStatus::WaitingToCharge:
        return DurationToFullCharge();
      case VehicleStatus::Charging:
        return DurationToFullCharge();
      case VehicleStatus::Flying:
        return Endurance();
    }
  }

  // Updates the current vehicle's status and related properties. This method
  // should be called for each vehicle once at the beginning of each time step
  // of the simulation and once at the end of each time step of the simulation.
  void Update(ChargingStations& charging_stations) noexcept {
    switch (status_) {
      case VehicleStatus::OnStandby:
        if (battery_ > PhQ::Energy::Zero()) {
          Takeoff();
        } else {
          EnqueueAtChargingStationIfNotAlready(charging_stations);
          if (CanBeginCharging(charging_stations)) {
            BeginCharging();
          }
        }
        break;
      case VehicleStatus::WaitingToCharge:
        if (CanBeginCharging(charging_stations)) {
          BeginCharging();
        }
        break;
      case VehicleStatus::Charging:
        if (battery_ >= model_->BatteryCapacity()) {
          battery_ = model_->BatteryCapacity();
          DequeueFromChargingStation(charging_stations);
          Takeoff();
        }
        break;
      case VehicleStatus::Flying:
        if (battery_ <= PhQ::Energy::Zero()) {
          battery_ = PhQ::Energy::Zero();
          Land();
          EnqueueAtChargingStationIfNotAlready(charging_stations);
        }
        break;
    }
  }

  // Proceeds forward in time during a time step of the simulation. If the given
  // time duration is greater than the time duration to the next status change,
  // it is reduced to match this duration. This method should be called once for
  // each vehicle at each time step of the simulation.
  void PerformTimeStep(
      const PhQ::Time& duration, ChargingStations& charging_stations,
      std::mt19937_64& random_generator) noexcept {
    const PhQ::Time effective_duration =
        std::min(duration, DurationToNextStatusChange());
    switch (status_) {
      case VehicleStatus::OnStandby:
        if (battery_ > PhQ::Energy::Zero()) {
          Takeoff();
          Fly(effective_duration, random_generator);
        } else {
          EnqueueAtChargingStationIfNotAlready(charging_stations);
        }
        break;
      case VehicleStatus::WaitingToCharge:
        if (CanBeginCharging(charging_stations)) {
          BeginCharging();
          Charge(effective_duration, random_generator);
        }
        break;
      case VehicleStatus::Charging:
        Charge(effective_duration, random_generator);
        break;
      case VehicleStatus::Flying:
        Fly(effective_duration, random_generator);
        break;
    }
  }

private:
  // This vehicle takes off and begins flying.
  void Takeoff() noexcept {
    status_ = VehicleStatus::Flying;
    statistics_.IncrementTotalFlightCount();
  }

  // This vehicle lands.
  void Land() noexcept { status_ = VehicleStatus::OnStandby; }

  // This vehicle enqueues at a charging station if it is not already.
  void EnqueueAtChargingStationIfNotAlready(
      ChargingStations& charging_stations) noexcept {
    if (!charging_station_id_.has_value()) {
      const std::shared_ptr<ChargingStation> best_charging_station =
          charging_stations.LowestCount();
      if (best_charging_station != nullptr) {
        best_charging_station->Enqueue(id_);
        charging_station_id_ = best_charging_station->Id();
        status_ = VehicleStatus::WaitingToCharge;
      }
    }
  }

  // Returns whether this vehicle can now begin charging at its current charging
  // station.
  bool CanBeginCharging(ChargingStations& charging_stations) noexcept {
    if (charging_station_id_.has_value()) {
      const std::shared_ptr<ChargingStation> charging_station =
          charging_stations.At(charging_station_id_.value());
      const std::optional<VehicleId> front_id = charging_station->Front();
      if (front_id.has_value() && front_id == id_) {
        return true;
      }
    }
    return false;
  }

  // This vehicle begins charging at its current charging station.
  void BeginCharging() noexcept {
    status_ = VehicleStatus::Charging;
    statistics_.IncrementTotalChargingSessionCount();
  }

  // This vehicle charges its battery at its current charging station.
  void Charge(
      const PhQ::Time& duration, std::mt19937_64& random_generator) noexcept {
    status_ = VehicleStatus::Charging;
    if (model_ == nullptr) {
      return;
    }
    battery_ += model_->ChargingRate() * duration;
    statistics_.ModifyTotalChargingSessionDuration(duration);
    RandomlyGenerateFaults(duration, random_generator);
  }

  // This vehicle stops charging at its current charging station and dequeues
  // from it.
  void DequeueFromChargingStation(
      ChargingStations& charging_stations) noexcept {
    if (charging_station_id_.has_value()) {
      const std::shared_ptr<ChargingStation> charging_station =
          charging_stations.At(charging_station_id_.value());
      if (charging_station != nullptr) {
        charging_station->Dequeue();
        charging_station_id_.reset();
      }
    }
  }

  // This vehicle flies for a given time duration.
  void Fly(
      const PhQ::Time& duration, std::mt19937_64& random_generator) noexcept {
    status_ = VehicleStatus::Flying;
    if (model_ == nullptr) {
      return;
    }
    const PhQ::Length distance = model_->CruiseSpeed() * duration;
    battery_ -= model_->TransportPowerUsage() * duration;
    statistics_.ModifyTotalFlightDurationAndDistance(
        model_->PassengerCount(), duration, distance);
    RandomlyGenerateFaults(duration, random_generator);
  }

  // Given a time duration, randomly generates faults during this time according
  // to this vehicle model's mean fault rate using a random Poisson process.
  void RandomlyGenerateFaults(
      const PhQ::Time& duration, std::mt19937_64& random_generator) noexcept {
    if (model_ == nullptr) {
      return;
    }
    const double expected_faults_during_this_duration =
        duration * model_->MeanFaultRate();
    std::poisson_distribution<int64_t> distribution(
        expected_faults_during_this_duration);
    const int64_t faults_during_this_duration = distribution(random_generator);
    statistics_.ModifyTotalFaultCount(faults_during_this_duration);
  }

  VehicleId id_ = 0;

  std::shared_ptr<const VehicleModel> model_;

  VehicleStatus status_ = VehicleStatus::OnStandby;

  std::optional<Demo::ChargingStationId> charging_station_id_;

  PhQ::Energy battery_ = PhQ::Energy::Zero();

  Demo::Statistics statistics_;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_VEHICLE_HPP
