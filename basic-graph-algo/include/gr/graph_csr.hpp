#pragma once
#include <vector>
#include <stdexcept>
#include "igraph.hpp"

namespace gr {

  // Immutable CSR
  class CSRGraph final : public IGraph {
    private:
      NodeId n_;
      bool directed_;
      std::vector<int> offsets_;  // size = n + 1
      std::vector<Edge> edges_;   // size m

      void check (NodeId u) const {
        if (u < 0 || u >= n_) throw std::out_of_range("NodeId out of range");
      }
    
    public:
      CSRGraph() : n_(0), directed_(false) {}

      CSRGraph(
        NodeId n,
        bool directed,
        std::vector<int> offsets,
        std::vector<Edge> edges) : 
      n_(n), directed_(directed),
      offsets_(std::move(offsets)),
      edges_(std::move(edges)) {}
        
      NodeId num_vertices() const override { return n_; }
      bool is_directed() const override { return directed_; }

      NeighborRange neighbors(NodeId u) const override {
        check(u);
        int l = offsets_[u];
        int r = offsets_[u + 1];

        return NeighborRange { edges_.data() + l, edges_.data() + r };
      }

      long long num_edges() const { return (long long)edges_.size(); }
  };

  // CSR builder as CSR not good for new edge addition
  class CSRBuilder {
    private:
      struct RawEdge { 
        NodeId u, v; 
        Weight w; 
      };

      NodeId n_;
      bool directed_;
      std::vector<RawEdge> raw_;

      void check(NodeId u) const {
        if (u < 0 || u >= n_) throw std::out_of_range("NodeId out of range");
      }
    
    public:
      CSRBuilder(NodeId n = 0, bool directed = false)
        : n_(n), directed_(directed) {}
      
        NodeId num_vertices() const { return n_; }
        bool is_directed() const { return directed_; }

        void add_edge(NodeId u, NodeId v, Weight w = 1) {
          check(u);
          check(v);

          raw_.push_back({u, v, w});
          if (!directed_) raw_.push_back({v, u, w});
        }

        CSRGraph build(bool sort_neighbors_by_to = true) const {
          // 1. degree count
          std::vector<int> deg(n_, 0);
          for (const auto& e: raw_) deg[e.u]++;

          // 2. creating offsets
          std::vector<int> offsets(n_ + 1, 0);
          for (NodeId i = 0; i < n_; i++) {
            offsets[i + 1] = offsets[i] + deg[i];
          }

          // 3. creating edges set
          std::vector<Edge> edges(offsets[n_]);
          std::vector<int> cursor = offsets; // copy

          for (const auto& e: raw_) {
            int idx = cursor[e.u]++;
            edges[idx] = Edge{ e.v, e.w };
          }

          // sorting
          if (sort_neighbors_by_to) {
            for (NodeId u = 0; u < n_; u++) {
              int l = offsets[u];
              int r = offsets[u + 1];
              std::sort(edges.begin() + l, edges.begin() + r,
                [](const Edge& a, const Edge& b) {
                  if (a.to != b.to) return a.to < b.to;
                  return a.w < b.w;
                });
            }
          }

          return CSRGraph(n_, directed_, std::move(offsets), std::move(edges));
        }
  };

  inline CSRGraph build_transpose_csr(const IGraph& G) {
    NodeId n = G.num_vertices();
    CSRBuilder builder(n, true);

    for (NodeId u = 0; u < n; u++) {
      for (const auto& e: G.neighbors(u)) {
        builder.add_edge(e.to, u, e.w);
      }
    }

    return builder.build();
  }
}