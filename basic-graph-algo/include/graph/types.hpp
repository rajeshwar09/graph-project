#pragma once
#include<cstdint>

namespace graph {
  using NodeId = int32_t;
  using Weight = int32_t;

  struct Edge {
    NodeId to;
    Weight w;
  };
}