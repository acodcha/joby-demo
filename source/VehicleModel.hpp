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

namespace Demo {

// Globally-unique identifier of a vehicle model.
using VehicleModelId = std::size_t;

// Properties of a vehicle model.
// TODO: This should probably use a Protocol Buffer schema.
struct VehicleModel {
  // Globally-unique identifier for this vehicle model.
  VehicleModelId id = 0;

  // Name of the manufacturer of this vehicle model in English.
  // TODO: Do we need the manufacturer name in other languages?
  std::string manufacturer_name_english;

  // Name of this vehicle model in English.
  // TODO: Do we need the model name in other languages?
  std::string model_name_english;

  // Maximum number of passengers that this vehicle model can carry at a time.
  // This only includes passengers and excludes pilots and other crew, if any.
  // TODO: Consider a pilot count and other crew count?
  int32_t passenger_count = 0;

  // Cruise speed of this vehicle model during steady level flight.
  PhQ::Speed cruise_speed = PhQ::Speed::Zero();

  // Energy capacity of the vehicle model's battery when fully charged.
  PhQ::Energy battery_capacity = PhQ::Energy::Zero();

  // Time duration to charge the battery from zero charge to a full charge for
  // this vehicle model.
  PhQ::Time charging_duration = PhQ::Time::Zero();

  // Fault rate per unit time of this vehicle model.
  PhQ::Frequency fault_rate = PhQ::Frequency::Zero();

  // Energy consumption in transport for this vehicle model, which measures
  // energy use per distance traveled.
  PhQ::TransportEnergyConsumption transport_energy_consumption =
      PhQ::TransportEnergyConsumption::Zero();
};

}  // namespace Demo
