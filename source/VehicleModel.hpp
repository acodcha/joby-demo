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

#ifndef DEMO_INCLUDE_VEHICLE_MODEL_HPP
#define DEMO_INCLUDE_VEHICLE_MODEL_HPP

#include <PhQ/Energy.hpp>
#include <PhQ/Frequency.hpp>
#include <PhQ/Power.hpp>
#include <PhQ/Speed.hpp>
#include <PhQ/Time.hpp>
#include <PhQ/TransportEnergyConsumption.hpp>
#include <string>
#include <string_view>

#include "VehicleModelId.hpp"

namespace Demo {

// Properties of a vehicle model.
// TODO: This could use a Protocol Buffer schema.
class VehicleModel {
public:
  // Default constructor. Initializes all properties to zero.
  VehicleModel() noexcept = default;

  // Constructs a vehicle model from the given parameters. Checks the given
  // parameters for consistency and initializes all members accordingly.
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
      passenger_count_(std::max(passenger_count, 0)),
      cruise_speed_(std::max(cruise_speed, PhQ::Speed::Zero())),
      battery_capacity_(std::max(battery_capacity, PhQ::Energy::Zero())),
      charging_duration_(std::max(charging_duration, PhQ::Time::Zero())),
      mean_fault_rate_(std::max(fault_rate, PhQ::Frequency::Zero())),
      transport_energy_consumption_(
          std::max(transport_energy_consumption,
                   PhQ::TransportEnergyConsumption::Zero())),
      transport_power_usage_(cruise_speed_ * transport_energy_consumption_) {
    if (charging_duration_ > PhQ::Time::Zero()) {
      charging_rate_ = battery_capacity_ / charging_duration_;
    }

    if (transport_energy_consumption_
        > PhQ::TransportEnergyConsumption::Zero()) {
      range_limit_ = battery_capacity_ / transport_energy_consumption_;
    }

    if (cruise_speed_ > PhQ::Speed::Zero()) {
      endurance_limit_ = range_limit_ / cruise_speed_;
    }
  }

  // Globally-unique identifier for this vehicle model.
  constexpr const VehicleModelId Id() const noexcept { return id_; }

  // Name of the manufacturer of this vehicle model in English.
  // TODO: Consider using a Name class to handle names in multiple languages.
  const std::string_view ManufacturerNameEnglish() const noexcept {
    return manufacturer_name_english_;
  }

  // Name of this vehicle model in English.
  // TODO: Consider using a Name class to handle names in multiple languages.
  const std::string_view ModelNameEnglish() const noexcept {
    return model_name_english_;
  }

  // Maximum number of passengers that this vehicle model can carry at a time.
  // This only includes passengers and excludes pilots and other crew, if any.
  // TODO: Consider adding a crew count.
  constexpr const int32_t PassengerCount() const noexcept {
    return passenger_count_;
  }

  // Cruise speed of this vehicle model during steady level flight.
  constexpr const PhQ::Speed CruiseSpeed() const noexcept {
    return cruise_speed_;
  }

  // Energy capacity of the vehicle model's battery when fully charged.
  constexpr const PhQ::Energy BatteryCapacity() const noexcept {
    return battery_capacity_;
  }

  // Time duration to charge the battery from zero charge to a full charge for
  // this vehicle model.
  constexpr const PhQ::Time ChargingDuration() const noexcept {
    return charging_duration_;
  }

  // Mean fault rate of this vehicle model. This is the expected value for the
  // number of faults per unit time for this vehicle model.
  constexpr const PhQ::Frequency MeanFaultRate() const noexcept {
    return mean_fault_rate_;
  }

  // Energy consumption in transport for this vehicle model, which measures
  // energy use per distance traveled.
  constexpr const PhQ::TransportEnergyConsumption
  TransportEnergyConsumption() const noexcept {
    return transport_energy_consumption_;
  }

  // Power usage in transport for this vehicle model, which measures the rate at
  // which energy is used per unit time while traveling.
  constexpr const PhQ::Power& TransportPowerUsage() const noexcept {
    return transport_power_usage_;
  }

  // Rate when charging this vehicle model's battery.
  constexpr const PhQ::Power& ChargingRate() const noexcept {
    return charging_rate_;
  }

  // Range limit of this vehicle model. This is the maximum distance this
  // vehicle can travel starting with a full battery charge.
  constexpr const PhQ::Length& RangeLimit() const noexcept {
    return range_limit_;
  }

  // Endurance limit of this vehicle model. This is the maximum time duration
  // this vehicle can remain in flight starting with a full battery charge.
  constexpr const PhQ::Time& EnduranceLimit() const noexcept {
    return endurance_limit_;
  }

private:
  VehicleModelId id_ = 0;

  std::string manufacturer_name_english_;

  std::string model_name_english_;

  int32_t passenger_count_ = 0;

  PhQ::Speed cruise_speed_ = PhQ::Speed::Zero();

  PhQ::Energy battery_capacity_ = PhQ::Energy::Zero();

  PhQ::Time charging_duration_ = PhQ::Time::Zero();

  PhQ::Frequency mean_fault_rate_ = PhQ::Frequency::Zero();

  PhQ::TransportEnergyConsumption transport_energy_consumption_ =
      PhQ::TransportEnergyConsumption::Zero();

  PhQ::Power transport_power_usage_ = PhQ::Power::Zero();

  PhQ::Power charging_rate_ = PhQ::Power::Zero();

  PhQ::Length range_limit_ = PhQ::Length::Zero();

  PhQ::Time endurance_limit_ = PhQ::Time::Zero();
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_VEHICLE_MODEL_HPP
