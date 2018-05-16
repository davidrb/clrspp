#ifndef ALGO_DISJOINT_SET_HPP
#define ALGO_DISJOINT_SET_HPP

#include<map>

namespace algo {
  template<typename value_type>
  class disjoint_set {
  public:
    void make(value_type x) {
      rank[x] = 0;
      parent[x] = x;
    }

    auto find(value_type x) {
      if (x == parent.at(x)) {
        return x;
      }
      parent[x] = find(parent[x]);
      return parent[x];
    }

    void link(value_type a, value_type b) {
      if (a == b) return;

      if (rank.at(a) > rank.at(b)) {
        parent.at(b) = a;
      } else {
        parent[a] = b;
        if (rank.at(a) == rank.at(b))
          rank.at(b) += 1;
      }
    }

    void union_set(value_type a, value_type b) {
      link(find(a), find(b));
    }

  private:
    std::map<value_type, std::size_t> rank;
    std::map<value_type, value_type> parent;
  };
}

#endif
