#include "test_common.hpp"

#include "../include/gr/graph_adjlist.hpp"
#include "../include/gr/algorithms/dfs.hpp"

int main() {
  gr::AdjListGraph g(6, true);

  // 0 -> 1 -> 2
  // 0 -> 3 -> 4
  // 5 isolated
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(0, 3);
  g.add_edge(3, 4);

  auto r = gr::dfs(g);

  for (int v = 0; v < g.num_vertices(); v++) {
    GR_ASSERT(r.start[v] != -1);
    GR_ASSERT(r.etime[v] != -1);
    GR_ASSERT(r.start[v] < r.etime[v]);
  }

  pass("test_dfs");

  return EXIT_SUCCESS;
}