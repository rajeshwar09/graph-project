#include "test_common.hpp"

#include "../include/gr/graph_adjlist.hpp"
#include "../include/gr/algorithms/scc.hpp"

int main() {
  gr::AdjListGraph g(9, true);

  // SCC A: {0,1,2}
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 1);
  g.add_edge(2, 0, 1);

  g.add_edge(2, 3, 1);

  // SCC B: {3,4,5}
  g.add_edge(3, 4, 1);
  g.add_edge(4, 5, 1);
  g.add_edge(5, 3, 1);

  g.add_edge(5, 6, 1);

  // SCC C: {6,7}
  g.add_edge(6, 7, 1);
  g.add_edge(7, 6, 1);

  // node 8 alone
  g.add_edge(7, 8, 1);

  auto r = gr::scc(g);

  GR_ASSERT(r.num_components == 4);

  // group check
  GR_ASSERT(r.components[0] == r.components[1]);
  GR_ASSERT(r.components[1] == r.components[2]);

  GR_ASSERT(r.components[3] == r.components[4]);
  GR_ASSERT(r.components[4] == r.components[5]);

  GR_ASSERT(r.components[6] == r.components[7]);

  // 8 has to be alone (!= SCC C)
  GR_ASSERT(r.components[0] == r.components[1]);

  pass("test_scc");

  return EXIT_SUCCESS;
}