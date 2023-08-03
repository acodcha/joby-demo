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

#ifndef DEMO_INCLUDE_FILE_HPP
#define DEMO_INCLUDE_FILE_HPP

#include <filesystem>
#include <fstream>
#include <iostream>

namespace Demo {

// General-purpose file handler.
template<class FileStream> class File {
public:
  // Destructor. Closes the file if needed.
  ~File() noexcept {
    if (stream_.is_open()) {
      stream_.close();
    }
  }

  // Path to this file.
  const std::filesystem::path& Path() const noexcept { return path_; }

protected:
  std::filesystem::path path_;

  FileStream stream_;

  // Creates and opens a file at the given path.
  File(const std::filesystem::path& path) : path_(path) {
    if (!path_.empty()) {
      stream_.open(path_.string());
      if (!stream_.is_open()) {
        std::cerr << "Could not open the file: " << path_.string() << std::endl;
      }
    }
  }
};

}  // namespace Demo

#endif  // DEMO_INCLUDE_FILE_HPP
