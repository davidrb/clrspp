#ifndef ALGO_GRAPH_HPP
#define ALGO_GRAPH_HPP

#include <map>
#include <functional>

namespace algo {
  template<typename G>
  void relax(G const& g, auto v, auto w, auto& dist, auto& parent) {
    auto d = dist[v] + weight(g, {v, w});
    if (d < dist[w]) {
      dist[w] = d;
      parent[w] = v;
    }
  }

  template<typename G>
  auto init_single_source(G const& g, auto start) {
    auto dist = std::map<decltype(start), typename G::weight_t>{};
    auto parent = std::map<decltype(start), decltype(start)>{};

    for (auto v : g) {
      dist[v] = G::inf;
      parent[v] = G::nil;
    }
    dist[start] = {0};

    return std::make_pair(dist, parent);
  }
}

#endif
