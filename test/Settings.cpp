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

#include "../source/Settings.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(Settings, DefaultConstructor) {
  const Settings settings;
  EXPECT_EQ(settings.Duration(), PhQ::Time::Zero());
  EXPECT_EQ(settings.VehicleCount(), 0);
  EXPECT_EQ(settings.ChargingStationCount(), 0);
  EXPECT_EQ(settings.RandomSeed(), std::nullopt);
}

TEST(Settings, MainConstructor) {
  const Settings settings{
      /*duration=*/PhQ::Time(3.0, PhQ::Unit::Time::Hour),
      /*vehicle_count=*/20,
      /*charging_station_count=*/3,
      /*random_seed=*/42,
  };
  EXPECT_EQ(settings.Duration(), PhQ::Time(3.0, PhQ::Unit::Time::Hour));
  EXPECT_EQ(settings.VehicleCount(), 20);
  EXPECT_EQ(settings.ChargingStationCount(), 3);
  EXPECT_EQ(settings.RandomSeed(), 42);
}

TEST(Settings, NegativeValues) {
  const Settings settings{
      /*duration=*/PhQ::Time(-3.0, PhQ::Unit::Time::Hour),
      /*vehicle_count=*/-20,
      /*charging_station_count=*/-3,
  };
  EXPECT_EQ(settings.Duration(), PhQ::Time::Zero());
  EXPECT_EQ(settings.VehicleCount(), 0);
  EXPECT_EQ(settings.ChargingStationCount(), 0);
}

}  // namespace

}  // namespace Demo
