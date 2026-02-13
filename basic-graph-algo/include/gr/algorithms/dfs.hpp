#pragma once
#include <vector>
#include "../igraph.hpp"

namespace gr {
  enum class Color: unsigned char {WHITE, GRAY, BLACK};

  struct DFSResult {
    std::vector<Color> color;
    std::vector<int> start;
    std::vector<int> etime;
    std::vector<NodeId> pred;
  };

  inline void traverse(NodeId p, const IGraph& g, int& clock, DFSResult& result) {
    // Setting discovery time + color to GRAY
    result.start[p] = ++clock;
    result.color[p] = Color::GRAY;

    // Loop through neighbors + recursion on WHITE vertices
    for (const auto& edge: g.neighbors(p)) {
      NodeId t = edge.to;

      if (result.color[t] == Color::WHITE) {
        result.pred[t] = p;
        traverse(t, g, clock, result);
      }
    }

    // Setting finish time + color to BLACK
    result.color[p] = Color::BLACK;
    result.etime[p] = ++clock;
  }

  inline DFSResult dfs(const IGraph& g) {
    DFSResult result;

    // Initialize clock variable
    int clock = 0;

    // Initialization of result arrays
    result.color.assign(g.num_vertices(), Color::WHITE);
    result.start.assign(g.num_vertices(), -1);
    result.etime.assign(g.num_vertices(), -1);
    result.pred.assign(g.num_vertices(), (NodeId) - 1);

    // Looping all vertices and call traverse for WHITE vertices
    for (NodeId p = 0; p < g.num_vertices(); p++) {
      if (result.color[p] == Color::WHITE) {
        traverse(p, g, clock, result);
      }
    }

    return result;
  }
}