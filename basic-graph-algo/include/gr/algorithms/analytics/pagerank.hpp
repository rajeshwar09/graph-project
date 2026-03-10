#pragma once
#include <vector>
#include <cmath>
#include "../../graph_csr.hpp"

namespace gr {

  struct PageRankResult {
    std::vector<double> pr;
    int iterations = 0;
  };

  inline PageRankResult pagerank(const IGraph& g, int max_iters = 20, double damping = 0.85) {
    
    PageRankResult result;

    const NodeId n = g.num_vertices();
    if (n == 0) return result;

    // build transpose graph
    CSRGraph gt = build_transpose_csr(g);

    // outdegree edge of each vertex in orignal graph
    std::vector<int> outdeg(n, 0);
    for (NodeId u = 0; u < n; u++) {
      outdeg[u] = g.neighbors(u).size();
    }

    // Initial PR = 1/ N
    std::vector<double> curr(n, 1.0 / (double)n);
    std::vector<double> next(n, 0.0);

    const double base = (1.0 - damping) / (double)n;

    for (int iter = 0; iter < max_iters; iter++) {
      double dangling_sum = 0.0;

      // adding PR of dangling vertices
      for (NodeId u = 0; u < n; u++) {
        if (outdeg[u] == 0) {
          dangling_sum += curr[u];
        }
      }

      double dangling_contribution = damping * dangling_sum / (double)n;

      for (NodeId p = 0; p < n; p++) {
        double val = 0.0;

        // in-degree neighbots of p in orignal = neighbors of p in transpose
        for (const auto& e: gt.neighbors(p)) {
          NodeId t = e.to;
          if (outdeg[t] != 0) {
            val += curr[t] / (double)outdeg[t];
          }
        }

        next[p] = damping * val + base + dangling_contribution;
      }

      curr.swap(next);
      result.iterations = iter + 1;
    }

    result.pr = std::move(curr);
    
    return result;
  }
}