#include "test_common.hpp"

#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/scc.hpp"

int main() {
  gr::CSRBuilder builder(9, true);

  // SCC A: {0,1,2}
  builder.add_edge(0, 1, 1);
  builder.add_edge(1, 2, 1);
  builder.add_edge(2, 0, 1);

  builder.add_edge(2, 3, 1);

  // SCC B: {3,4,5}
  builder.add_edge(3, 4, 1);
  builder.add_edge(4, 5, 1);
  builder.add_edge(5, 3, 1);

  builder.add_edge(5, 6, 1);

  // SCC C: {6,7}
  builder.add_edge(6, 7, 1);
  builder.add_edge(7, 6, 1);

  // node 8 alone
  builder.add_edge(7, 8, 1);

  gr::CSRGraph g = builder.build();
  
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