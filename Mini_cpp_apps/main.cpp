#include "function_declarations.h"

int main() {
  int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int n = getPairsCount(arr, 5, std::cend(arr) - std::cbegin(arr));
}
