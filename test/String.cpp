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

#include "../source/String.hpp"

#include <gtest/gtest.h>

namespace Demo {

namespace {

TEST(String, PadToLength) {
  EXPECT_EQ(PadToLength("", 0), "");
  EXPECT_EQ(PadToLength("", 10), "          ");
  EXPECT_EQ(PadToLength("Hello world!", 0), "Hello world!");
  EXPECT_EQ(PadToLength("Hello world!", 15), "Hello world!   ");
}

TEST(String, ReplaceCharacter) {
  EXPECT_EQ(ReplaceCharacter("", 'a', 'b'), "");
  EXPECT_EQ(ReplaceCharacter("Hello world!", 'l', 'L'), "HeLLo worLd!");
}

TEST(String, ReplaceSpacesWithUnderscores) {
  EXPECT_EQ(ReplaceSpacesWithUnderscores(""), "");
  EXPECT_EQ(ReplaceSpacesWithUnderscores("Hello world!"), "Hello_world!");
  EXPECT_EQ(ReplaceSpacesWithUnderscores("H e l l o   w o r l d !"), "H_e_l_l_o___w_o_r_l_d_!");
}

}  // namespace

}  // namespace Demo
