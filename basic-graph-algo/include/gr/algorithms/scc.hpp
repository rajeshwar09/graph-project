#pragma once
#include <vector>
#include <algorithm>
#include "../igraph.hpp"
#include "../graph_adjlist.hpp"
#include "../algorithms/dfs.hpp"

namespace gr {

  struct SCCResult {
    std::vector<int> components;
    int num_components = 0;
  };

  // Helper DFS that also updates the component number
  inline void dfs_for_scc(NodeId u, const IGraph& g, std::vector<uint8_t>& visited, std::vector<int>& components, int cid) {
    visited[u] = 1;
    components[u] = cid;

    for (const auto& e: g.neighbors(u)) {
      NodeId v = e.to;
      if (!visited[v]) {
        dfs_for_scc(v, g, visited, components, cid);
      }
    }
  }

  inline SCCResult scc(const IGraph& g) {
    SCCResult result;
    DFSResult dfs_result;

    auto n = g.num_vertices();

    // Initialization
    result.components.assign(n, -1);

    // Computing end/finish time
    dfs_result = dfs(g);

    // Creating transpose of given graph g ie. reversing edges
    AdjListGraph g_t(n, true);
    for (NodeId u = 0; u < n; u++) {
      for (const auto& e: g.neighbors(u)) {
        g_t.add_edge(e.to, u, e.w);
      }
    }

    // Sorting vertices in decreasing finish time
    std::vector<NodeId> order(n);
    for (NodeId i = 0; i < n; i++) {
      order[i] = i;
    }
    
    std::sort(order.begin(), order.end(), [&](NodeId a, NodeId b) {
      return dfs_result.etime[a] > dfs_result.etime[b];
    });

    // Perforing DFS on reversed graph in the given order
    // Every DFS tree will give 1 SCC
    std::vector<uint8_t> visited(n, 0);
    int cid = 0;

    for (NodeId v: order) {
      if (!visited[v]) {
        dfs_for_scc(v, g_t, visited, result.components, cid);
        cid++;
      }
    }

    result.num_components = cid;
    return result;
    
  }
}