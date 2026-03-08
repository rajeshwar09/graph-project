#include <iostream>
#include "../include/gr/graph_csr.hpp"
#include "../include/gr/algorithms/bfs.hpp"
#include "../include/gr/utils/print.hpp"
#include "../include/gr/algorithms/dfs.hpp"
#include "../include/gr/algorithms/sssp.hpp"
#include "../include/gr/algorithms/mst_boruvka.hpp"

int main()
{
  // gr::CSRBuilder builder(12, true);

  // builder.add_edge(0, 1, 4);
  // builder.add_edge(0, 2, 2);
  // builder.add_edge(1, 3, 1);
  // builder.add_edge(2, 3, 3);
  // builder.add_edge(3, 4, 2);
  // builder.add_edge(4, 5, 1);
  // builder.add_edge(5, 3, 1);
  // builder.add_edge(2, 6, 4);
  // builder.add_edge(6, 7, 1);
  // builder.add_edge(7, 2, 2);

  // builder.add_edge(8, 9, 1);
  // builder.add_edge(9, 10, 2);
  // builder.add_edge(10, 11, 3);
  // builder.add_edge(11, 9, 1);

  // For SCC
  gr::CSRBuilder builder(9, true);

  // SCC 1: 0 -> 1 -> 2 -> 0
  builder.add_edge(1, 2, 1);
  builder.add_edge(0, 1, 1);
  builder.add_edge(2, 0, 1);

  // edge from SCC1 to SCC2
  builder.add_edge(2, 3, 1);

  // SCC 2: 3 -> 4 -> 5 -> 3
  builder.add_edge(3, 4, 1);
  builder.add_edge(4, 5, 1);
  builder.add_edge(5, 3, 1);

  // edge from SCC2 to SCC3
  builder.add_edge(5, 6, 1);

  // SCC 3: 6 <-> 7
  builder.add_edge(6, 7, 1);
  builder.add_edge(7, 6, 1);

  // Node 8 alone, reachable from 7 but no return
  builder.add_edge(7, 8, 1);

  gr::CSRGraph g = builder.build();

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

  std::cout << "MST\n";
  gr::CSRBuilder mst_builder(4, false);
  mst_builder.add_edge(0, 1, 1);
  mst_builder.add_edge(1, 3, 2);
  mst_builder.add_edge(0, 3, 3);
  mst_builder.add_edge(0, 2, 4);
  mst_builder.add_edge(2, 3, 5);

  gr::CSRGraph mst_graph = mst_builder.build();
  auto mst_res = gr::mst_boruvka(mst_graph);
  gr::print_mst_boruvka_result(mst_res);

  return 0;
}