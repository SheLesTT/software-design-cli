#pragma once

#include <vector>

namespace coreutils {

constexpr size_t DEFAULT_BLOCK_SIZE = 4096;

class Input {
 public:
  Input() = default;
  virtual ~Input() = default;
  Input(const Input&) noexcept = delete;
  Input(Input&&) noexcept = default;
  Input& operator=(const Input&) noexcept = delete;
  Input& operator=(Input&&) noexcept = default;

  virtual std::vector<char> read(size_t size) = 0;
};

}  // namespace coreutils
