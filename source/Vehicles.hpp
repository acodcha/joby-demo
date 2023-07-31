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
#include <random>
#include <unordered_map>
#include <vector>

#include "Vehicle.hpp"

namespace Demo {

// Container for a collection of vehicles.
class Vehicles {
private:
  // Vector of vehicles.
  using VehicleVector = std::vector<std::shared_ptr<Vehicle>>;

  // Map of vehicle IDs to the index of the corresponding vehicle in the vector.
  using IdToIndex = std::unordered_map<VehicleId, std::size_t>;

public:
  // Default constructor. Initializes an empty collection of vehicles.
  Vehicles() noexcept = default;

  // Returns whether the collection is empty.
  bool empty() const noexcept { return vehicles_.empty(); }

  // Returns the number of vehicles in the collection.
  std::size_t size() const noexcept { return vehicles_.size(); }

  // Attempts to insert a new vehicle into the collection. Returns true if the
  // new vehicle was successfully inserted, or false otherwise.
  bool insert(const std::shared_ptr<Vehicle> vehicle) noexcept {
    if (vehicle != nullptr) {
      const std::pair<IdToIndex::const_iterator, bool> result =
          ids_to_indices_.emplace(vehicle->Id(), vehicles_.size());
      if (result.second) {
        vehicles_.push_back(vehicle);
      }
      return result.second;
    }
    return false;
  }

  // Returns the vehicle corresponding to a given vehicle ID, or nullptr if that
  // vehicle ID is not found in this collection.
  std::shared_ptr<Vehicle> at(const VehicleId id) const noexcept {
    const IdToIndex::const_iterator id_and_index = ids_to_indices_.find(id);
    if (id_and_index != ids_to_indices_.cend()) {
      return vehicles_[id_and_index->second];
    }
    return nullptr;
  }

  // Returns a random vehicle from the collection, or nullptr if the collection
  // is empty.
  std::shared_ptr<Vehicle> random(
      std::mt19937_64& random_generator) const noexcept {
    if (empty()) {
      return nullptr;
    }
    std::uniform_int_distribution<> distribution(0, size() - 1);
    return vehicles_[distribution(random_generator)];
  }

  struct iterator : public VehicleVector::iterator {
    iterator(const VehicleVector::iterator i) noexcept
      : VehicleVector::iterator(i) {}
  };

  iterator begin() noexcept { return iterator(vehicles_.begin()); }

  iterator end() noexcept { return iterator(vehicles_.end()); }

  struct const_iterator : public VehicleVector::const_iterator {
    const_iterator(const VehicleVector::const_iterator i) noexcept
      : VehicleVector::const_iterator(i) {}
  };

  const_iterator begin() const noexcept {
    return const_iterator(vehicles_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(vehicles_.cbegin());
  }

  const_iterator end() const noexcept {
    return const_iterator(vehicles_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(vehicles_.cend());
  }

private:
  VehicleVector vehicles_;

  IdToIndex ids_to_indices_;
};

}  // namespace Demo
