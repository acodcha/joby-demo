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

#include "../source/VehicleModels.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

const std::shared_ptr<const VehicleModel> model111 = std::make_shared<
    const VehicleModel>(
    /*id=*/111,
    /*manufacturer_name_english=*/"Manufacturer A",
    /*model_name_english=*/"Model A",
    /*passenger_count=*/4,
    /*cruise_speed=*/PhQ::Speed(120.0, PhQ::Unit::Speed::MilePerHour),
    /*battery_capacity=*/PhQ::Energy(320.0, PhQ::Unit::Energy::KilowattHour),
    /*charging_duration=*/PhQ::Time(0.6, PhQ::Unit::Time::Hour),
    /*fault_rate=*/PhQ::Frequency(0.25, PhQ::Unit::Frequency::PerHour),
    /*transport_energy_consumption=*/
    PhQ::TransportEnergyConsumption(
        1.6, PhQ::Unit::Force::KilowattHourPerMile));

const std::shared_ptr<const VehicleModel> model222 = std::make_shared<
    const VehicleModel>(
    /*id=*/222,
    /*manufacturer_name_english=*/"Manufacturer B",
    /*model_name_english=*/"Model B",
    /*passenger_count=*/4,
    /*cruise_speed=*/PhQ::Speed(110.0, PhQ::Unit::Speed::MilePerHour),
    /*battery_capacity=*/PhQ::Energy(180.0, PhQ::Unit::Energy::KilowattHour),
    /*charging_duration=*/PhQ::Time(0.9, PhQ::Unit::Time::Hour),
    /*fault_rate=*/PhQ::Frequency(0.11, PhQ::Unit::Frequency::PerHour),
    /*transport_energy_consumption=*/
    PhQ::TransportEnergyConsumption(
        2.2, PhQ::Unit::Force::KilowattHourPerMile));

TEST(VehicleModels, Empty) {
  const VehicleModels empty_models;
  EXPECT_TRUE(empty_models.Empty());
  VehicleModels two_models;
  two_models.Insert(model111);
  two_models.Insert(model222);
  EXPECT_FALSE(two_models.Empty());
}

TEST(VehicleModels, Size) {
  const VehicleModels empty_models;
  EXPECT_EQ(empty_models.Size(), 0);
  VehicleModels two_models;
  two_models.Insert(model111);
  two_models.Insert(model222);
  EXPECT_EQ(two_models.Size(), 2);
}

TEST(VehicleModels, Insert) {
  VehicleModels models;
  EXPECT_FALSE(models.Insert(nullptr));
  EXPECT_TRUE(models.Insert(model111));
  EXPECT_FALSE(models.Insert(model111));
  EXPECT_TRUE(models.Insert(model222));
  EXPECT_FALSE(models.Insert(model222));
}

TEST(VehicleModels, At) {
  VehicleModels models;
  models.Insert(model111);
  models.Insert(model222);
  EXPECT_EQ(models.At(111), model111);
  EXPECT_EQ(models.At(222), model222);
  EXPECT_EQ(models.At(789), nullptr);
}

TEST(VehicleModels, Random) {
  VehicleModels models;
  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());
  random_generator.seed(0);
  EXPECT_EQ(models.Random(random_generator), nullptr);
  models.Insert(model111);
  EXPECT_EQ(models.Random(random_generator), model111);
  models.Insert(model222);
  EXPECT_NE(models.Random(random_generator), nullptr);
}

TEST(VehicleModels, Iterator) {
  VehicleModels models;
  models.Insert(model111);
  models.Insert(model222);

  int64_t count1 = 0;
  for (const std::shared_ptr<const VehicleModel>& model : models) {
    if (model != nullptr) {
      ++count1;
    }
  }
  EXPECT_EQ(count1, 2);

  int64_t count2 = 0;
  for (VehicleModels::const_iterator it = models.cbegin(); it != models.cend();
       ++it) {
    ++count2;
  }
  EXPECT_EQ(count2, 2);

  int64_t count3 = 0;
  for (VehicleModels::const_iterator it = models.begin(); it != models.end();
       ++it) {
    ++count3;
  }
  EXPECT_EQ(count3, 2);
}

}  // namespace

}  // namespace Demo
