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

#include "../source/ChargingStations.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(ChargingStations, Constructor) {
  const ChargingStations charging_stations{3};
  EXPECT_EQ(charging_stations.Size(), 3);
  EXPECT_NE(charging_stations.At(0), nullptr);
  EXPECT_NE(charging_stations.At(1), nullptr);
  EXPECT_NE(charging_stations.At(2), nullptr);
  EXPECT_EQ(charging_stations.At(3), nullptr);
}

TEST(ChargingStations, Empty) {
  const ChargingStations charging_stations_a;
  EXPECT_TRUE(charging_stations_a.Empty());

  ChargingStations charging_stations_b;
  charging_stations_b.Insert(std::make_shared<ChargingStation>(111));
  EXPECT_FALSE(charging_stations_b.Empty());
}

TEST(ChargingStations, Size) {
  ChargingStations charging_stations;

  EXPECT_EQ(charging_stations.Size(), 0);

  charging_stations.Insert(std::make_shared<ChargingStation>(111));
  EXPECT_EQ(charging_stations.Size(), 1);

  charging_stations.Insert(std::make_shared<ChargingStation>(222));
  EXPECT_EQ(charging_stations.Size(), 2);
}

TEST(ChargingStations, Insert) {
  ChargingStations charging_stations;

  EXPECT_FALSE(charging_stations.Insert(nullptr));

  EXPECT_TRUE(charging_stations.Insert(std::make_shared<ChargingStation>(111)));

  EXPECT_FALSE(charging_stations.Insert(std::make_shared<ChargingStation>(111)));

  EXPECT_TRUE(charging_stations.Insert(std::make_shared<ChargingStation>(222)));
}

TEST(ChargingStations, At) {
  ChargingStations charging_stations;
  const std::shared_ptr<ChargingStation> charging_station_111 =
      std::make_shared<ChargingStation>(111);

  const std::shared_ptr<ChargingStation> charging_station_222 =
      std::make_shared<ChargingStation>(222);

  charging_stations.Insert(charging_station_111);
  charging_stations.Insert(charging_station_222);

  EXPECT_EQ(charging_stations.At(111), charging_station_111);
  EXPECT_EQ(charging_stations.At(222), charging_station_222);
  EXPECT_EQ(charging_stations.At(333), nullptr);
}

TEST(ChargingStations, LowestCount) {
  ChargingStations charging_stations;

  EXPECT_EQ(charging_stations.LowestCount(), nullptr);

  const std::shared_ptr<ChargingStation> charging_station_111 =
      std::make_shared<ChargingStation>(111);

  const std::shared_ptr<ChargingStation> charging_station_222 =
      std::make_shared<ChargingStation>(222);

  charging_stations.Insert(charging_station_111);
  charging_stations.Insert(charging_station_222);

  charging_station_111->Enqueue(7);
  charging_station_111->Enqueue(8);
  charging_station_222->Enqueue(9);
  EXPECT_EQ(charging_stations.LowestCount(), charging_station_222);

  charging_station_111->Dequeue();
  charging_station_111->Dequeue();
  EXPECT_EQ(charging_stations.LowestCount(), charging_station_111);
}

}  // namespace

}  // namespace Demo
