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

#include "../source/ChargingStation.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(ChargingStation, Id) {
  const ChargingStation station0;
  EXPECT_EQ(station0.Id(), 0);
  const ChargingStation station333{333};
  EXPECT_EQ(station333.Id(), 333);
}

TEST(ChargingStation, Empty) {
  ChargingStation station;
  EXPECT_TRUE(station.Empty());
  station.Enqueue(111);
  EXPECT_FALSE(station.Empty());
}

TEST(ChargingStation, Count) {
  ChargingStation station;
  EXPECT_EQ(station.Count(), 0);
  station.Enqueue(111);
  EXPECT_EQ(station.Count(), 1);
  station.Enqueue(222);
  EXPECT_EQ(station.Count(), 2);
  station.Dequeue();
  EXPECT_EQ(station.Count(), 1);
  station.Dequeue();
  EXPECT_EQ(station.Count(), 0);
}

TEST(ChargingStation, Exists) {
  ChargingStation station;
  station.Enqueue(111);
  station.Enqueue(222);
  EXPECT_TRUE(station.Exists(111));
  EXPECT_TRUE(station.Exists(222));
  EXPECT_FALSE(station.Exists(333));
}

TEST(ChargingStation, Front) {
  ChargingStation station;
  EXPECT_EQ(station.Front(), std::nullopt);
  station.Enqueue(111);
  EXPECT_EQ(station.Front(), 111);
  station.Enqueue(222);
  EXPECT_EQ(station.Front(), 111);
  station.Dequeue();
  EXPECT_EQ(station.Front(), 222);
  station.Dequeue();
  EXPECT_EQ(station.Front(), std::nullopt);
}

TEST(ChargingStation, Enqueue) {
  ChargingStation station;
  EXPECT_TRUE(station.Enqueue(111));
  EXPECT_FALSE(station.Enqueue(111));
  EXPECT_TRUE(station.Enqueue(222));
  EXPECT_FALSE(station.Enqueue(222));
}

TEST(ChargingStation, Dequeue) {
  ChargingStation station;
  EXPECT_FALSE(station.Dequeue());
  station.Enqueue(111);
  station.Enqueue(222);
  EXPECT_TRUE(station.Dequeue());
  EXPECT_TRUE(station.Dequeue());
  EXPECT_FALSE(station.Dequeue());
}

}  // namespace

}  // namespace Demo
