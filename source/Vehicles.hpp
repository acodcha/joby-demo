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

// Collection of vehicles.
class Vehicles {
public:
  // Constructs an empty collection of vehicles.
  Vehicles() noexcept = default;

  // Returns whether the collection is empty.
  bool Empty() const noexcept { return data_.empty(); }

  // Returns the number of vehicles in the collection.
  std::size_t Size() const noexcept { return data_.size(); }

  // Attempts to insert a new vehicle into the collection. Returns true if the
  // new vehicle was successfully inserted, or false otherwise.
  bool Insert(const std::shared_ptr<Vehicle> vehicle) noexcept {
    if (vehicle == nullptr) {
      return false;
    }
    const std::pair<std::unordered_map<VehicleId, std::size_t>::const_iterator,
                    bool>
        result = ids_to_indices_.emplace(vehicle->Id(), data_.size());
    if (result.second) {
      data_.push_back(vehicle);
    }
    return result.second;
  }

  // Returns whether a given vehicle ID exists in this collection.
  bool Exists(const VehicleId id) const noexcept {
    return ids_to_indices_.find(id) != ids_to_indices_.cend();
  }

  // Returns the vehicle corresponding to a given vehicle ID, or nullptr if that
  // vehicle ID is not found in this collection.
  std::shared_ptr<Vehicle> At(const VehicleId id) const noexcept {
    const std::unordered_map<VehicleId, std::size_t>::const_iterator
        id_and_index = ids_to_indices_.find(id);
    if (id_and_index != ids_to_indices_.cend()) {
      return data_[id_and_index->second];
    }
    return nullptr;
  }

  // Returns a random vehicle from the collection, or nullptr if the collection
  // is empty.
  std::shared_ptr<Vehicle> Random(
      std::mt19937_64& random_generator) const noexcept {
    if (Empty()) {
      return nullptr;
    }
    std::uniform_int_distribution<> distribution(0, Size() - 1);
    return data_[distribution(random_generator)];
  }

  struct iterator : public std::vector<std::shared_ptr<Vehicle>>::iterator {
    iterator(const std::vector<std::shared_ptr<Vehicle>>::iterator i) noexcept
      : std::vector<std::shared_ptr<Vehicle>>::iterator(i) {}
  };

  iterator begin() noexcept { return iterator(data_.begin()); }

  iterator end() noexcept { return iterator(data_.end()); }

  struct const_iterator
    : public std::vector<std::shared_ptr<Vehicle>>::const_iterator {
    const_iterator(
        const std::vector<std::shared_ptr<Vehicle>>::const_iterator i) noexcept
      : std::vector<std::shared_ptr<Vehicle>>::const_iterator(i) {}
  };

  const_iterator begin() const noexcept {
    return const_iterator(data_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  const_iterator end() const noexcept { return const_iterator(data_.end()); }

  const_iterator cend() const noexcept { return const_iterator(data_.cend()); }

private:
  std::vector<std::shared_ptr<Vehicle>> data_;

  // Map of vehicle IDs to the index of the corresponding vehicle in the vector.
  std::unordered_map<VehicleId, std::size_t> ids_to_indices_;
};

}  // namespace Demo
