#include "test_common.hpp"

#include <cmath>
#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/analytics/pagerank.hpp"

int main() {
  // 0 -> 1 -> 2 -> 0

  // Symmetric graph
  gr::CSRBuilder builder(3, true);
  builder.add_edge(0, 1);
  builder.add_edge(1, 2);
  builder.add_edge(2, 0);

  gr::CSRGraph g = builder.build();

  auto r = gr::pagerank(g, 50, 0.85);

  GR_ASSERT((int)r.pr.size() == 3);

  // All should be approximately equal
  GR_ASSERT(std::fabs(r.pr[0] - r.pr[1]) < 1e-9);
  GR_ASSERT(std::fabs(r.pr[1] - r.pr[2]) < 1e-9);

  // Sum should be approximately 1
  double sum = 0.0;
  for (double x : r.pr) sum += x;
  GR_ASSERT(std::fabs(sum - 1.0) < 1e-9);

  pass("test_pagerank");
  return 0;
}