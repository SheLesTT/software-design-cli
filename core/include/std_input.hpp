#pragma once

#include <input.hpp>

#include <cstddef>
#include <iostream>
#include <vector>

namespace coreutils {

class StdInput final : public Input {
 public:
  std::vector<char> read(size_t size) override {
    if (size == 0 || !std::cin.good()) {
      return {};
    }
    std::vector<char> res(size);
    std::cin.read(res.data(), static_cast<std::streamsize>(size));
    auto count = std::cin.gcount();
    res.resize(count);
    return res;
  }
};

}  // namespace coreutils
