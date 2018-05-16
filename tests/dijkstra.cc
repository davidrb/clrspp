#include "../algo/dijkstra.hpp"

#include "catch.hpp"

#include <map>
#include <vector>
#include <functional>

#include <boost/range.hpp>

using std::map;
using std::pair;
using std::vector;

// Test Graph Type
struct my_graph_t {
  using vertex_t = int;
  using edge_t = pair<int, int>;
  using iterator_t = std::vector<int>::iterator;
  using weight_t = double;
  using vertex_range_t = boost::iterator_range<iterator_t>;

  static auto constexpr nil = -1;
  static auto constexpr inf = std::numeric_limits<double>::infinity();

  my_graph_t(vector<int>&& vs,
             map<int, vector<int>>&& adj,
             map<pair<int, int>, double>&& ws) :
    vertices_{std::move(vs)},
    adjacency_{std::move(adj)},
    weights_{std::move(ws)} {
  }

  auto begin() const { return vertices_.begin(); }
  auto end() const { return vertices_.end(); }

  friend auto neighbors(my_graph_t const& g, int v) {
    auto const& l = g.adjacency_.at(v);
    return boost::make_iterator_range(l.begin(), l.end());
  }

  friend auto weight(my_graph_t const& g, pair<int, int> e) {
    return g.weights_.at(e);
  }

private:
  vector<int> vertices_;
  map<int, vector<int>> adjacency_;
  map<pair<int, int>, double> weights_;
};

TEST_CASE("Dijkstra's Algorithm finds all shortest paths", "[dijkstra]") {
  auto g = my_graph_t{
    { 1, 2, 3, 4, 5 },
    { {1, {2, 3}},
      {2, {3, 4}},
      {3, {5}},
      {4, {}},
      {5, {4}}},
    { {{1, 2}, 2.0},
      {{1, 3}, 4.0},
      {{2, 3}, 1.0},
      {{2, 4}, 4.0},
      {{3, 5}, 1.0},
      {{5, 4}, 1.0} }
  };

  auto result = algo::dijkstra(g, 1, 3);

  REQUIRE( result.first[1] == 0.0 );
  REQUIRE( result.first[2] == 2.0 );
  REQUIRE( result.first[3] == 2.0+1.0 );
  REQUIRE( result.first[4] == 2.0+1.0+1.0+1.0 );
  REQUIRE( result.first[5] == 2.0+1.0+1.0 );

  REQUIRE( result.second[1] == my_graph_t::nil );
  REQUIRE( result.second[2] == 1 );
  REQUIRE( result.second[3] == 2 );
  REQUIRE( result.second[4] == 5 );
  REQUIRE( result.second[5] == 3 );
}
