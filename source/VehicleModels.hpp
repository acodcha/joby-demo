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

#ifndef DEMO_INCLUDE_VEHICLE_MODELS_HPP
#define DEMO_INCLUDE_VEHICLE_MODELS_HPP

#include <map>
#include <memory>
#include <random>
#include <vector>

#include "VehicleModel.hpp"

namespace Demo {

// Collection of vehicle models.
class VehicleModels {
public:
  // Constructs an empty collection of vehicle models.
  VehicleModels() noexcept = default;

  // Returns whether the collection is empty.
  bool Empty() const noexcept { return vehicle_models_.empty(); }

  // Returns the number of vehicle models in the collection.
  std::size_t Size() const noexcept { return vehicle_models_.size(); }

  // Attempts to insert a new vehicle model into the collection. Returns true if
  // the new vehicle model was successfully inserted, or false otherwise.
  bool Insert(const std::shared_ptr<const VehicleModel> model) noexcept {
    if (model == nullptr) {
      return false;
    }

    const std::pair<std::map<VehicleModelId, std::size_t>::const_iterator, bool>
        result = vehicle_model_ids_to_indices_.emplace(
            model->Id(), vehicle_models_.size());

    if (result.second) {
      vehicle_models_.push_back(model);
    }

    return result.second;
  }

  // Returns the vehicle model corresponding to a given vehicle model ID, or
  // nullptr if that vehicle model ID is not found in this collection.
  std::shared_ptr<const VehicleModel> At(
      const VehicleModelId id) const noexcept {
    const std::map<VehicleModelId, std::size_t>::const_iterator id_and_index =
        vehicle_model_ids_to_indices_.find(id);

    if (id_and_index != vehicle_model_ids_to_indices_.cend()) {
      return vehicle_models_[id_and_index->second];
    }

    return nullptr;
  }

  // Returns a random vehicle model from the collection, or nullptr if the
  // collection is empty.
  std::shared_ptr<const VehicleModel> Random(
      std::mt19937_64& random_generator) const noexcept {
    if (Empty()) {
      return nullptr;
    }

    std::uniform_int_distribution<std::size_t> random_distribution(
        0, Size() - 1);

    return vehicle_models_[random_distribution(random_generator)];
  }

  struct const_iterator
    : public std::vector<std::shared_ptr<const VehicleModel>>::const_iterator {
    const_iterator(
        const std::vector<std::shared_ptr<const VehicleModel>>::const_iterator
            i) noexcept
      : std::vector<std::shared_ptr<const VehicleModel>>::const_iterator(i) {}
  };

  const_iterator begin() const noexcept {
    return const_iterator(vehicle_models_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(vehicle_models_.cbegin());
  }

  const_iterator end() const noexcept {
    return const_iterator(vehicle_models_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(vehicle_models_.cend());
  }

private:
  std::vector<std::shared_ptr<const VehicleModel>> vehicle_models_;

  // Map of vehicle model IDs to the index of the corresponding vehicle model in
  // the vector. This implementation assumes that only a small number of vehicle
  // models are used, say 20 or fewer. If more vehicle models are used, this
  // implementation should instead use a hash map rather than a binary tree map.
  std::map<VehicleModelId, std::size_t> vehicle_model_ids_to_indices_;
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_VEHICLE_MODELS_HPP
