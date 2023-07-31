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
        /*id=*/123,
        /*manufacturer_name_english=*/"Manufacturer A",
        /*model_name_english=*/"Model B",
        /*passenger_count=*/4,
        /*cruise_speed=*/PhQ::Speed(100.0, PhQ::Unit::Speed::MilePerHour),
        /*battery_capacity=*/PhQ::Energy(200.0, PhQ::Unit::Energy::KilowattHour),
        /*charging_duration=*/PhQ::Time(0.8, PhQ::Unit::Time::Hour),
        /*fault_rate=*/PhQ::Frequency(0.1, PhQ::Unit::Frequency::PerHour),
        /*transport_energy_consumption=*/
        PhQ::TransportEnergyConsumption(
            2.0, PhQ::Unit::Force::KilowattHourPerMile));

const std::shared_ptr<Vehicle> null_vehicle = nullptr;

const std::shared_ptr<Vehicle> vehicle123 =
    std::make_shared<Vehicle>(123, model);

const std::shared_ptr<Vehicle> vehicle456 =
    std::make_shared<Vehicle>(456, model);

TEST(Vehicles, Empty) {
  const Vehicles empty;
  EXPECT_TRUE(empty.empty());

  Vehicles two;
  two.insert(vehicle123);
  two.insert(vehicle456);
  EXPECT_FALSE(two.empty());
}

TEST(Vehicles, Size) {
  const Vehicles empty;
  EXPECT_EQ(empty.size(), 0);

  Vehicles two;
  two.insert(vehicle123);
  two.insert(vehicle456);
  EXPECT_EQ(two.size(), 2);
}

TEST(Vehicles, Insert) {
  Vehicles vehicles;
  EXPECT_FALSE(vehicles.insert(null_vehicle));
  EXPECT_TRUE(vehicles.insert(vehicle123));
  EXPECT_FALSE(vehicles.insert(vehicle123));
  EXPECT_TRUE(vehicles.insert(vehicle456));
  EXPECT_FALSE(vehicles.insert(vehicle456));
}

TEST(Vehicles, At) {
  Vehicles vehicles;
  vehicles.insert(vehicle123);
  vehicles.insert(vehicle456);
  EXPECT_EQ(vehicles.at(123), vehicle123);
  EXPECT_EQ(vehicles.at(456), vehicle456);
  EXPECT_EQ(vehicles.at(789), nullptr);
}

TEST(Vehicles, Random) {
  Vehicles vehicles;
  std::random_device random_device;
  std::mt19937_64 random_generator(random_device());
  random_generator.seed(0);
  EXPECT_EQ(vehicles.random(random_generator), nullptr);
  vehicles.insert(vehicle123);
  EXPECT_EQ(vehicles.random(random_generator), vehicle123);
  vehicles.insert(vehicle456);
  EXPECT_NE(vehicles.random(random_generator), nullptr);
}

TEST(Vehicles, Iterator) {
  Vehicles vehicles;
  vehicles.insert(vehicle123);
  vehicles.insert(vehicle456);

  int64_t count1 = 0;
  for (const std::shared_ptr<Vehicle>& id_and_model : vehicles) {
    if (id_and_model != nullptr) {
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
