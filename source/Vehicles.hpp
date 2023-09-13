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

#ifndef DEMO_INCLUDE_VEHICLES_HPP
#define DEMO_INCLUDE_VEHICLES_HPP

#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <unordered_map>
#include <vector>

#include "Vehicle.hpp"
#include "VehicleModels.hpp"

namespace Demo {

// Collection of vehicles.
class Vehicles {
public:
  // Constructs an empty collection of vehicles.
  Vehicles() noexcept = default;

  // Constructs a collection of vehicles by randomly generating a given number
  // of vehicles from a collection of available vehicle models.
  Vehicles(const int32_t count, const VehicleModels& vehicle_models,
           std::mt19937_64& random_generator) noexcept {
    VehicleId id = 0;

    for (int32_t vehicle_index = 0; vehicle_index < count; ++vehicle_index) {
      const std::shared_ptr<const VehicleModel> vehicle_model =
          vehicle_models.Random(random_generator);

      if (vehicle_model != nullptr) {
        const std::pair<std::map<VehicleModelId, std::size_t>::iterator, bool>
            result =
                vehicle_model_ids_to_counts_.emplace(vehicle_model->Id(), 1);

        if (!result.second) {
          ++result.first->second;
        }

        Insert(std::make_shared<Vehicle>(id, vehicle_model));

        ++id;
      }
    }

    PrintVehicleModelCounts(vehicle_models);
  }

  // Returns whether the collection is empty.
  bool Empty() const noexcept {
    return vehicles_.empty();
  }

  // Returns the number of vehicles in the collection.
  std::size_t Size() const noexcept {
    return vehicles_.size();
  }

  // Attempts to insert a new vehicle into the collection. Returns true if the
  // new vehicle was successfully inserted, or false otherwise.
  bool Insert(const std::shared_ptr<Vehicle> vehicle) noexcept {
    if (vehicle == nullptr) {
      return false;
    }

    const std::pair<std::unordered_map<VehicleId, std::size_t>::const_iterator,
                    bool>
        result =
            vehicle_ids_to_indices_.emplace(vehicle->Id(), vehicles_.size());

    if (result.second) {
      vehicles_.push_back(vehicle);
    }

    return result.second;
  }

  // Returns whether a given vehicle ID exists in this collection.
  bool Exists(const VehicleId id) const noexcept {
    return vehicle_ids_to_indices_.find(id) != vehicle_ids_to_indices_.cend();
  }

  // Returns the vehicle corresponding to a given vehicle ID, or nullptr if that
  // vehicle ID is not found in this collection.
  std::shared_ptr<Vehicle> At(const VehicleId id) const noexcept {
    const std::unordered_map<VehicleId, std::size_t>::const_iterator
        id_and_index = vehicle_ids_to_indices_.find(id);

    if (id_and_index != vehicle_ids_to_indices_.cend()) {
      return vehicles_[id_and_index->second];
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

    return vehicles_[distribution(random_generator)];
  }

  struct iterator : public std::vector<std::shared_ptr<Vehicle>>::iterator {
    iterator(const std::vector<std::shared_ptr<Vehicle>>::iterator i) noexcept
      : std::vector<std::shared_ptr<Vehicle>>::iterator(i) {}
  };

  iterator begin() noexcept {
    return iterator(vehicles_.begin());
  }

  iterator end() noexcept {
    return iterator(vehicles_.end());
  }

  struct const_iterator
    : public std::vector<std::shared_ptr<Vehicle>>::const_iterator {
    const_iterator(
        const std::vector<std::shared_ptr<Vehicle>>::const_iterator i) noexcept
      : std::vector<std::shared_ptr<Vehicle>>::const_iterator(i) {}
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
  // Prints the number of vehicles of each vehicle model to the console.
  void PrintVehicleModelCounts(
      const VehicleModels& vehicle_models) const noexcept {
    if (vehicle_model_ids_to_counts_.empty()) {
      return;
    }

    std::cout << "Vehicle models in this simulation:" << std::endl;

    for (const std::pair<const VehicleModelId, std::size_t>&
             vehicle_model_id_and_count : vehicle_model_ids_to_counts_) {
      const std::shared_ptr<const VehicleModel> vehicle_model =
          vehicle_models.At(vehicle_model_id_and_count.first);

      if (vehicle_model != nullptr) {
        std::cout
            << "- " << vehicle_model->ManufacturerNameEnglish() << ", "
            << vehicle_model->ModelNameEnglish() << ": "
            << vehicle_model_id_and_count.second << " vehicles" << std::endl;
      }
    }
  }

  // Map of vehicle model IDs to the count of vehicles of that model.
  std::map<VehicleModelId, std::size_t> vehicle_model_ids_to_counts_;

  // Vehicles in this simulation.
  std::vector<std::shared_ptr<Vehicle>> vehicles_;

  // Map of vehicle IDs to the index of the corresponding vehicle in the vector.
  std::unordered_map<VehicleId, std::size_t> vehicle_ids_to_indices_;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_VEHICLES_HPP
