#include "test_common.hpp"

#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/mis.hpp"

int main() {

  // Path graph: 0 - 1 - 2 - 3 - 4
  gr::CSRBuilder builder(5, false); // undirected
  builder.add_edge(0, 1);
  builder.add_edge(1, 2);
  builder.add_edge(2, 3);
  builder.add_edge(3, 4);

  gr::CSRGraph g = builder.build();

  auto r = gr::maximal_independent_set(g);

  // Checking exact chosen set
  GR_ASSERT((int)r.vertices.size() == 3);
  GR_ASSERT(r.in_mis[0] == 1);
  GR_ASSERT(r.in_mis[1] == 0);
  GR_ASSERT(r.in_mis[2] == 1);
  GR_ASSERT(r.in_mis[3] == 0);
  GR_ASSERT(r.in_mis[4] == 1);

  // no edge should have both endpoints in MIS
  for (gr::NodeId u = 0; u < g.num_vertices(); u++) {
    for (const auto& e : g.neighbors(u)) {
      gr::NodeId v = e.to;
      GR_ASSERT(!(r.in_mis[u] && r.in_mis[v]));
    }
  }

  // every vertex not in MIS must have at least one selected neighbor
  for (gr::NodeId u = 0; u < g.num_vertices(); u++) {
    if (r.in_mis[u]) continue;

    bool has_selected_neighbor = false;
    for (const auto& e : g.neighbors(u)) {
      if (r.in_mis[e.to]) {
        has_selected_neighbor = true;
        break;
      }
    }
    GR_ASSERT(has_selected_neighbor);
  }

  pass("test_mis");
  return 0;
}