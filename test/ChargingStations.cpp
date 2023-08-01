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

#include "../source/ChargingStations.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(ChargingStations, Empty) {
  const ChargingStations charging_stations_a;
  EXPECT_TRUE(charging_stations_a.Empty());
  const std::shared_ptr<ChargingStation> charging_station_123 =
      std::make_shared<ChargingStation>(123);
  ChargingStations charging_stations_b;
  charging_stations_b.Insert(charging_station_123);
  EXPECT_FALSE(charging_stations_b.Empty());
}

TEST(ChargingStations, Size) {
  ChargingStations charging_stations;
  EXPECT_EQ(charging_stations.Size(), 0);
  charging_stations.Insert(std::make_shared<ChargingStation>(123));
  EXPECT_EQ(charging_stations.Size(), 1);
  charging_stations.Insert(std::make_shared<ChargingStation>(456));
  EXPECT_EQ(charging_stations.Size(), 2);
}

TEST(ChargingStations, Insert) {
  ChargingStations charging_stations;
  EXPECT_FALSE(charging_stations.Insert(nullptr));
  EXPECT_TRUE(charging_stations.Insert(std::make_shared<ChargingStation>(123)));
  EXPECT_FALSE(
      charging_stations.Insert(std::make_shared<ChargingStation>(123)));
  EXPECT_TRUE(charging_stations.Insert(std::make_shared<ChargingStation>(456)));
}

TEST(ChargingStations, At) {
  ChargingStations charging_stations;
  const std::shared_ptr<ChargingStation> charging_station_123 =
      std::make_shared<ChargingStation>(123);
  const std::shared_ptr<ChargingStation> charging_station_456 =
      std::make_shared<ChargingStation>(456);
  charging_stations.Insert(charging_station_123);
  charging_stations.Insert(charging_station_456);
  EXPECT_EQ(charging_stations.At(123), charging_station_123);
  EXPECT_EQ(charging_stations.At(456), charging_station_456);
  EXPECT_EQ(charging_stations.At(789), nullptr);
}

TEST(ChargingStations, LowestCount) {
  ChargingStations charging_stations;
  EXPECT_EQ(charging_stations.LowestCount(), nullptr);
  const std::shared_ptr<ChargingStation> charging_station_123 =
      std::make_shared<ChargingStation>(123);
  const std::shared_ptr<ChargingStation> charging_station_456 =
      std::make_shared<ChargingStation>(456);
  charging_stations.Insert(charging_station_123);
  charging_stations.Insert(charging_station_456);
  charging_station_123->Enqueue(7);
  charging_station_123->Enqueue(8);
  charging_station_456->Enqueue(9);
  EXPECT_EQ(charging_stations.LowestCount(), charging_station_456);
  charging_station_123->Dequeue();
  charging_station_123->Dequeue();
  EXPECT_EQ(charging_stations.LowestCount(), charging_station_123);
}

}  // namespace

}  // namespace Demo
