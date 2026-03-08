#include "test_common.hpp"

#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/dfs.hpp"

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

  auto r = gr::dfs(g);

  for (int v = 0; v < g.num_vertices(); v++) {
    GR_ASSERT(r.start[v] != -1);
    GR_ASSERT(r.etime[v] != -1);
    GR_ASSERT(r.start[v] < r.etime[v]);
  }

  pass("test_dfs");

  return EXIT_SUCCESS;
}