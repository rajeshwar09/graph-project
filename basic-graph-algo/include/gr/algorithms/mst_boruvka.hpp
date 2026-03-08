#pragma once
#include <vector>
#include "../graph_csr.hpp"

namespace gr {
  
  struct MSTEdge {
    NodeId u;
    NodeId v;
    Weight w;
  };

  struct MSTResult {
    std::vector<MSTEdge> edges;
    Weight mst_cost = 0;
  };

  struct DSU {
    std::vector<NodeId> parent;
    std::vector<int> rank;
    int num_compoennts = 0;

    DSU(NodeId n = 0) {
      init(n);
    }

    void init(NodeId n) {
      parent.resize(n);
      rank.assign(n, 0);
      num_compoennts = 0;

      for (NodeId i = 0; i < n; i++) {
        parent[i] = i;
      }
    }

    NodeId find(NodeId x) {
      if (parent[x] == x) return x;
      parent[x] = find(parent[x]);
      return parent[x];
    }

    bool unite(NodeId a, NodeId b) {
      a = find(a);
      b = find(b);

      if (a == b) {
        return false;
      }

      if (rank[a] < rank[b]) {
        parent[a] = b;
      } else if (rank[a] > rank[b]) {
        parent[b] = a;
      } else {
        parent[b] = a;
        rank[a]++;
      }

      num_compoennts--;

      return true;
    }

    int components() const {
      return num_compoennts;
    }
  };

  // to store the cheapest edge
  struct CandidateEdge {
    NodeId u = -1;
    NodeId v = -1;
    Weight w = std::numeric_limits<Weight>::max();
    bool valid = false;
  };

  inline MSTResult mst_boruvka(const IGraph& g) {
    MSTResult result;

    const NodeId n = g.num_vertices();
    if (n == 0) {
      return result;
    }

    DSU dsu(n);

    while (dsu.components() > 1) {
      std::vector<CandidateEdge> cheapest(n);

      // Scanning all the edges to get the cheapest one
      for (NodeId u = 0; u < n; u++) {
        for (const auto& e: g.neighbors(u)) {
          NodeId v = e.to;
          Weight w = e.w;

          NodeId cu = dsu.find(u);
          NodeId cv = dsu.find(v);

          if (cu == cv) continue;

          if (!cheapest[cu].valid || w < cheapest[cu].w) {
            cheapest[cu] = {u, v, w, true};
          }

          if (!cheapest[cv].valid || w < cheapest[cv].w) {
            cheapest[cv] = {u, v, w, true};
          }
        }
      }

      bool progress = false;

      // adding selected cheapest edges
      for (NodeId c = 0; c < n; c++) {
        if (!cheapest[c].valid) continue;

        NodeId u = cheapest[c].u;
        NodeId v = cheapest[c].v;
        Weight w = cheapest[c].w;

        if (dsu.unite(u, v)) {
          result.edges.push_back({u, v, w});
          result.mst_cost += w;
          progress = true;
        }
      }

      if (!progress) break;
    }

    return result;
  }
}