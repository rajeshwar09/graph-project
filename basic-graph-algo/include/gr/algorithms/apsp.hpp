#pragma once
#include <vector>
#include <algorithm>
#include "../igraph.hpp"

namespace gr {

  struct APSPResult {
    std::vector<std::vector<Weight>> dist;
    std::vector<std::vector<NodeId>> pred;
  };

  inline APSPResult apsp(const IGraph& g) {
    APSPResult result;

    Weight INF = 1e9;

    auto n = g.num_vertices();

    result.dist.assign(n, std::vector<Weight>(n, INF));
    result.pred.assign(n, std::vector<NodeId>(n, (NodeId) - 1));

    for (gr::NodeId i = 0; i < g.num_vertices(); i++) {
      result.dist[i][i] = 0;
      result.pred[i][i] = i;

      for (const auto& edge: g.neighbors(i)) {
        auto p = edge.to;
        result.dist[i][p] = std::min(result.dist[i][p], edge.w);
        result.pred[i][p] = (NodeId) - 1;
      }
    }

    for (gr::NodeId k = 0; k < n; k++) {
      for (gr::NodeId i = 0; i < n; i++) {
        for (gr::NodeId j = 0; j < n; j++) {
          if (result.dist[i][k] != INF && result.dist[k][j] != INF) {
            if (result.dist[i][k] + result.dist[k][j] < result.dist[i][j]) {
              result.dist[i][j] = result.dist[i][k] + result.dist[k][j];
              result.pred[i][j] = k;
            }
          }
        }
      }
    }

    return result;
  }
}