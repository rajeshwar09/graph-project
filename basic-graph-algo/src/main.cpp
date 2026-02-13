#include <iostream>
#include "../include/gr/graph_adjlist.hpp"
#include "../include/gr/algorithms/bfs.hpp"

int main()
{
  gr::AdjListGraph g(6, true);
  g.add_edge(0, 1);
  g.add_edge(1, 2);
  g.add_edge(0, 3);
  g.add_edge(3, 4);
  g.add_edge(4, 2);

  auto result = gr::bfs(0, g);

  for (int v = 0; v < g.num_vertices(); v++)
  {
    if (result.dist[v] >= 1e8)
    {
      std::cout << v << ": INF\n";
    }
    else
    {
      std::cout << "vertex= " << v << "\tdist= " << result.dist[v] << "\tpred= " << result.pred[v] << "\n";
    }
  }
}