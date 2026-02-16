#pragma once
#include <iostream>
#include <vector>
#include "../igraph.hpp"
#include "../types.hpp"
#include "../algorithms/bfs.hpp"
#include "../algorithms/dfs.hpp"
#include "../algorithms/sssp.hpp"
#include "../algorithms/apsp.hpp"
#include "../algorithms/scc.hpp"

namespace gr {
  
  // Helper : color print for DFS
  inline const char* color_to_str(Color c) {
    switch (c) {
      case Color::WHITE: return "White";
      case Color::GRAY: return "Gray";
      case Color::BLACK: return "Black";
    }

    return "?";
  }

  // Vecotr printer (of any type)
  template <typename T>
  inline void print_vector(const std::vector<T>& v, const std::string& name) {
    std::cout << name << ":\n";
    for (size_t i = 0; i < v.size(); v++) {
      std::cout << i << " -> " << v[i] << "\n";
    }
  }

  // BFS result printer
  inline void print_bfs_result(const BFSResult& r) {
    std::cout << "vertex\tdist\tpred\n";
    for (size_t i = 0; i < r.dist.size(); i++) {
      if (r.dist[i] >= 1e8) {
        std::cout << i << "\tINF\t" << r.pred[i] << "\n";
      } 
      else {
        std::cout << i << "\t" << r.dist[i] << "\t" << r.pred[i] << "\n";
      }
    }
  }

  // DFS result printer
  inline void print_dfs_result(const DFSResult& r) {
    std::cout << "vertex\tcolor\tstart\tend\tpred\n";
    for (size_t i = 0; i < r.color.size(); i++) {
      std::cout << i
                << "\t" << color_to_str(r.color[i])
                << "\t" << r.start[i]
                << "\t" << r.etime[i]
                << "\t" << r.pred[i]
                << "\n";
    }
  }

  // SSSP result printer
  inline void print_sssp_result(const SSSPResult& r) {
    const Weight INF = 1e9;

    std::cout << "vertex\tdist\tpred\n";
    for (size_t i = 0; i < r.dist.size(); i++) {
      if (r.dist[i] >= INF) {
        std::cout << i << "\tINF\t" << r.pred[i] << "\n";
      }
      else {
        std::cout << i << "\t" << r.dist[i] << "\t" << r.pred[i] << "\n";
      }
    }
  }

  // APSP result printer
  inline void print_apsp_result(const APSPResult& r) {
    const Weight INF = 1e9;
    
    std::cout << "\t";
    for (size_t i = 0; i < r.dist.size(); i++) std::cout << i << "\t";
    std::cout << "\n";

    for (size_t i = 0; i < r.dist.size(); i++) {
      std::cout << i << "\t";

      for (size_t j = 0; j < r.dist.size(); j++) {
        if (r.dist[i][j] >= INF) std::cout << "INF\t";
        else std::cout << r.dist[i][j] << "\t";
      }
      std::cout << "\n";
    }
  }

  // SCC result printer
  inline void print_scc_result(const SCCResult& r) {
    std::cout << "num_components = " << r.num_components << "\n";
    std::cout << "vertex\tcomponent\n";
    for (size_t i = 0; i < r.components.size(); i++) {
      std::cout << i << "\t" << r.components[i] << "\n";
    }
  }
}