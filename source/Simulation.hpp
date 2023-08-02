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

#ifndef DEMO_INCLUDE_SIMULATION_HPP
#define DEMO_INCLUDE_SIMULATION_HPP

#include <map>
#include <random>

#include "ChargingStations.hpp"
#include "Statistics.hpp"
#include "Vehicles.hpp"

namespace Demo {

// A vehicle fleet simulation.
class Simulation {
public:
  // Constructs and runs a simulation.
  Simulation(const PhQ::Time& duration, Vehicles& vehicles,
             ChargingStations& charging_stations,
             std::mt19937_64& random_generator) noexcept {
    while (elapsed_time_ < duration) {
      const PhQ::Time time_step = ComputeTimeStep(duration, vehicles);
      if (time_step <= PhQ::Time::Zero()) {
        break;
      }
      RunTimeStep(time_step, vehicles, charging_stations, random_generator);
      elapsed_time_ += time_step;
    }
  }

private:
  // Runs a time step of this simulation.
  // TODO: Consider using multithreading to operate on all vehicles in parallel,
  // and make sure the relevant operations are performed atomically when
  // appropriate.
  void RunTimeStep(const PhQ::Time& time_step, Vehicles& vehicles,
                   ChargingStations& charging_stations,
                   std::mt19937_64& random_generator) noexcept {
    // Update all vehicles at the beginning of the time step.
    UpdateAllVehicles(vehicles, charging_stations);

    // Perform the time step on each vehicle.
    for (const std::shared_ptr<Vehicle>& vehicle : vehicles) {
      if (vehicle != nullptr) {
        vehicle->PerformTimeStep(
            time_step, charging_stations, random_generator);
      }
    }

    // Update all vehicles at the end of the time step.
    UpdateAllVehicles(vehicles, charging_stations);
  }

  // Updates all vehicles either at the beginning or at the end of a time step.
  void UpdateAllVehicles(
      Vehicles& vehicles, ChargingStations& charging_stations) noexcept {
    for (const std::shared_ptr<Vehicle>& vehicle : vehicles) {
      if (vehicle != nullptr) {
        vehicle->Update(charging_stations);
      }
    }
  }

  // Computes the largest possible time step given the states of the vehicles.
  PhQ::Time ComputeTimeStep(
      const PhQ::Time& duration, const Vehicles& vehicles) const noexcept {
    PhQ::Time time_step = duration;
    for (const std::shared_ptr<Vehicle>& vehicle : vehicles) {
      if (vehicle != nullptr) {
        const PhQ::Time vehicle_time_step =
            vehicle->DurationToNextStatusChange();
        if (vehicle_time_step < time_step) {
          time_step = vehicle_time_step;
        }
      }
    }
    return time_step;
  }

  // Elapsed time in the simulation.
  PhQ::Time elapsed_time_ = PhQ::Time::Zero();
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_SIMULATION_HPP
