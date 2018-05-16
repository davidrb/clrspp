#ifndef ALGO_CONTIGUOUS_HEAP_HPP
#define ALGO_CONTIGUOUS_HEAP_HPP

#include "../algo/heap.hpp"

#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>

namespace algo {
  template<typename heap_type>
  class contiguous_heap {
  public:
    using value_type = typename heap_type::value_type;
    using key_type = typename heap_type::key_type;

    contiguous_heap() :
      key_{default_key_func<key_type, value_type>::value()} {
    };

    template<typename... args>
    contiguous_heap(std::function<key_type(value_type)> key, args... a) :
      key_{key}, buffer_{a...} {
      fill(a...);
    }

    template<typename... args_t>
    auto& fill(args_t... args) {
      buffer_ = decltype(buffer_){args...};
      build();
      return *this;
    }

    auto& build() {
      algo::build(buffer_.begin(), buffer_.end(), &heap_type::comp, key_);
      return *this;
    }

    auto empty() const {
      return buffer_.empty();
    }

    auto extract() {
      auto x = buffer_.front();
      buffer_.front() = buffer_.back();
      heapify(std::begin(buffer_), std::begin(buffer_), std::end(buffer_),
              &heap_type::comp, key_);
      buffer_.pop_back();
      return x;
    }

  private:
    std::function<key_type(value_type)> key_;
    std::vector<value_type> buffer_;
  };
}

#endif
