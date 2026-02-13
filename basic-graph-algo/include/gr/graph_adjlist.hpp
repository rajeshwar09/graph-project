#pragma once
#include <vector>
#include <stdexcept>
#include "igraph.hpp"

namespace gr {
  class AdjListGraph final: public IGraph {
    private:
      NodeId n_;
      bool directed_;
      std::vector<std::vector<Edge>> adj_;

      // To check if node actually exists
      void check(NodeId u) const {
        if (u < 0 || u >= n_) 
          throw std::out_of_range("NodeId out of range");
      }
    public:
      AdjListGraph(NodeId n = 0, bool directed = false) : n_(n), directed_(directed), adj_(n) {}
      
      NodeId num_vertices() const override {
        return n_;
      }

      bool is_directed() const override {
        return directed_;
      }

      void add_edge(NodeId u, NodeId v, Weight w = 1) {
        check(u);
        check(v);

        adj_[u].push_back({v, w});
        if (!directed_) {
          adj_[v].push_back({u, w});
        }
      }

      // Return edges for the node "u"
      const std::vector<Edge>& neighbors(NodeId u) const override {
        check(u);
        return adj_[u];
      }
      
  };
}