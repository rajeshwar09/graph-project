#pragma once
#include <vector>
#include "types.hpp"

namespace graph {
  class IGraph {
    public:
      // Destructor
      virtual ~IGraph() = default;
      // Number of vertices
      virtual NodeId num_vertices() const = 0;
      // Tell if graph is undirected of directed
      virtual bool is_directed() const = 0;
      // List of edges
      virtual const std::vector<Edge>& neighbors(NodeId u) const = 0;
  };
}