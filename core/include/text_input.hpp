#pragma once

#include <input.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace coreutils {

class TextInput final : public Input {
 public:
  explicit TextInput(std::string str) : str_(std::move(str)) {}
  std::vector<char> read(size_t size) override {
    if (offset_ == str_.size()) {
      return {};
    }

    size = std::min(size, str_.size() - offset_);
    std::vector<char> res{&str_[offset_], &str_[offset_ + size]};
    offset_ += size;
    return res;
  }

 private:
  std::string str_;
  size_t offset_{};
};

}  // namespace coreutils
