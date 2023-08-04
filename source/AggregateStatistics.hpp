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

#ifndef DEMO_INCLUDE_AGGREGATE_STATISTICS_HPP
#define DEMO_INCLUDE_AGGREGATE_STATISTICS_HPP

#include <iostream>
#include <map>

#include "Statistics.hpp"
#include "Vehicles.hpp"

namespace Demo {

// Collection of vehicle model aggregate statistics.
class AggregateStatistics {
public:
  // Constructs an empty collection of aggregate statistics.
  AggregateStatistics() noexcept = default;

  // Constructs the collection of aggregate statistics of each vehicle model by
  // aggregating the statistics of the individual vehicles of each model.
  AggregateStatistics(const Vehicles& vehicles) noexcept {
    for (const std::shared_ptr<Vehicle>& vehicle : vehicles) {
      if (vehicle != nullptr && vehicle->Model() != nullptr) {
        // Attempt to insert this vehicle's statistics into the aggregate
        // vehicle model statistics map.
        const std::pair<std::map<VehicleModelId, Statistics>::iterator, bool>
            result = vehicle_model_ids_to_statistics_.emplace(
                vehicle->Model()->Id(), vehicle->Statistics());

        if (!result.second) {
          // In this case, this vehicle model is already in the map, so
          // aggregate its existing statistics with this individual vehicle's
          // statistics.
          result.first->second.Aggregate(vehicle->Statistics());
        }
      }
    }

    std::cout << "Computed the aggregate statistics." << std::endl;
  }

  // Returns whether the collection is empty.
  bool Empty() const noexcept {
    return vehicle_model_ids_to_statistics_.empty();
  }

  // Returns the number of vehicle models in the collection.
  std::size_t Size() const noexcept {
    return vehicle_model_ids_to_statistics_.size();
  }

  // Returns the aggregate statistics corresponding to a given vehicle model ID,
  // or std::nullopt if that vehicle model ID is not found in this collection.
  const std::optional<Statistics> At(const VehicleModelId id) const noexcept {
    const std::map<VehicleModelId, Statistics>::const_iterator
        vehicle_model_id_and_statistics =
            vehicle_model_ids_to_statistics_.find(id);

    if (vehicle_model_id_and_statistics
        != vehicle_model_ids_to_statistics_.cend()) {
      return vehicle_model_id_and_statistics->second;
    }

    return std::nullopt;
  }

  struct const_iterator
    : public std::map<VehicleModelId, Statistics>::const_iterator {
    const_iterator(
        const std::map<VehicleModelId, Statistics>::const_iterator i) noexcept
      : std::map<VehicleModelId, Statistics>::const_iterator(i) {}
  };

  const_iterator begin() const noexcept {
    return const_iterator(vehicle_model_ids_to_statistics_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(vehicle_model_ids_to_statistics_.cbegin());
  }

  const_iterator end() const noexcept {
    return const_iterator(vehicle_model_ids_to_statistics_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(vehicle_model_ids_to_statistics_.cend());
  }

private:
  // Map of vehicle model IDs to their corresponding aggregate statistics. These
  // statistics are aggregated at the end of the simulation from all vehicles of
  // each vehicle model. This implementation assumes that only a small number of
  // vehicle models are used, say 20 or fewer. If more vehicle models are used,
  // this implementation should instead use a hash map rather than a binary tree
  // map.
  std::map<VehicleModelId, Statistics> vehicle_model_ids_to_statistics_;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_AGGREGATE_STATISTICS_HPP
