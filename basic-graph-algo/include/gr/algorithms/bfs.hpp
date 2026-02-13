#pragma once
#include <vector>
#include "../igraph.hpp"

namespace gr
{

  // For output
  struct BFSResult
  {
    std::vector<int> dist;
    std::vector<NodeId> pred;
  };

  inline BFSResult bfs(NodeId src, const IGraph &g)
  {
    // INF value
    const int INF = 1e9;

    // Initialization
    BFSResult result;
    result.dist.assign(g.num_vertices(), INF);
    result.pred.assign(g.num_vertices(), (NodeId)-1);

    // Setting distance to 0 and rest to INF
    result.dist[src] = 0;

    while (true)
    {
      bool changed = false;

      // For each vertex p in g
      for (NodeId p = 0; p < g.num_vertices(); p++)
      {
        // For each edge t in neighbors of p
        for (const auto &edge : g.neighbors(p))
        {
          NodeId t = edge.to;

          // t.dist > (p.dist + 1)
          if (result.dist[t] > (result.dist[p] + 1))
          {
            result.dist[t] = result.dist[p] + 1;
            result.pred[t] = p;
            changed = true;
          }
        }
      }

      if (changed == false)
      {
        break;
      }
    }

    return result;
  }
}