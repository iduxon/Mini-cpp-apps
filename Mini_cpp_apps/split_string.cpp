#include "function_declarations.h"

std::vector<std::string> split(const std::string &str) {
  std::vector<std::string> result;
  auto i = str.cbegin();

  while (i != str.cend()) {
    i = std::find_if_not(i, str.cend(), isspace);
    auto j = std::find_if(i, str.cend(), isspace);
    if (i != str.cend()) {
      result.push_back(std::string(i, j));
    }
    i = j;
  }
  return result;
}
