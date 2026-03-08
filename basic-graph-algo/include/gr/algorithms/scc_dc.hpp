#pragma once
#include <vector>
#include <random>
#include <queue>
#include "../igraph.hpp"
#include "../graph_csr.hpp"

namespace gr {

  struct SCCResultDC {
    std::vector<int> components;
    int num_components = 0;
  };

  // Forward-Reachable(Graph X, P, start)
  // Also used for Backward-Reachable
  // inP[v] == 1 means v is in current vertes set P
  // return inR[v] == 1 if reachable from start
  inline std::vector<uint8_t> fwd_reachable(const IGraph& X, const std::vector<uint8_t>& inP, NodeId start) {
    NodeId n = X.num_vertices();
    std::vector<uint8_t> inR(n, 0);

    if (start < 0 || start >= n) return inR;
    if (!inP[start]) return inR;

    std::queue<NodeId> q;
    inR[start] = 1;
    q.push(start);

    while (!q.empty()) {
      NodeId u = q.front();
      q.pop();

      for (const auto& e: X.neighbors(u)) {
        NodeId v = e.to;
        if (v < 0 || v >= n) continue;
        if (!inP[v]) continue;
        if (!inR[v]) {
          inR[v] = 1;
          q.push(v);
        }
      }
    }

    return inR;
  }

  // picking random pivot to start
  // (random because better average recursion balance)
  inline NodeId pick_pivot(const std::vector<NodeId>& P_list) {
    static thread_local std::mt19937 rng(123456789); //fixed seed for reproducibility
    std::uniform_int_distribution<size_t> dist(0, P_list.size() - 1);

    return P_list[dist(rng)];
  }

  // Recursive DnC SCC
  inline void ssc_dc_rec(
    const IGraph& G,
    const IGraph& GT,
    const std::vector<NodeId>& P_list,
    std::vector<int>& components,
    int& next_cid
  ) {
    // 1. if P is empty, return
    if (P_list.empty()) return;

    const NodeId n = G.num_vertices();

    // Build array for P
    std::vector<uint8_t> inP(n, 0);
    for (NodeId x: P_list) inP[x] = 1;

    // 2. pick random pivot
    NodeId v = pick_pivot(P_list);

    // 3. find forward vertices
    auto inV_fwd = fwd_reachable(G, inP, v);

    // 4. find backward vertices
    auto inV_bwd = fwd_reachable(GT, inP, v);

    // 5. ssc = intersection of step 3 and 4
    // 7. building subproblems
    std::vector<NodeId> A;  // inV_fwd \ ssc
    std::vector<NodeId> B;  // inV_bwd \ ssc
    std::vector<NodeId> C;  // P \ (Vfwd ∪ Vbwd)
    std::vector<NodeId> SCC_nodes;

    A.reserve(P_list.size());
    B.reserve(P_list.size());
    C.reserve(P_list.size());
    SCC_nodes.reserve(P_list.size());

    for (NodeId x: P_list) {
      const bool f = (inV_fwd[x] != 0);
      const bool b = (inV_bwd[x] != 0);

      if (f && b) {
        SCC_nodes.push_back(x);
      } else if (f && !b) {
        A.push_back(x);
      } else if (!f && b) {
        B.push_back(x);
      } else {
        C.push_back(x);
      }
    }

    // 6. assign component id to SCC
    const int cid = next_cid++;
    for (NodeId x: SCC_nodes) components[x] = cid;

    // 8. recursion on 3 disjoint sets A, B, C
    ssc_dc_rec(G, GT, A, components, next_cid);
    ssc_dc_rec(G, GT, B, components, next_cid);
    ssc_dc_rec(G, GT, C, components, next_cid);
  }

  inline SCCResultDC scc_dc(const IGraph& G) {
    SCCResultDC result;
    const NodeId n = G.num_vertices();

    result.components.assign(n, -1);

    // creating transpose graph
    CSRGraph GT = build_transpose_csr(G);

    // initial P = all verticces
    std::vector<NodeId> P_list(n);
    for (NodeId i = 0; i < n; i++) P_list[i] = i;

    int next_cid = 0;
    ssc_dc_rec(G, GT, P_list, result.components, next_cid);

    result.num_components = next_cid;

    return result;
  }
}