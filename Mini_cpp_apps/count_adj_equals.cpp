#include "function_declarations.h"
template <typename T> bool equal_to(const T &left, const T &right) {
  return left == right;
}

int plus(int left, int right) { return left + right; }

template <typename T, typename Inner> int count_adj_equals(const T &xs) {
  return std::inner_product(std::begin(xs), std::end(xs) - 1,
                            std::begin(xs) + 1, 0, plus, equal_to<Inner>);
}

// counts how many adjacent letters are equal (string type)
template int count_adj_equals<std::string>(const std::string &xs);
