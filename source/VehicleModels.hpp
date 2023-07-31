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

#include <map>
#include <memory>
#include <random>
#include <vector>

#include "VehicleModel.hpp"

namespace Demo {

// Container for a collection of vehicle models.
class VehicleModels {
private:
  // Vector of vehicle models.
  using ModelVector = std::vector<std::shared_ptr<const VehicleModel>>;

  // Map of vehicle model IDs to the index of the corresponding vehicle model in
  // the vector. This implementation assumes that only a small number of vehicle
  // models are used, say 20 or fewer. If more vehicle models are used, this
  // implementation should instead use a hash map rather than a binary tree map.
  using IdToIndex = std::map<VehicleModelId, std::size_t>;

public:
  // Default constructor. Initializes an empty collection of vehicle models.
  VehicleModels() noexcept = default;

  // Returns whether the collection is empty.
  bool empty() const noexcept { return models_.empty(); }

  // Returns the number of vehicle models in the collection.
  std::size_t size() const noexcept { return models_.size(); }

  // Attempts to insert a new vehicle model into the collection. Returns true if
  // the new vehicle model was successfully inserted, or false otherwise.
  bool insert(const std::shared_ptr<const VehicleModel> model) noexcept {
    if (model != nullptr) {
      const std::pair<IdToIndex::const_iterator, bool> result =
          ids_to_indices_.emplace(model->Id(), models_.size());
      if (result.second) {
        models_.push_back(model);
      }
      return result.second;
    }
    return false;
  }

  // Returns the vehicle model corresponding to a given vehicle model ID, or
  // nullptr if that vehicle model ID is not found in this collection.
  std::shared_ptr<const VehicleModel> at(
      const VehicleModelId id) const noexcept {
    const IdToIndex::const_iterator id_and_index = ids_to_indices_.find(id);
    if (id_and_index != ids_to_indices_.cend()) {
      return models_[id_and_index->second];
    }
    return nullptr;
  }

  // Returns a random vehicle model from the collection, or nullptr if the
  // collection is empty.
  std::shared_ptr<const VehicleModel> random(
      std::mt19937_64& random_generator) const noexcept {
    if (empty()) {
      return nullptr;
    }
    std::uniform_int_distribution<> distribution(0, size() - 1);
    return models_[distribution(random_generator)];
  }

  struct const_iterator : public ModelVector::const_iterator {
    const_iterator(const ModelVector::const_iterator i) noexcept
      : ModelVector::const_iterator(i) {}
  };

  const_iterator begin() const noexcept {
    return const_iterator(models_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(models_.cbegin());
  }

  const_iterator end() const noexcept { return const_iterator(models_.end()); }

  const_iterator cend() const noexcept {
    return const_iterator(models_.cend());
  }

private:
  ModelVector models_;

  IdToIndex ids_to_indices_;
};

}  // namespace Demo
