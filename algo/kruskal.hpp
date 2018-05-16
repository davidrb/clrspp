#ifndef ALGO_KRUSKAL_HPP
#define ALGO_KRUSKAL_HPP

#include "../algo/disjoint_set.hpp"
#include "../algo/contiguous_heap.hpp"

#include <algorithm>
#include <vector>

namespace algo {
  template<typename tree_t>
  auto kruskal(tree_t const& t) {
    using weight_t = typename tree_t::weight_t;
    using edge_t = typename tree_t::edge_t;

    auto key = [&](auto e){ return weight(t, e); };
    auto heap = algo::contiguous_heap<algo::min<weight_t, edge_t>>{key};
    heap.fill(edges(t).begin(), edges(t).end());

    auto mst_edges = std::vector<typename tree_t::edge_t>{};
    auto sets = algo::disjoint_set<typename tree_t::vertex_t>{};

    for (auto v : vertices(t))
      sets.make(v);

    while (!heap.empty()) {
      auto e = heap.extract();

      if (sets.find(e.first) != sets.find(e.second)) {
        mst_edges.emplace_back(e);
        sets.union_set(e.first, e.second);
      }
    }
    return mst_edges;
  }
}

#endif
