#ifndef ALGO_DIJKSTRA_HPP
#define ALGO_DIJKSTRA_HPP

#include "graph.hpp"
#include "contiguous_heap.hpp"

#include <vector>

namespace algo {
  template<typename graph_t, typename vertex_t, typename weight_t = typename graph_t::weight_t>
  auto dijkstra(graph_t const& g, vertex_t start, vertex_t target) {
    auto [dist, parent] = algo::init_single_source(g, start);

    auto unvisited = algo::contiguous_heap<algo::min<weight_t, vertex_t>>{
      [&](vertex_t v){ return dist[v]; }}
      .fill(std::begin(g), std::end(g));

    while (!unvisited.empty()) {
      unvisited.build();
      auto v = unvisited.extract();

      for (auto n : neighbors(g, v))
        algo::relax(g, v, n, dist, parent);
    }

    return std::make_pair(dist, parent);
  }
};

#endif
