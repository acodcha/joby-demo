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

#ifndef DEMO_INCLUDE_CHARGING_STATIONS_HPP
#define DEMO_INCLUDE_CHARGING_STATIONS_HPP

#include <limits>
#include <map>
#include <memory>

#include "ChargingStation.hpp"

namespace Demo {

// Collection of charging stations.
class ChargingStations {
public:
  // Constructs an empty collection of charging stations.
  ChargingStations() noexcept = default;

  // Constructs a collection containing a given number of charging stations.
  ChargingStations(const int32_t count) noexcept {
    ChargingStationId id = 0;

    for (int32_t index = 0; index < count; ++index) {
      Insert(std::make_shared<ChargingStation>(id));
      ++id;
    }
  }

  // Returns whether the collection is empty.
  bool Empty() const noexcept {
    return data_.empty();
  }

  // Returns the number of charging stations in the collection.
  std::size_t Size() const noexcept {
    return data_.size();
  }

  // Attempts to insert a new charging station into the collection. Returns true if the new charging
  // station was successfully inserted, or false otherwise.
  bool Insert(const std::shared_ptr<ChargingStation> charging_station) noexcept {
    if (charging_station == nullptr) {
      return false;
    }

    const std::pair<std::map<ChargingStationId, std::shared_ptr<ChargingStation>>::const_iterator,
                    bool>
        result = data_.emplace(charging_station->Id(), charging_station);

    return result.second;
  }

  // Returns the charging station corresponding to a given charging station ID, or nullptr if that
  // charging station ID is not found in this collection.
  std::shared_ptr<ChargingStation> At(const ChargingStationId id) const noexcept {
    const std::map<ChargingStationId, std::shared_ptr<ChargingStation>>::const_iterator
        id_and_data = data_.find(id);

    if (id_and_data != data_.cend()) {
      return id_and_data->second;
    }

    return nullptr;
  }

  // Returns the charging station in the collection with the lowest current count of vehicles
  // (either queued or charging), or nullptr if the collection is empty. If multiple charging
  // stations are tied for the lowest count, returns the first one encountered while traversing the
  // collection.
  std::shared_ptr<ChargingStation> LowestCount() const noexcept {
    std::shared_ptr<ChargingStation> best = nullptr;

    std::size_t lowest_count = std::numeric_limits<std::size_t>::max();

    for (const std::pair<const ChargingStationId, std::shared_ptr<ChargingStation>>& element :
         data_) {
      if (element.second->Count() < lowest_count) {
        best = element.second;
        lowest_count = element.second->Count();
      }
    }

    return best;
  }

private:
  // Map of charging station IDs to their corresponding charging stations. This implementation
  // assumes that only a small number of charging stations are used, say 20 or fewer. If more
  // charging stations are used, this implementation should instead use a hash map rather than a
  // binary tree map.
  std::map<ChargingStationId, std::shared_ptr<ChargingStation>> data_;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_CHARGING_STATIONS_HPP
