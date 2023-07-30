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

#include <PhQ/Energy.hpp>
#include <PhQ/Frequency.hpp>
#include <PhQ/Speed.hpp>
#include <PhQ/Time.hpp>
#include <PhQ/TransportEnergyConsumption.hpp>
#include <string>
#include <string_view>

namespace Demo {

// Globally-unique identifier of a vehicle model.
using VehicleModelId = int64_t;

// Properties of a vehicle model.
// TODO: This should probably use a Protocol Buffer schema.
class VehicleModel {
public:
  // Default constructor.
  VehicleModel() noexcept = default;

  // Main constructor.
  VehicleModel(
      const VehicleModelId& id,
      const std::string_view manufacturer_name_english,
      const std::string_view model_name_english, const int32_t passenger_count,
      const PhQ::Speed& cruise_speed, const PhQ::Energy& battery_capacity,
      const PhQ::Time& charging_duration, const PhQ::Frequency& fault_rate,
      const PhQ::TransportEnergyConsumption&
          transport_energy_consumption) noexcept
    : id_(id), manufacturer_name_english_(manufacturer_name_english),
      model_name_english_(model_name_english),
      passenger_count_(passenger_count), cruise_speed_(cruise_speed),
      battery_capacity_(battery_capacity),
      charging_duration_(charging_duration), fault_rate_(fault_rate),
      transport_energy_consumption_(transport_energy_consumption) {}

  constexpr const VehicleModelId Id() const noexcept { return id_; }

  const std::string_view ManufacturerNameEnglish() const noexcept {
    return manufacturer_name_english_;
  }

  const std::string_view ModelNameEnglish() const noexcept {
    return model_name_english_;
  }

  constexpr const int32_t PassengerCount() const noexcept {
    return passenger_count_;
  }

  constexpr const PhQ::Speed CruiseSpeed() const noexcept {
    return cruise_speed_;
  }

  constexpr const PhQ::Energy BatteryCapacity() const noexcept {
    return battery_capacity_;
  }

  constexpr const PhQ::Time ChargingDuration() const noexcept {
    return charging_duration_;
  }

  constexpr const PhQ::Frequency FaultRate() const noexcept {
    return fault_rate_;
  }

  constexpr const PhQ::TransportEnergyConsumption
  TransportEnergyConsumption() const noexcept {
    return transport_energy_consumption_;
  }

private:
  // Globally-unique identifier for this vehicle model.
  VehicleModelId id_ = 0;

  // Name of the manufacturer of this vehicle model in English.
  // TODO: Do we need the manufacturer name in other languages?
  std::string manufacturer_name_english_;

  // Name of this vehicle model in English.
  // TODO: Do we need the model name in other languages?
  std::string model_name_english_;

  // Maximum number of passengers that this vehicle model can carry at a time.
  // This only includes passengers and excludes pilots and other crew, if any.
  // TODO: Consider a pilot count and other crew count?
  int32_t passenger_count_ = 0;

  // Cruise speed of this vehicle model during steady level flight.
  PhQ::Speed cruise_speed_ = PhQ::Speed::Zero();

  // Energy capacity of the vehicle model's battery when fully charged.
  PhQ::Energy battery_capacity_ = PhQ::Energy::Zero();

  // Time duration to charge the battery from zero charge to a full charge for
  // this vehicle model.
  PhQ::Time charging_duration_ = PhQ::Time::Zero();

  // Fault rate per unit time of this vehicle model.
  PhQ::Frequency fault_rate_ = PhQ::Frequency::Zero();

  // Energy consumption in transport for this vehicle model, which measures
  // energy use per distance traveled.
  PhQ::TransportEnergyConsumption transport_energy_consumption_ =
      PhQ::TransportEnergyConsumption::Zero();
};

}  // namespace Demo
