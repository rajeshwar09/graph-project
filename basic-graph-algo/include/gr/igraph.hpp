#pragma once
#include <vector>
#include "types.hpp"

namespace gr {

  // -- added to work with CSR
  // to work with loops: for (auto &e: g.neighbours(u))
  struct NeighborRange {
    const Edge* b = nullptr;
    const Edge* e = nullptr;

    const Edge* begin() const { return b; }
    const Edge* end() const { return e; }
    
    int size() const { return (int)(e - b); }

    bool empty() const { return b == e; }
  };

  class IGraph {
    public:
      // Destructor
      virtual ~IGraph() = default;
      // Number of vertices
      virtual NodeId num_vertices() const = 0;
      // Tell if graph is undirected of directed
      virtual bool is_directed() const = 0;
      // List of edges

      // virtual const std::vector<Edge>& neighbors(NodeId u) const = 0;
      // -- updated for CSR
      virtual NeighborRange neighbors(NodeId u) const = 0;
  };
}