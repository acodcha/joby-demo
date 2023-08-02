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

#ifndef DEMO_INCLUDE_CHARGING_STATION_HPP
#define DEMO_INCLUDE_CHARGING_STATION_HPP

#include <optional>
#include <queue>
#include <unordered_set>

#include "ChargingStationId.hpp"
#include "VehicleId.hpp"

namespace Demo {

// Class representing a charging station. Vehicles queue in line and wait for
// their turn to charge at the charging station. Only the vehicle at the front
// of the queue can charge its battery.
class ChargingStation {
public:
  // Default constructor. Constructs an empty charging station with an ID of
  // zero.
  ChargingStation() noexcept = default;

  // Constructs an empty charging station with a given ID.
  ChargingStation(const ChargingStationId& id) noexcept : id_(id) {}

  // Globally-unique identifier of this charging station.
  const ChargingStationId& Id() const noexcept { return id_; }

  // Returns whether this charging station is empty.
  bool Empty() const noexcept { return queue_.empty(); }

  // Returns the count of vehicles at this charging station (either queued or
  // charging).
  std::size_t Count() const noexcept { return queue_.size(); }

  // Returns whether a given vehicle is present at this charging station (either
  // queued or charging).
  bool Exists(const VehicleId& id) const noexcept {
    return ids_.find(id) != ids_.cend();
  }

  // Returns the ID of the vehicle that is currently charging at this charging
  // station (the vehicle at the front of the queue), or nullopt if there are no
  // vehicles at this charging station.
  std::optional<VehicleId> Front() const noexcept {
    if (queue_.empty()) {
      return std::nullopt;
    }
    return queue_.front();
  }

  // Attempts to enqueue a new vehicle at the back of the queue of this charging
  // station. Returns true if the vehicle was successfully enqueued, or false if
  // the vehicle was already queued.
  bool Enqueue(const VehicleId& id) noexcept {
    const std::pair<std::unordered_set<VehicleId>::iterator, bool> result =
        ids_.insert(id);
    if (result.second) {
      queue_.push(id);
      return true;
    }
    return false;
  }

  // Attempts to remove the vehicle that is currently charging (the vehicle at
  // the front of the queue) from this charging station. Returns true if the
  // vehicle was successfully dequeued, or false if there are no vehicles at
  // this charging station.
  bool Dequeue() noexcept {
    if (queue_.empty()) {
      return false;
    }
    ids_.erase(queue_.front());
    queue_.pop();
    return true;
  }

private:
  ChargingStationId id_ = 0;

  // Queue of vehicle IDs at this charging station.
  std::queue<VehicleId> queue_;

  // Set of vehicle IDs at this charging station.
  std::unordered_set<VehicleId> ids_;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_CHARGING_STATION_HPP
