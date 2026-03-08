#include "test_common.hpp"

#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/bfs.hpp"

int main() {
  gr::CSRBuilder builder(6, true);

  // 0 -> 1 -> 2
  // 0 -> 3 -> 4
  // 5 isolated
  builder.add_edge(0, 1);
  builder.add_edge(1, 2);
  builder.add_edge(0, 3);
  builder.add_edge(3, 4);

  gr::CSRGraph g = builder.build();

  auto r = gr::bfs(0, g);

  GR_ASSERT(r.dist[0] == 0);
  GR_ASSERT(r.dist[1] == 1);
  GR_ASSERT(r.dist[2] == 2);
  GR_ASSERT(r.dist[3] == 1);
  GR_ASSERT(r.dist[4] == 2);

  // unreachable
  GR_ASSERT(r.dist[5] >= 100000000);

  pass("test_bfs");

  return EXIT_SUCCESS;
}