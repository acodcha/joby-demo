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

TEST(Settings, Default) {
  const Settings settings;
  EXPECT_EQ(settings.Duration(), PhQ::Time::Zero());
  EXPECT_EQ(settings.Vehicles(), 0);
  EXPECT_EQ(settings.ChargingStations(), 0);
  EXPECT_EQ(settings.Seed(), std::nullopt);
}

TEST(Settings, Regular) {
  char program[] = "bin/joby-demo";

  char vehicles_key[] = "--vehicles";
  char vehicles_value[] = "20";

  char charging_stations_key[] = "--charging-stations";
  char charging_stations_value[] = "3";

  char duration_key[] = "--duration-hours";
  char duration_value[] = "3.0";

  char results_key[] = "--results";
  char results_value[] = "results.dat";

  char seed_key[] = "--seed";
  char seed_value[] = "42";

  int argc = 11;

  char* argv[] = {
      program,
      vehicles_key,
      vehicles_value,
      charging_stations_key,
      charging_stations_value,
      duration_key,
      duration_value,
      results_key,
      results_value,
      seed_key,
      seed_value,
  };

  const Settings settings{argc, argv};

  EXPECT_EQ(settings.Vehicles(), 20);
  EXPECT_EQ(settings.ChargingStations(), 3);
  EXPECT_EQ(settings.Duration(), PhQ::Time(3.0, PhQ::Unit::Time::Hour));
  EXPECT_EQ(settings.Results(), "results.dat");
  EXPECT_TRUE(settings.Seed().has_value());
  EXPECT_EQ(settings.Seed().value(), 42);
}

TEST(Settings, Bogus) {
  char program[] = "bin/joby-demo";

  char vehicles_key[] = "--vehicles";
  char vehicles_value[] = "-20";

  char charging_stations_key[] = "--charging-stations";
  char charging_stations_value[] = "-3";

  char duration_key[] = "--duration-hours";
  char duration_value[] = "-3.0";

  int argc = 7;

  char* argv[] = {
      program,
      vehicles_key,
      vehicles_value,
      charging_stations_key,
      charging_stations_value,
      duration_key,
      duration_value,
  };

  const Settings settings{argc, argv};

  EXPECT_EQ(settings.Duration(), PhQ::Time::Zero());
  EXPECT_EQ(settings.Vehicles(), 0);
  EXPECT_EQ(settings.ChargingStations(), 0);
}

}  // namespace

}  // namespace Demo
