#pragma once
#include <vector>
#include "../igraph.hpp"

namespace gr {

  struct MISResult {
    std::vector<uint8_t> in_mis;
    std::vector<NodeId> vertices;
  };

  inline MISResult maximal_independent_set(const IGraph& g) {
    MISResult result;

    const NodeId n = g.num_vertices();

    std::vector<uint8_t> active(n, 1);
    result.in_mis.assign(n, 0);
    result.vertices.clear();

    while (true) {
      NodeId chosen = -1;

      // choosing 1st active vertex
      for (NodeId v = 0; v < n; v++) {
        if (active[v]) {
          chosen = v;
          break;
        }
      }

      if (chosen == -1) break; // no active vertex left

      // add to MIS
      result.in_mis[chosen] = 1;
      result.vertices.push_back(chosen);

      // remove the chosen vertex
      active[chosen] = 0;

      // removing all its neighbours
      for (const auto& e: g.neighbors(chosen)) {
        active[e.to] = 0;
      }
    }

    return result;
  }
}