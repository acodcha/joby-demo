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

#include "../source/ChargingStation.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(ChargingStation, Id) {
  const ChargingStation station0;
  EXPECT_EQ(station0.Id(), 0);
  const ChargingStation station789{789};
  EXPECT_EQ(station789.Id(), 789);
}

TEST(ChargingStation, Empty) {
  ChargingStation station;
  EXPECT_TRUE(station.Empty());
  station.Enqueue(123);
  EXPECT_FALSE(station.Empty());
}

TEST(ChargingStation, Count) {
  ChargingStation station;
  EXPECT_EQ(station.Count(), 0);
  station.Enqueue(123);
  EXPECT_EQ(station.Count(), 1);
  station.Enqueue(456);
  EXPECT_EQ(station.Count(), 2);
  station.Dequeue();
  EXPECT_EQ(station.Count(), 1);
  station.Dequeue();
  EXPECT_EQ(station.Count(), 0);
}

TEST(ChargingStation, Exists) {
  ChargingStation station;
  station.Enqueue(123);
  station.Enqueue(456);
  EXPECT_TRUE(station.Exists(123));
  EXPECT_TRUE(station.Exists(456));
  EXPECT_FALSE(station.Exists(789));
}

TEST(ChargingStation, Front) {
  ChargingStation station;
  EXPECT_EQ(station.Front(), std::nullopt);
  station.Enqueue(123);
  EXPECT_EQ(station.Front(), 123);
  station.Enqueue(456);
  EXPECT_EQ(station.Front(), 123);
  station.Dequeue();
  EXPECT_EQ(station.Front(), 456);
  station.Dequeue();
  EXPECT_EQ(station.Front(), std::nullopt);
}

TEST(ChargingStation, Enqueue) {
  ChargingStation station;
  EXPECT_TRUE(station.Enqueue(123));
  EXPECT_FALSE(station.Enqueue(123));
  EXPECT_TRUE(station.Enqueue(456));
  EXPECT_FALSE(station.Enqueue(456));
}

TEST(ChargingStation, Dequeue) {
  ChargingStation station;
  EXPECT_FALSE(station.Dequeue());
  station.Enqueue(123);
  station.Enqueue(456);
  EXPECT_TRUE(station.Dequeue());
  EXPECT_TRUE(station.Dequeue());
  EXPECT_FALSE(station.Dequeue());
}

}  // namespace

}  // namespace Demo
