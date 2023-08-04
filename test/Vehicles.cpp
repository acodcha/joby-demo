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

#include "../source/Vehicles.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

const std::shared_ptr<const VehicleModel> model =
    std::make_shared<const VehicleModel>(
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

const std::shared_ptr<Vehicle> vehicle222 =
    std::make_shared<Vehicle>(222, model);

const std::shared_ptr<Vehicle> vehicle333 =
    std::make_shared<Vehicle>(333, model);

TEST(Vehicles, RandomConstructor) {
  VehicleModels vehicle_models;
  vehicle_models.Insert(model);

  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());
  random_generator.seed(0);

  const Vehicles vehicles{4, vehicle_models, random_generator};

  EXPECT_EQ(vehicles.Size(), 4);
  EXPECT_NE(vehicles.At(0), nullptr);
  EXPECT_NE(vehicles.At(1), nullptr);
  EXPECT_NE(vehicles.At(2), nullptr);
  EXPECT_NE(vehicles.At(3), nullptr);
  EXPECT_EQ(vehicles.At(4), nullptr);
}

TEST(Vehicles, Empty) {
  const Vehicles vehicles0;
  EXPECT_TRUE(vehicles0.Empty());

  Vehicles vehicles1;
  vehicles1.Insert(vehicle222);
  vehicles1.Insert(vehicle333);
  EXPECT_FALSE(vehicles1.Empty());
}

TEST(Vehicles, Size) {
  const Vehicles vehicles0;
  EXPECT_EQ(vehicles0.Size(), 0);

  Vehicles vehicles1;
  vehicles1.Insert(vehicle222);
  vehicles1.Insert(vehicle333);
  EXPECT_EQ(vehicles1.Size(), 2);
}

TEST(Vehicles, Insert) {
  Vehicles vehicles;
  EXPECT_FALSE(vehicles.Insert(nullptr));
  EXPECT_TRUE(vehicles.Insert(vehicle222));
  EXPECT_FALSE(vehicles.Insert(vehicle222));
  EXPECT_TRUE(vehicles.Insert(vehicle333));
  EXPECT_FALSE(vehicles.Insert(vehicle333));
}

TEST(Vehicles, Exists) {
  Vehicles vehicles;
  vehicles.Insert(vehicle222);
  vehicles.Insert(vehicle333);
  EXPECT_TRUE(vehicles.Exists(222));
  EXPECT_TRUE(vehicles.Exists(333));
  EXPECT_FALSE(vehicles.Exists(444));
}

TEST(Vehicles, At) {
  Vehicles vehicles;
  vehicles.Insert(vehicle222);
  vehicles.Insert(vehicle333);
  EXPECT_EQ(vehicles.At(222), vehicle222);
  EXPECT_EQ(vehicles.At(333), vehicle333);
  EXPECT_EQ(vehicles.At(444), nullptr);
}

TEST(Vehicles, Random) {
  Vehicles vehicles;

  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());
  random_generator.seed(0);

  EXPECT_EQ(vehicles.Random(random_generator), nullptr);

  vehicles.Insert(vehicle222);
  EXPECT_EQ(vehicles.Random(random_generator), vehicle222);

  vehicles.Insert(vehicle333);
  EXPECT_NE(vehicles.Random(random_generator), nullptr);
}

TEST(Vehicles, Iterator) {
  Vehicles vehicles;
  vehicles.Insert(vehicle222);
  vehicles.Insert(vehicle333);

  int64_t count1 = 0;
  for (const std::shared_ptr<Vehicle>& vehicle : vehicles) {
    if (vehicle != nullptr) {
      ++count1;
    }
  }
  EXPECT_EQ(count1, 2);

  int64_t count2 = 0;
  for (Vehicles::const_iterator it = vehicles.cbegin(); it != vehicles.cend();
       ++it) {
    ++count2;
  }
  EXPECT_EQ(count2, 2);

  int64_t count3 = 0;
  for (Vehicles::iterator it = vehicles.begin(); it != vehicles.end(); ++it) {
    ++count3;
  }
  EXPECT_EQ(count3, 2);
}

}  // namespace

}  // namespace Demo
