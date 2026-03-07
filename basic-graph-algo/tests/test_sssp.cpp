#include "test_common.hpp"

#include "../include/gr/graph_adjlist.hpp"
#include "../include/gr/algorithms/sssp.hpp"

int main() {
  gr::AdjListGraph g(6, true);

  // Weighted graph:
  // 0->1 (2)
  // 0->2 (5)
  // 1->2 (1)  => best 0->1->2 = 3
  // 2->3 (2)  => best 0->3 = 5
  // 0->3 (100) (bad direct)
  // 4,5 disconnected
  g.add_edge(0, 1, 2);
  g.add_edge(0, 2, 5);
  g.add_edge(1, 2, 1);
  g.add_edge(2, 3, 2);
  g.add_edge(0, 3, 100);

  auto r = gr::sssp(g, 0);

  GR_ASSERT(r.dist[0] == 0);
  GR_ASSERT(r.dist[1] == 2);
  GR_ASSERT(r.dist[2] == 3);  // 0 -> 1 -> 2
  GR_ASSERT(r.dist[3] == 5);  // 0 -> 1 -> 2 -> 3

  // If INF, these will star near INF
  GR_ASSERT(r.dist[4] >= 100000000);
  GR_ASSERT(r.dist[5] >= 100000000);

  pass("test_sssp");

  return EXIT_SUCCESS;
}