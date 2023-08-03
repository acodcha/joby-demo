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

#ifndef DEMO_INCLUDE_RESULTS_FILE_WRITER_HPP
#define DEMO_INCLUDE_RESULTS_FILE_WRITER_HPP

#include "AggregateStatistics.hpp"
#include "String.hpp"
#include "TextFileWriter.hpp"
#include "VehicleModels.hpp"

namespace Demo {

// File writer for writing results to a text file.
class ResultsFileWriter : public TextFileWriter {
public:
  // Creates and opens a file at the given path, writes the given aggregate
  // statistics to it, and closes the file.
  ResultsFileWriter(
      const std::filesystem::path& path, const VehicleModels& vehicle_models,
      const AggregateStatistics& aggregate_statistics)
    : TextFileWriter(path) {
    ComputePaddingLengths(vehicle_models, aggregate_statistics);

    // Print the header line.
    Line(PadToLength(manufacturer_, manufacturer_padding_) + space_
         + PadToLength(model_, model_padding_) + space_
         + PadToLength(mean_flight_duration_, mean_flight_duration_padding_)
         + space_
         + PadToLength(mean_flight_distance_, mean_flight_distance_padding_)
         + space_
         + PadToLength(mean_charging_duration_, mean_charging_duration_padding_)
         + space_
         + PadToLength(total_flight_passenger_distance_,
                       total_flight_passenger_distance_padding_)
         + space_ + PadToLength(total_faults_, total_faults_padding_));

    // Print one line for each vehicle model.
    for (const std::pair<const VehicleModelId, Statistics>&
             vehicle_model_id_and_statistics : aggregate_statistics) {
      const VehicleModelId& vehicle_model_id =
          vehicle_model_id_and_statistics.first;

      const Statistics& statistics = vehicle_model_id_and_statistics.second;

      const std::shared_ptr<const VehicleModel> vehicle_model =
          vehicle_models.At(vehicle_model_id);

      if (vehicle_model == nullptr) {
        continue;
      }

      Line(
          PadToLength(
              PrintManufacturerName(*vehicle_model), manufacturer_padding_)
          + space_ + PadToLength(PrintModelName(*vehicle_model), model_padding_)
          + space_
          + PadToLength(PrintMeanFlightDuration(statistics),
                        mean_flight_duration_padding_)
          + space_
          + PadToLength(PrintMeanFlightDistance(statistics),
                        mean_flight_distance_padding_)
          + space_
          + PadToLength(PrintMeanChargingDuration(statistics),
                        mean_charging_duration_padding_)
          + space_
          + PadToLength(PrintTotalFlightPassengerDistance(statistics),
                        total_flight_passenger_distance_padding_)
          + space_
          + PadToLength(
              PrintTotalFaultCount(statistics), total_faults_padding_));
    }
  }

private:
  void ComputePaddingLengths(
      const VehicleModels& vehicle_models,
      const AggregateStatistics& aggregate_statistics) noexcept {
    for (const std::pair<const VehicleModelId, Statistics>&
             vehicle_model_id_and_statistics : aggregate_statistics) {
      const VehicleModelId& vehicle_model_id =
          vehicle_model_id_and_statistics.first;

      const Statistics& statistics = vehicle_model_id_and_statistics.second;

      const std::shared_ptr<const VehicleModel> vehicle_model =
          vehicle_models.At(vehicle_model_id);

      if (vehicle_model == nullptr) {
        continue;
      }

      const std::size_t current_manufacturer_padding =
          PrintManufacturerName(*vehicle_model).size();
      if (current_manufacturer_padding > manufacturer_padding_) {
        manufacturer_padding_ = current_manufacturer_padding;
      }

      const std::size_t current_model_padding =
          PrintModelName(*vehicle_model).size();
      if (current_model_padding > model_padding_) {
        model_padding_ = current_model_padding;
      }

      const std::size_t current_mean_flight_duration_padding =
          PrintMeanFlightDuration(statistics).size();
      if (current_mean_flight_duration_padding
          > mean_flight_duration_padding_) {
        mean_flight_duration_padding_ = current_mean_flight_duration_padding;
      }

      const std::size_t current_mean_flight_distance_padding =
          PrintMeanFlightDistance(statistics).size();
      if (current_mean_flight_distance_padding
          > mean_flight_distance_padding_) {
        mean_flight_distance_padding_ = current_mean_flight_distance_padding;
      }

      const std::size_t current_mean_charging_duration_padding =
          PrintMeanChargingDuration(statistics).size();
      if (current_mean_charging_duration_padding
          > mean_charging_duration_padding_) {
        mean_charging_duration_padding_ =
            current_mean_charging_duration_padding;
      }

      const std::size_t current_total_flight_passenger_distance_padding =
          PrintTotalFlightPassengerDistance(statistics).size();
      if (current_total_flight_passenger_distance_padding
          > total_flight_passenger_distance_padding_) {
        total_flight_passenger_distance_padding_ =
            current_total_flight_passenger_distance_padding;
      }

      const std::size_t current_total_faults_padding =
          PrintTotalFaultCount(statistics).size();
      if (current_total_faults_padding > total_faults_padding_) {
        total_faults_padding_ = current_total_faults_padding;
      }
    }
  }

  std::string PrintManufacturerName(
      const VehicleModel& vehicle_model) const noexcept {
    return ReplaceSpacesWithUnderscores(
        vehicle_model.ManufacturerNameEnglish());
  }

  std::string PrintModelName(const VehicleModel& vehicle_model) const noexcept {
    return ReplaceSpacesWithUnderscores(vehicle_model.ModelNameEnglish());
  }

  std::string PrintMeanFlightDuration(
      const Statistics& statistics) const noexcept {
    return statistics.MeanFlightDuration().Print(PhQ::Unit::Time::Hour);
  }

  std::string PrintMeanFlightDistance(
      const Statistics& statistics) const noexcept {
    return statistics.MeanFlightDistance().Print(PhQ::Unit::Length::Mile);
  }

  std::string PrintMeanChargingDuration(
      const Statistics& statistics) const noexcept {
    return statistics.MeanChargingDuration().Print(PhQ::Unit::Time::Hour);
  }

  std::string PrintTotalFlightPassengerDistance(
      const Statistics& statistics) const noexcept {
    return statistics.TotalFlightPassengerDistance().Print(
        PhQ::Unit::Length::Mile);
  }

  std::string PrintTotalFaultCount(
      const Statistics& statistics) const noexcept {
    return std::to_string(statistics.TotalFaultCount());
  }

  const std::string space_{"  "};

  std::string manufacturer_{"#Manufacturer"};

  std::size_t manufacturer_padding_ = manufacturer_.size();

  std::string model_{"Model"};

  std::size_t model_padding_ = model_.size();

  std::string mean_flight_duration_{"MeanFlightDuration"};

  std::size_t mean_flight_duration_padding_ = mean_flight_duration_.size();

  std::string mean_flight_distance_{"MeanFlightDistance"};

  std::size_t mean_flight_distance_padding_ = mean_flight_distance_.size();

  std::string mean_charging_duration_{"MeanChargingDuration"};

  std::size_t mean_charging_duration_padding_ = mean_charging_duration_.size();

  std::string total_flight_passenger_distance_{"TotalFlightPassengerDistance"};

  std::size_t total_flight_passenger_distance_padding_ =
      total_flight_passenger_distance_.size();

  std::string total_faults_{"TotalFaults"};

  std::size_t total_faults_padding_ = total_faults_.size();
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_RESULTS_FILE_WRITER_HPP
