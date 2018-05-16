#ifndef ALGO_HEAP_HPP
#define ALGO_HEAP_HPP

#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>

namespace algo {
  template<typename iterator>
  static auto left(iterator begin, iterator it, iterator end) {
    auto i = std::distance(begin, it);
    std::advance(begin, 2*i + 1);
    return begin;
  }

  template<typename iterator>
  static auto right(iterator begin, iterator it, iterator end) {
    auto i = std::distance(begin, it);
    std::advance(begin, 2*i + 2);
    return begin;
  }

  template<typename iterator, typename comp_t, typename key_t>
  static void heapify(iterator begin, iterator it, iterator end, comp_t comp, key_t key) {
    auto l = left(begin, it, end);
    auto r = right(begin, it, end);

    auto largest = (l < end && comp(key(*it), key(*l))) ? l : it;
    if (r < end && comp(key(*largest), key(*r)))
      largest = r;

    if (largest != it) {
      std::swap(*it, *largest);
      heapify(begin, largest, end, comp, key);
    }
  }

  template<typename iterator, typename comp_t, typename key_t>
  static void build(iterator begin, iterator end, comp_t comp, key_t key) {
    if (begin == end) return;
    auto it = begin + std::distance(begin, end)/2;
    while (true) {
      heapify(begin, it, end, comp, key);
      if (it-- == begin) return;
    }
  }

  template <typename key_type_, typename value_type_ = key_type_>
  struct max {
    using key_type = key_type_;
    using value_type = value_type_;

    static auto comp(key_type l, key_type r) {
      return l < r;
    }
  };

  template <typename key_type_, typename value_type_ = key_type_>
  struct min {
    using key_type = key_type_;
    using value_type = value_type_;

    static auto comp(key_type l, key_type r) {
      return l > r;
    }
  };

  template<typename key_type, typename value_type>
  struct default_key_func {
    static auto value() -> std::function<key_type(value_type)> {
      throw std::runtime_error{"no default key function."};
    }
  };

  template<typename value_type>
  struct default_key_func<value_type, value_type> {
    static auto value() -> std::function<value_type(value_type)> {
      return [](value_type v){ return v; };
    }
  };
};

#endif
