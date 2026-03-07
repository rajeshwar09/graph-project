#pragma once
#include <iostream>
#include <cstdlib>

#define GR_ASSERT(cond)                                         \
  do {                                                          \
    if (!(cond)) {                                              \
      std::cerr << "[FAIL] " << __FILE__ << ":" << __LINE__     \
                << "  (" << #cond << ")\n";                     \
      std::exit(1);                                             \
    }                                                           \
  } while (0)

  inline void pass(const char* name) {
    std::cout << "[PASS] " << name << "\n";
  }