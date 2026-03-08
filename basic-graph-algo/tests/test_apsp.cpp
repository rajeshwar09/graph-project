#include "test_common.hpp"

#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/apsp.hpp"

int main() {
  gr::CSRBuilder builder(4, true);

  // 0->1 (3)
  // 1->2 (4)
  // 0->2 (10)  => should become 7 via 1
  // 2->3 (2)
  builder.add_edge(0, 1, 3);
  builder.add_edge(1, 2, 4);
  builder.add_edge(0, 2, 10);
  builder.add_edge(2, 3, 2);

  gr::CSRGraph g = builder.build();
  
  auto r = gr::apsp(g);

  GR_ASSERT(r.dist[0][0] == 0);
  GR_ASSERT(r.dist[0][1] == 3);
  GR_ASSERT(r.dist[0][2] == 7); // improve via 1
  GR_ASSERT(r.dist[0][3] == 9); // 0 -> 1 -> 2 -> 3
  GR_ASSERT(r.dist[1][3] == 6); // 1 -> 2 -> 3

  pass("test_apsp");

  return EXIT_SUCCESS;
}