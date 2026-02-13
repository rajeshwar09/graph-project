#pragma once
#include <iostream>
#include <vector>
#include "../igraph.hpp"
#include "../types.hpp"
#include "../algorithms/bfs.hpp"
#include "../algorithms/dfs.hpp"

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
}