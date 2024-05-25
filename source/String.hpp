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

#ifndef DEMO_INCLUDE_STRING_HPP
#define DEMO_INCLUDE_STRING_HPP

#include <algorithm>
#include <string>
#include <string_view>

namespace Demo {

// Returns a copy of a given string where the copy has been padded to a given length with trailing
// spaces. If the given string is already longer than the given length, nothing is changed.
std::string PadToLength(const std::string_view text, const std::size_t length) noexcept {
  std::string padded_text{text};
  const std::size_t text_length{text.size()};
  if (length > text_length) {
    padded_text.append(length - text_length, ' ');
  }
  return padded_text;
}

// Returns a copy of a given string where all occurences of a given character have been replaced
// with a different character.
std::string ReplaceCharacter(
    const std::string_view text, const char original, const char replacement) noexcept {
  std::string transformed_text{text};
  std::transform(transformed_text.begin(), transformed_text.end(), transformed_text.begin(),
                 [original, replacement](const char character) -> char {
                   if (character == original) {
                     return replacement;
                   } else {
                     return character;
                   }
                 });
  return transformed_text;
}

// Returns a copy of a given string where all spaces have been replaced by
// underscores.
std::string ReplaceSpacesWithUnderscores(const std::string_view text) noexcept {
  return ReplaceCharacter(text, ' ', '_');
}

}  // namespace Demo

#endif  // DEMO_INCLUDE_STRING_HPP
