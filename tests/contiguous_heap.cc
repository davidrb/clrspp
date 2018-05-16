#include "../algo/contiguous_heap.hpp"

#include "catch.hpp"

#include <string>

using namespace std::string_literals;

TEST_CASE("Min Heap", "[heap]") {
  auto my_heap = algo::contiguous_heap<algo::min<int>>{}
                  .fill(5, 3, 7, 1, 2, 0, 9, 8, 4, 6);

  REQUIRE(my_heap.extract() == 0);
  REQUIRE(my_heap.extract() == 1);
  REQUIRE(my_heap.extract() == 2);
  REQUIRE(my_heap.extract() == 3);
  REQUIRE(my_heap.extract() == 4);
  REQUIRE(my_heap.extract() == 5);
  REQUIRE(my_heap.extract() == 6);
  REQUIRE(my_heap.extract() == 7);
  REQUIRE(my_heap.extract() == 8);
  REQUIRE(my_heap.extract() == 9);
}

TEST_CASE("Max Heap With Key", "[heap]") {
  auto my_heap = algo::contiguous_heap<algo::max<int, std::string>>{
    [](std::string s){ return s.length(); }
  };

  my_heap.fill("longer", "long", "longest");

  REQUIRE(my_heap.extract() == "longest");
  REQUIRE(my_heap.extract() == "longer");
  REQUIRE(my_heap.extract() == "long");
  REQUIRE(my_heap.empty());
}
