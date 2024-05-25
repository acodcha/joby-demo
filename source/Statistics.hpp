// Copyright © 2023-2024 Alexandre Coderre-Chabot
//
// This file is part of Joby Demonstration, a simple demonstration of C++ principles in the context
// of a vehicle fleet simulation.
//
// Joby Demonstration is hosted at:
//     https://github.com/acodcha/joby-demo
//
// This file is licensed under the MIT license (https://mit-license.org). Permission is hereby
// granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//   - The above copyright notice and this permission notice shall be included in all copies or
//     substantial portions of the Software.
//   - THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
//     BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//     NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//     DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//     FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef DEMO_INCLUDE_STATISTICS_HPP
#define DEMO_INCLUDE_STATISTICS_HPP

#include <PhQ/Length.hpp>
#include <PhQ/Time.hpp>

namespace Demo {

// Statistics of a vehicle or collection of vehicles.
// TODO: This could use a Protocol Buffer schema.
class Statistics {
public:
  // Default constructor. Initializes all properties to zero.
  constexpr Statistics() noexcept = default;

  // Total count of flights.
  constexpr int64_t TotalFlightCount() const noexcept {
    return total_flight_count_;
  }

  // Total duration of all flights.
  constexpr const PhQ::Time<>& TotalFlightDuration() const noexcept {
    return total_flight_duration_;
  }

  // Total distance of all flights.
  constexpr const PhQ::Length<>& TotalFlightDistance() const noexcept {
    return total_flight_distance_;
  }

  // Total passenger-distance of all flights. This is the product of the passenger count and the
  // total flight distance.
  constexpr const PhQ::Length<>& TotalFlightPassengerDistance() const noexcept {
    return total_flight_passenger_distance_;
  }

  // Arithmetic mean of the duration of all flights. This is the total flight duration divided by
  // the number of flights.
  constexpr const PhQ::Time<>& MeanFlightDuration() const noexcept {
    return mean_flight_duration_;
  }

  // Arithmetic mean of the distance of all flights. This is the total flight distance divided by
  // the number of flights.
  constexpr const PhQ::Length<>& MeanFlightDistance() const noexcept {
    return mean_flight_distance_;
  }

  // Total count of charging sessions.
  constexpr int64_t TotalChargingSessionCount() const noexcept {
    return total_charging_session_count_;
  }

  // Total duration of all charging sessions.
  constexpr const PhQ::Time<>& TotalChargingDuration() const noexcept {
    return total_charging_duration_;
  }

  // Arithmetic mean of the duration of all charging sessions. This is the total duration of all
  // charging sessions divided by the number of charging sessions.
  constexpr const PhQ::Time<>& MeanChargingDuration() const noexcept {
    return mean_charging_duration_;
  }

  // Total count of faults.
  constexpr int64_t TotalFaultCount() const noexcept {
    return total_fault_count_;
  }

  // Increments the total flight count by one and recalculates dependent statistics.
  void IncrementTotalFlightCount() noexcept {
    ++total_flight_count_;

    mean_flight_duration_ = total_flight_duration_ / total_flight_count_;

    mean_flight_distance_ = total_flight_distance_ / total_flight_count_;
  }

  // Modifies the total flight duration and distance by given differences and recalculates dependent
  // statistics.
  void ModifyTotalFlightDurationAndDistance(
      const int32_t passenger_count, const PhQ::Time<>& duration_difference,
      const PhQ::Length<>& distance_difference) noexcept {
    total_flight_duration_ += duration_difference;

    mean_flight_duration_ = total_flight_duration_ / total_flight_count_;

    total_flight_distance_ += distance_difference;

    mean_flight_distance_ = total_flight_distance_ / total_flight_count_;

    total_flight_passenger_distance_ += static_cast<double>(passenger_count) * distance_difference;
  }

  // Increments the total charging session count by one and recalculates dependent statistics.
  void IncrementTotalChargingSessionCount() noexcept {
    ++total_charging_session_count_;

    mean_charging_duration_ = total_charging_duration_ / total_charging_session_count_;
  }

  // Modifies the total charging session duration by a given difference and recalculates dependent
  // statistics.
  void ModifyTotalChargingSessionDuration(const PhQ::Time<>& duration_difference) noexcept {
    total_charging_duration_ += duration_difference;

    mean_charging_duration_ = total_charging_duration_ / total_charging_session_count_;
  }

  // Modifies the total fault count by a given difference.
  void ModifyTotalFaultCount(const int64_t difference) noexcept {
    total_fault_count_ += difference;
  }

  // Aggregates data from another set of statistics into this set of statistics.
  void Aggregate(const Statistics& other) noexcept {
    total_flight_count_ += other.total_flight_count_;

    total_flight_duration_ += other.total_flight_duration_;

    total_flight_distance_ += other.total_flight_distance_;

    total_flight_passenger_distance_ += other.total_flight_passenger_distance_;

    mean_flight_duration_ = total_flight_duration_ / total_flight_count_;

    mean_flight_distance_ = total_flight_distance_ / total_flight_count_;

    total_charging_session_count_ += other.total_charging_session_count_;

    total_charging_duration_ += other.total_charging_duration_;

    mean_charging_duration_ = total_charging_duration_ / total_charging_session_count_;

    total_fault_count_ += other.total_fault_count_;
  }

  constexpr bool operator==(const Statistics& other) const noexcept {
    return total_flight_count_ == other.total_flight_count_
           && total_flight_duration_ == other.total_flight_duration_
           && total_flight_distance_ == other.total_flight_distance_
           && total_flight_passenger_distance_ == other.total_flight_passenger_distance_
           && mean_flight_duration_ == other.mean_flight_duration_
           && mean_flight_distance_ == other.mean_flight_distance_
           && total_charging_session_count_ == other.total_charging_session_count_
           && total_charging_duration_ == other.total_charging_duration_
           && mean_charging_duration_ == other.mean_charging_duration_
           && total_fault_count_ == other.total_fault_count_;
  }

  constexpr bool operator!=(const Statistics& other) const noexcept {
    return !(*this == other);
  }

private:
  int64_t total_flight_count_ = 0;

  PhQ::Time<> total_flight_duration_ = PhQ::Time<>::Zero();

  PhQ::Length<> total_flight_distance_ = PhQ::Length<>::Zero();

  PhQ::Length<> total_flight_passenger_distance_ = PhQ::Length<>::Zero();

  PhQ::Time<> mean_flight_duration_ = PhQ::Time<>::Zero();

  PhQ::Length<> mean_flight_distance_ = PhQ::Length<>::Zero();

  int64_t total_charging_session_count_ = 0;

  PhQ::Time<> total_charging_duration_ = PhQ::Time<>::Zero();

  PhQ::Time<> mean_charging_duration_ = PhQ::Time<>::Zero();

  int64_t total_fault_count_ = 0;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_STATISTICS_HPP
