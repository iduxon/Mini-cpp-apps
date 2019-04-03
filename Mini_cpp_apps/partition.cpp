#include "function_declarations.h"

template <typename T> void partition(std::vector<T> &xs) {
  // In this version we divide the vector into even(first half), dividable by 3
  // ,and rest
  const auto first_end = std::stable_partition(
      std::begin(xs), std::end(xs), [](auto i) { return i % 2 == 0; });
  const auto second_end = std::stable_partition(
      first_end, std::end(xs), [](auto i) { return i % 3 == 0; });
}

template void partition<int>(std::vector<int> &xs);
