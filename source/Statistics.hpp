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

#include <PhQ/Length.hpp>
#include <PhQ/Time.hpp>

namespace Demo {

// Statistics of a vehicle or collection of vehicles.
// TODO: This could use a Protocol Buffer schema.
class Statistics {
public:
  // Default constructor. Initializes all properties to zero.
  constexpr Statistics() noexcept = default;

  constexpr int64_t TotalFlightCount() const noexcept {
    return total_flight_count_;
  }

  constexpr const PhQ::Time& TotalFlightDuration() const noexcept {
    return total_flight_duration_;
  }

  constexpr const PhQ::Length& TotalFlightDistance() const noexcept {
    return total_flight_distance_;
  }

  constexpr const PhQ::Time& MeanFlightDurationPerFlight() const noexcept {
    return mean_flight_duration_per_flight_;
  }

  constexpr const PhQ::Length& MeanFlightDistancePerFlight() const noexcept {
    return mean_flight_distance_per_flight_;
  }

  constexpr const PhQ::Length& TotalPassengerDistance() const noexcept {
    return total_passenger_distance_;
  }

  constexpr int64_t TotalChargingSessionsCount() const noexcept {
    return total_charging_sessions_count_;
  }

  constexpr const PhQ::Time& TotalChargingDuration() const noexcept {
    return total_charging_duration_;
  }

  constexpr const PhQ::Time&
  MeanChargingDurationPerChargingSession() const noexcept {
    return mean_charging_duration_per_charging_session_;
  }

  constexpr int64_t TotalFaultCount() const noexcept {
    return total_fault_count_;
  }

  constexpr bool operator==(const Statistics& other) const noexcept {
    return total_flight_count_ == other.total_flight_count_
           && total_flight_duration_ == other.total_flight_duration_
           && total_flight_distance_ == other.total_flight_distance_
           && mean_flight_duration_per_flight_
                  == other.mean_flight_duration_per_flight_
           && mean_flight_distance_per_flight_
                  == other.mean_flight_distance_per_flight_
           && total_passenger_distance_ == other.total_passenger_distance_
           && total_charging_sessions_count_
                  == other.total_charging_sessions_count_
           && total_charging_duration_ == other.total_charging_duration_
           && mean_charging_duration_per_charging_session_
                  == other.mean_charging_duration_per_charging_session_
           && total_fault_count_ == other.total_fault_count_;
  }

  constexpr bool operator!=(const Statistics& other) const noexcept {
    return !(*this == other);
  }

private:
  int64_t total_flight_count_ = 0;

  PhQ::Time total_flight_duration_ = PhQ::Time::Zero();

  PhQ::Length total_flight_distance_ = PhQ::Length::Zero();

  PhQ::Time mean_flight_duration_per_flight_ = PhQ::Time::Zero();

  PhQ::Length mean_flight_distance_per_flight_ = PhQ::Length::Zero();

  PhQ::Length total_passenger_distance_ = PhQ::Length::Zero();

  int64_t total_charging_sessions_count_ = 0;

  PhQ::Time total_charging_duration_ = PhQ::Time::Zero();

  PhQ::Time mean_charging_duration_per_charging_session_ = PhQ::Time::Zero();

  int64_t total_fault_count_ = 0;
};

}  // namespace Demo
