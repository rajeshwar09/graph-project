#include "test_common.hpp"

#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/mst_boruvka.hpp"

int main() {
  // Undirected weighted graph
  //
  // 0 --1-- 1
  // | \     |
  // 4  3    2
  // |    \  |
  // 2 --5-- 3

  gr::CSRBuilder builder(4, false);
  builder.add_edge(0, 1, 1);
  builder.add_edge(1, 3, 2);
  builder.add_edge(0, 3, 3);
  builder.add_edge(0, 2, 4);
  builder.add_edge(2, 3, 5);

  gr::CSRGraph g = builder.build();

  auto r = gr::mst_boruvka(g);

  GR_ASSERT((int)r.edges.size() == 3);
  GR_ASSERT(r.mst_cost == 7);

  pass("test_mst_boruvka");
  return 0;
}