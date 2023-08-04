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

#include "../source/ResultsFileWriter.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(ResultsFileWriter, Empty) {
  ResultsFileWriter results_file_writer{{}, {}, {}};

  EXPECT_EQ(results_file_writer.Path(), std::filesystem::path());

  EXPECT_EQ(results_file_writer.Permissions(),
            std::filesystem::perms{std::filesystem::perms::owner_read
                                   | std::filesystem::perms::owner_write
                                   | std::filesystem::perms::group_read
                                   | std::filesystem::perms::others_read});

  std::ifstream file;
  file.open("");
  EXPECT_FALSE(file.is_open());
}

TEST(ResultsFileWriter, Simple) {
  const std::filesystem::path path{"results.dat"};

  VehicleModels vehicle_models;

  vehicle_models.Insert(std::make_shared<const VehicleModel>(
      /*id=*/111,
      /*manufacturer_name_english=*/"Manufacturer A",
      /*model_name_english=*/"Model A",
      /*passenger_count=*/2,
      /*cruise_speed=*/PhQ::Speed(1.0, PhQ::Unit::Speed::MetrePerSecond),
      /*battery_capacity=*/PhQ::Energy(2.0, PhQ::Unit::Energy::Joule),
      /*charging_duration=*/PhQ::Time(1.0, PhQ::Unit::Time::Second),
      /*fault_rate=*/PhQ::Frequency(1.0, PhQ::Unit::Frequency::Hertz),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(1.0, PhQ::Unit::Force::Newton)));

  vehicle_models.Insert(std::make_shared<const VehicleModel>(
      /*id=*/222,
      /*manufacturer_name_english=*/"Manufacturer B",
      /*model_name_english=*/"Model B",
      /*passenger_count=*/2,
      /*cruise_speed=*/PhQ::Speed(1.0, PhQ::Unit::Speed::MetrePerSecond),
      /*battery_capacity=*/PhQ::Energy(2.0, PhQ::Unit::Energy::Joule),
      /*charging_duration=*/PhQ::Time(1.0, PhQ::Unit::Time::Second),
      /*fault_rate=*/PhQ::Frequency(1.0, PhQ::Unit::Frequency::Hertz),
      /*transport_energy_consumption=*/
      PhQ::TransportEnergyConsumption(1.0, PhQ::Unit::Force::Newton)));

  Vehicles vehicles;
  vehicles.Insert(std::make_shared<Vehicle>(333, vehicle_models.At(111)));
  vehicles.Insert(std::make_shared<Vehicle>(444, vehicle_models.At(222)));

  const AggregateStatistics aggregate_statistics{vehicles};

  ResultsFileWriter results_file_writer{
      path, vehicle_models, aggregate_statistics};

  EXPECT_EQ(results_file_writer.Path(), path);
  EXPECT_EQ(results_file_writer.Permissions(),
            std::filesystem::perms{std::filesystem::perms::owner_read
                                   | std::filesystem::perms::owner_write
                                   | std::filesystem::perms::group_read
                                   | std::filesystem::perms::others_read});

  std::ifstream file;
  file.open(path);
  ASSERT_TRUE(file.is_open());

  std::vector<std::string> lines;
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      lines.push_back(line);
    }
  }

  ASSERT_EQ(lines.size(), 3);
  EXPECT_EQ(lines[0],
            "#Manufacturer   Model    MeanFlightDuration  MeanFlightDistance  "
            "MeanChargingDuration  TotalFlightPassengerDistance  TotalFaults");
  EXPECT_EQ(lines[1],
            "Manufacturer_A  Model_A  0 hr                0 mi                "
            "0 hr                  0 mi                          0          ");
  EXPECT_EQ(lines[2],
            "Manufacturer_B  Model_B  0 hr                0 mi                "
            "0 hr                  0 mi                          0          ");

  ASSERT_TRUE(file.is_open());
  file.close();
}

}  // namespace

}  // namespace Demo
