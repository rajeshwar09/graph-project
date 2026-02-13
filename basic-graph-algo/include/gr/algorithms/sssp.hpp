#pragma once
#include <vector>
#include "../igraph.hpp"

namespace gr {

  struct SSSPResult {
    std::vector<Weight> dist;
    std::vector<NodeId> pred;
  };

  inline SSSPResult sssp(const IGraph& g, NodeId src) {
    SSSPResult result;

    // INF value
    const Weight INF = 1e9;

    // Initialization
    result.dist.assign(g.num_vertices(), INF);
    result.pred.assign(g.num_vertices(), (NodeId) - 1);

    // Setting source distace to 0
    result.dist[src] = 0;

    while (true) {
      bool changed = false;

      for (NodeId p = 0; p < g.num_vertices(); p++) {
        
        for (const auto& edge: g.neighbors(p)) {
          auto t = edge.to;
          
          if (result.dist[t] > (result.dist[p] + edge.w)) {
            result.dist[t] = result.dist[p] + edge.w;
            result.pred[t] = p;
            changed = true;
          }
        }
      }
      if (changed == false) {
        break;
      }
    }

    return result;
  }
}