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

#ifndef DEMO_INCLUDE_ARGUMENTS_HPP
#define DEMO_INCLUDE_ARGUMENTS_HPP

#include <string>

namespace Demo {

// Namespace listing this program's command-line argument keywords.
namespace Arguments {

static const std::string Help{"--help"};

static const std::string VehiclesKey{"--vehicles"};
static const std::string VehiclesPattern{VehiclesKey + " <number>"};

static const std::string ChargingStationsKey{"--charging-stations"};
static const std::string ChargingStationsPattern{ChargingStationsKey + " <number>"};

static const std::string DurationKey{"--duration-hours"};
static const std::string DurationPattern{DurationKey + " <number>"};

static const std::string ResultsKey{"--results"};
static const std::string ResultsPattern{ResultsKey + " <path>"};

static const std::string SeedKey{"--seed"};
static const std::string SeedPattern{SeedKey + " <number>"};

}  // namespace Arguments

}  // namespace Demo

#endif  // DEMO_INCLUDE_ARGUMENTS_HPP
