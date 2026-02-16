#include <iostream>
#include "../include/gr/graph_adjlist.hpp"
#include "../include/gr/algorithms/bfs.hpp"
#include "../include/gr/utils/print.hpp"
#include "../include/gr/algorithms/dfs.hpp"
#include "../include/gr/algorithms/sssp.hpp"

int main()
{
  // gr::AdjListGraph g(12, true);

  // g.add_edge(0, 1, 4);
  // g.add_edge(0, 2, 2);
  // g.add_edge(1, 3, 1);
  // g.add_edge(2, 3, 3);
  // g.add_edge(3, 4, 2);
  // g.add_edge(4, 5, 1);
  // g.add_edge(5, 3, 1);
  // g.add_edge(2, 6, 4);
  // g.add_edge(6, 7, 1);
  // g.add_edge(7, 2, 2);

  // g.add_edge(8, 9, 1);
  // g.add_edge(9, 10, 2);
  // g.add_edge(10, 11, 3);
  // g.add_edge(11, 9, 1);

  // For SCC
  gr::AdjListGraph g(9, true);
  // SCC 1: 0 -> 1 -> 2 -> 0
  g.add_edge(0, 1, 1);
  g.add_edge(1, 2, 1);
  g.add_edge(2, 0, 1);

  // edge from SCC1 to SCC2
  g.add_edge(2, 3, 1);

  // SCC 2: 3 -> 4 -> 5 -> 3
  g.add_edge(3, 4, 1);
  g.add_edge(4, 5, 1);
  g.add_edge(5, 3, 1);

  // edge from SCC2 to SCC3
  g.add_edge(5, 6, 1);

  // SCC 3: 6 <-> 7
  g.add_edge(6, 7, 1);
  g.add_edge(7, 6, 1);

  // Node 8 alone, reachable from 7 but no return
  g.add_edge(7, 8, 1);

  std::cout << "BFS (src = 0)\n";
  auto bfs_result = gr::bfs(0, g);
  gr::print_bfs_result(bfs_result);

  std::cout << "DFS (start/end time, color, pred)\n";
  auto dfs_result = gr::dfs(g);
  gr::print_dfs_result(dfs_result);

  std::cout << "SSSP (src = 0)\n";
  auto sssp_result = gr::sssp(g, 0);
  gr::print_sssp_result(sssp_result);

  std::cout << "APSP\n";
  auto apsp_result = gr::apsp(g);
  gr::print_apsp_result(apsp_result);

  std::cout << "SCC\n";
  auto scc_result = gr::scc(g);
  gr::print_scc_result(scc_result);

  return 0;
}