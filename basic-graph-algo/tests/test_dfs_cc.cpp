#include "test_common.hpp"

#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/dfs_cc.hpp"

int main() {
  // Undirected graph with 3 components:
  // Component A: 0-1-2
  // Component B: 3-4
  // Component C: 5 alone
  gr::CSRBuilder builder(6, false); // undirected

  builder.add_edge(0, 1);
  builder.add_edge(1, 2);

  builder.add_edge(3, 4);

  gr::CSRGraph g = builder.build();

  auto r = gr::dfs(g);

  // Same component checks
  GR_ASSERT(r.component[0] == r.component[1]);
  GR_ASSERT(r.component[1] == r.component[2]);

  GR_ASSERT(r.component[3] == r.component[4]);

  // Different components checks
  GR_ASSERT(r.component[0] != r.component[3]);
  GR_ASSERT(r.component[0] != r.component[5]);
  GR_ASSERT(r.component[3] != r.component[5]);

  pass("test_dfs_cc");

  return EXIT_SUCCESS;
}