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

#include <optional>
#include <PhQ/Time.hpp>

namespace Demo {

// Settings of a vehicle fleet simulation.
class SimulationSettings {
public:
  // Default constructor. Initializes all members to zero.
  SimulationSettings() noexcept = default;

  // Constructs simulation settings from the given parameters. Checks the given
  // parameters for consistency and initializes all members accordingly.
  SimulationSettings(
      const PhQ::Time& duration, const PhQ::Time& time_step,
      const int32_t vehicle_count, const int32_t charging_station_count,
      const std::optional<int64_t>& random_seed = std::nullopt) noexcept {
    duration_ = std::max(duration, PhQ::Time::Zero());
    InitializeTimeStepAndTimeStepCount(time_step);
    vehicle_count_ = std::max(vehicle_count, 0);
    charging_station_count_ = std::max(charging_station_count, 0);
    random_seed_ = random_seed;
  }

  constexpr const PhQ::Time& Duration() const noexcept { return duration_; }

  constexpr const PhQ::Time& TimeStep() const noexcept { return time_step_; }

  constexpr int32_t TimeStepCount() const noexcept { return time_step_count_; }

  constexpr int32_t VehicleCount() const noexcept { return vehicle_count_; }

  constexpr int32_t ChargingStationCount() const noexcept {
    return charging_station_count_;
  }

  constexpr const std::optional<int64_t>& RandomSeed() const noexcept {
    return random_seed_;
  }

private:
  void InitializeTimeStepAndTimeStepCount(const PhQ::Time& time_step) noexcept {
    time_step_ = std::max(time_step, PhQ::Time::Zero());
    if (duration_ > PhQ::Time::Zero() && time_step_ > PhQ::Time::Zero()) {
      time_step_count_ =
          static_cast<int32_t>(std::ceil(duration_ / time_step_));
    }
    time_step_ = duration_ / std::max(time_step_count_, 1);
  }

  PhQ::Time duration_ = PhQ::Time::Zero();

  PhQ::Time time_step_ = PhQ::Time::Zero();

  int32_t time_step_count_ = 0;

  int32_t vehicle_count_ = 0;

  int32_t charging_station_count_ = 0;

  std::optional<int64_t> random_seed_;
};

}  // namespace Demo
