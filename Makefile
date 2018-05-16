test: tests/contiguous_heap.cc tests/dijkstra.cc tests/disjoint_set.cc tests/kruskal.cc tests/main.cc
	$(CXX) --std=c++17 tests/*.cc -o test
	./test
