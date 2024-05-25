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

#include "../source/Statistics.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(Statistics, DefaultConstructor) {
  constexpr Statistics statistics;
  EXPECT_EQ(statistics.TotalFlightCount(), 0);
  EXPECT_EQ(statistics.TotalFlightDuration(), PhQ::Time<>::Zero());
  EXPECT_EQ(statistics.TotalFlightDistance(), PhQ::Length<>::Zero());
  EXPECT_EQ(statistics.TotalFlightPassengerDistance(), PhQ::Length<>::Zero());
  EXPECT_EQ(statistics.MeanFlightDuration(), PhQ::Time<>::Zero());
  EXPECT_EQ(statistics.MeanFlightDistance(), PhQ::Length<>::Zero());
  EXPECT_EQ(statistics.TotalChargingSessionCount(), 0);
  EXPECT_EQ(statistics.TotalChargingDuration(), PhQ::Time<>::Zero());
  EXPECT_EQ(statistics.MeanChargingDuration(), PhQ::Time<>::Zero());
  EXPECT_EQ(statistics.TotalFaultCount(), 0);
}

TEST(Statistics, Operators) {
  constexpr Statistics statistics1;
  constexpr Statistics statistics2;
  EXPECT_EQ(statistics1, statistics2);
  EXPECT_FALSE(statistics1 != statistics2);
}

TEST(Statistics, IncrementTotalFlightCount) {
  Statistics statistics;

  statistics.IncrementTotalFlightCount();
  EXPECT_EQ(statistics.TotalFlightCount(), 1);

  statistics.IncrementTotalFlightCount();
  EXPECT_EQ(statistics.TotalFlightCount(), 2);
}

TEST(Statistics, ModifyTotalFlightDurationAndDistance) {
  Statistics statistics;

  statistics.IncrementTotalFlightCount();

  statistics.ModifyTotalFlightDurationAndDistance(
      /*passenger_count=*/2, PhQ::Time(1.0, PhQ::Unit::Time::Minute),
      PhQ::Length(1.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(statistics.TotalFlightCount(), 1);

  EXPECT_EQ(statistics.TotalFlightDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.TotalFlightDistance(), PhQ::Length(1.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(
      statistics.TotalFlightPassengerDistance(), PhQ::Length(2.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(statistics.MeanFlightDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.MeanFlightDistance(), PhQ::Length(1.0, PhQ::Unit::Length::Kilometre));

  statistics.IncrementTotalFlightCount();

  statistics.ModifyTotalFlightDurationAndDistance(
      /*passenger_count=*/2, PhQ::Time(1.0, PhQ::Unit::Time::Minute),
      PhQ::Length(1.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(statistics.TotalFlightCount(), 2);

  EXPECT_EQ(statistics.TotalFlightDuration(), PhQ::Time(2.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.TotalFlightDistance(), PhQ::Length(2.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(
      statistics.TotalFlightPassengerDistance(), PhQ::Length(4.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(statistics.MeanFlightDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.MeanFlightDistance(), PhQ::Length(1.0, PhQ::Unit::Length::Kilometre));
}

TEST(Statistics, IncrementTotalChargingSessionCount) {
  Statistics statistics;

  statistics.IncrementTotalChargingSessionCount();
  EXPECT_EQ(statistics.TotalChargingSessionCount(), 1);

  statistics.IncrementTotalChargingSessionCount();
  EXPECT_EQ(statistics.TotalChargingSessionCount(), 2);
}

TEST(Statistics, ModifyTotalChargingSessionDuration) {
  Statistics statistics;

  statistics.IncrementTotalChargingSessionCount();

  statistics.ModifyTotalChargingSessionDuration(PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.TotalChargingSessionCount(), 1);

  EXPECT_EQ(statistics.TotalChargingDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.MeanChargingDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  statistics.IncrementTotalChargingSessionCount();

  statistics.ModifyTotalChargingSessionDuration(PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.TotalChargingSessionCount(), 2);

  EXPECT_EQ(statistics.TotalChargingDuration(), PhQ::Time(2.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(statistics.MeanChargingDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));
}

TEST(Statistics, ModifyTotalFaultCount) {
  Statistics statistics;

  statistics.ModifyTotalFaultCount(2);
  EXPECT_EQ(statistics.TotalFaultCount(), 2);

  statistics.ModifyTotalFaultCount(4);
  EXPECT_EQ(statistics.TotalFaultCount(), 6);
}

TEST(Statistics, Aggregate) {
  Statistics statistics1;
  statistics1.IncrementTotalFlightCount();
  statistics1.IncrementTotalFlightCount();
  statistics1.ModifyTotalFlightDurationAndDistance(
      /*passenger_count=*/2, PhQ::Time(2.0, PhQ::Unit::Time::Minute),
      PhQ::Length(2.0, PhQ::Unit::Length::Kilometre));
  statistics1.IncrementTotalChargingSessionCount();
  statistics1.ModifyTotalChargingSessionDuration(PhQ::Time(1.0, PhQ::Unit::Time::Minute));
  statistics1.ModifyTotalFaultCount(4);

  Statistics statistics2;
  statistics1.IncrementTotalFlightCount();
  statistics1.IncrementTotalFlightCount();
  statistics1.IncrementTotalFlightCount();
  statistics1.IncrementTotalFlightCount();
  statistics1.IncrementTotalFlightCount();
  statistics1.IncrementTotalFlightCount();
  statistics1.ModifyTotalFlightDurationAndDistance(
      /*passenger_count=*/2, PhQ::Time(6.0, PhQ::Unit::Time::Minute),
      PhQ::Length(6.0, PhQ::Unit::Length::Kilometre));
  statistics1.IncrementTotalChargingSessionCount();
  statistics1.IncrementTotalChargingSessionCount();
  statistics1.IncrementTotalChargingSessionCount();
  statistics1.ModifyTotalChargingSessionDuration(PhQ::Time(3.0, PhQ::Unit::Time::Minute));
  statistics1.ModifyTotalFaultCount(12);

  Statistics aggregate;

  aggregate.Aggregate(statistics1);
  EXPECT_EQ(aggregate, statistics1);

  aggregate.Aggregate(statistics2);

  EXPECT_EQ(aggregate.TotalFlightCount(), 8);

  EXPECT_EQ(aggregate.TotalFlightDuration(), PhQ::Time(8.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(aggregate.TotalFlightDistance(), PhQ::Length(8.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(
      aggregate.TotalFlightPassengerDistance(), PhQ::Length(16.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(aggregate.MeanFlightDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(aggregate.MeanFlightDistance(), PhQ::Length(1.0, PhQ::Unit::Length::Kilometre));

  EXPECT_EQ(aggregate.TotalChargingSessionCount(), 4);

  EXPECT_EQ(aggregate.TotalChargingDuration(), PhQ::Time(4.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(aggregate.MeanChargingDuration(), PhQ::Time(1.0, PhQ::Unit::Time::Minute));

  EXPECT_EQ(aggregate.TotalFaultCount(), 16);
}

}  // namespace

}  // namespace Demo
