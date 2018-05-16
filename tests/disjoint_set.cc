#include "catch.hpp"

#include "../algo/disjoint_set.hpp"

TEST_CASE("make_set makes a new set", "[disjoint set]") {
  auto dset = algo::disjoint_set<int>{};

  dset.make(3);
  dset.make(4);

  REQUIRE(dset.find(3) == 3);
  REQUIRE(dset.find(4) == 4);
}

TEST_CASE("link", "[disjoint set]") {
  auto dset = algo::disjoint_set<int>{};
  dset.make(1);
  dset.make(2);
  dset.make(3);

  dset.link(1, 2);

  REQUIRE(dset.find(1) == dset.find(2));
  REQUIRE(dset.find(2) != dset.find(3));
}

TEST_CASE("union set", "[disjoint set]") {
  auto dset = algo::disjoint_set<int>{};
  dset.make(1);
  dset.make(2);
  dset.make(3);

  dset.union_set(dset.find(1), dset.find(2));
  REQUIRE(dset.find(1) == dset.find(2));
  REQUIRE(dset.find(2) != dset.find(3));

  dset.union_set(dset.find(2), dset.find(3));
  REQUIRE(dset.find(1) == dset.find(3));
}
