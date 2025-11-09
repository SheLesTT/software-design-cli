#pragma once

#include <output.hpp>

#include <iostream>
#include <vector>

namespace coreutils {

class StdOutput : public Output {
 public:
  void write(std::vector<char> data) override {
    std::cout.write(data.data(), static_cast<std::streamsize>(data.size()));
  }
};

}  // namespace coreutils
