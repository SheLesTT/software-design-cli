#pragma once

#include <vector>

namespace coreutils {

class Output {
 public:
  Output() = default;
  virtual ~Output() = default;
  Output(const Output&) noexcept = delete;
  Output(Output&&) noexcept = default;
  Output& operator=(const Output&) noexcept = delete;
  Output& operator=(Output&&) noexcept = default;

  virtual void write(std::vector<char> data) = 0;
};

}  // namespace coreutils
