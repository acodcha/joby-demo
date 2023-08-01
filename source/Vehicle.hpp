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

#include <memory>

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
        return Endurance();
      case VehicleStatus::WaitingToCharge:
        return DurationToFullCharge();
      case VehicleStatus::Charging:
        return DurationToFullCharge();
      case VehicleStatus::Flying:
        return Endurance();
    }
  }

private:
  VehicleId id_ = 0;

  std::shared_ptr<const VehicleModel> model_;

  VehicleStatus status_ = VehicleStatus::OnStandby;

  PhQ::Energy battery_ = PhQ::Energy::Zero();

  Demo::Statistics statistics_;
};

}  // namespace Demo
