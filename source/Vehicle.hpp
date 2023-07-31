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
#include "VehicleModel.hpp"

namespace Demo {

// Globally-unique identifier of a vehicle. Not to be confused with
// VehicleModelId, which is a globally-unique identifier for a vehicle model
// rather than a vehicle.
using VehicleId = int64_t;

// Status of a vehicle at a given time.
enum class VehicleStatus : int8_t {
  OnStandby,
  WaitingToCharge,
  Charging,
  Flying,
};

// Simple class representing a vehicle.
class Vehicle {
public:
  // Default constructor. Initializes the identifier to 0 and the model to the
  // null pointer.
  constexpr Vehicle() noexcept = default;

  // Constructs a vehicle with a given identifier and vehicle model.
  Vehicle(const VehicleId& id,
          const std::shared_ptr<const VehicleModel> model) noexcept
    : id_(id), model_(model) {
    // Initialize the vehicle to its full battery capacity.
    if (model != nullptr) {
      remaining_battery_ = model->BatteryCapacity();
    }
  }

  constexpr const VehicleId& Id() const noexcept { return id_; }

  const std::shared_ptr<const VehicleModel>& Model() const noexcept {
    return model_;
  }

  constexpr const VehicleStatus Status() const noexcept { return status_; }

  constexpr const PhQ::Energy& RemainingBattery() const noexcept {
    return remaining_battery_;
  }

  constexpr const Demo::Statistics& Statistics() const noexcept {
    return statistics_;
  }

private:
  VehicleId id_ = 0;

  std::shared_ptr<const VehicleModel> model_;

  VehicleStatus status_ = VehicleStatus::OnStandby;

  PhQ::Energy remaining_battery_ = PhQ::Energy::Zero();

  Demo::Statistics statistics_;
};

}  // namespace Demo
