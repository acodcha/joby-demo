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

#ifndef DEMO_INCLUDE_FILE_WRITER_HPP
#define DEMO_INCLUDE_FILE_WRITER_HPP

#include "File.hpp"

namespace Demo {

// General-purpose file writer.
class FileWriter : public File<std::ofstream> {
public:
  // Destructor. Sets the permissions for this file before closing it.
  ~FileWriter() noexcept {
    SetPermissions();
  }

  // Permissions of this file.
  const std::filesystem::perms& Permissions() const noexcept {
    return permissions_;
  }

protected:
  // Creates and opens a file for writing at the given path and with the given permissions.
  FileWriter(const std::filesystem::path& path,
             const std::filesystem::perms& permissions =
                 {std::filesystem::perms::owner_read | std::filesystem::perms::owner_write
                  | std::filesystem::perms::group_read | std::filesystem::perms::others_read})
    : File(path), permissions_(permissions) {}

  std::filesystem::perms permissions_;

  // Sets the permissions of this file.
  void SetPermissions() noexcept {
    if (!path_.empty() && std::filesystem::exists(path_)) {
      std::filesystem::permissions(path_, permissions_);
    }
  }
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_FILE_WRITER_HPP
