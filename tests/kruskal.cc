#include "catch.hpp"

#include "../algo/kruskal.hpp"

#include <string>
#include <map>
#include <numeric>

#include <boost/range.hpp>

struct tree_t {
  using vertex_t = std::string;
  using edge_t = std::pair<std::string, std::string>;
  using weight_t = unsigned;

  std::map<edge_t, weight_t> weights_;
  std::vector<edge_t> edges_;
  std::vector<vertex_t> vertices_;

  friend auto weight(tree_t const& t, edge_t e) -> weight_t {
    return t.weights_.at(e);
  }

  friend auto edges(tree_t const& t) -> boost::iterator_range<decltype(edges_)::const_iterator> {
    return boost::make_iterator_range(t.edges_.begin(), t.edges_.end());
  }

  friend auto vertices(tree_t const& t) {
    return boost::make_iterator_range(t.vertices_.begin(), t.vertices_.end());
  }
};

TEST_CASE("Kruskal's Algorithm finds minimum spanning tree", "[kruskal]") {
  auto t = tree_t{};
  t.vertices_ = {"a", "b", "c", "d", "e", "f", "g"};
  t.weights_ = std::map<tree_t::edge_t, unsigned>{
    {{"a", "b"}, 7},
    {{"a", "d"}, 5},
    {{"b", "c"}, 8},
    {{"b", "e"}, 7},
    {{"b", "d"}, 9},
    {{"c", "e"}, 5},
    {{"d", "e"}, 15},
    {{"d", "f"}, 6},
    {{"e", "f"}, 8},
    {{"e", "g"}, 9},
    {{"f", "g"}, 11}
  };

  for(auto kv : t.weights_) {
    t.edges_.emplace_back(kv.first);
  }

  auto mst_edges = algo::kruskal(t);

  REQUIRE(mst_edges.size() == 6);

  auto w = std::accumulate(mst_edges.begin(), mst_edges.end(), 0u,
      [&](auto x, auto r){ return x + weight(t, r); });
  REQUIRE(w == 39);
}
