#include <iostream>
#include <numeric>
#include <string>

template <typename T> bool less_than_or_equal(const T &left, const T &right) {
  return left <= right;
}

bool conjunction(bool left, bool right) { return left && right; }

template <typename T, typename Inner = typename T::value_type>
int is_sorted(const T &xs) {
  return std::inner_product(std::begin(xs), std::end(xs) - 1,
                            std::begin(xs) + 1, true, conjunction,
                            less_than_or_equal<Inner>);
}

// counts if all letters are sorted in STRING
template int is_sorted<std::string>(const std::string &xs);
