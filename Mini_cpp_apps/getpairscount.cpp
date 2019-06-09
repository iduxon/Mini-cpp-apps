#include "function_declarations.h"
#include <map>

int getPairsCount(int arr[], int sum, int n) {
  std::map<int, int> map;

  for (int i = 0; i < n; i++) {
    map[arr[i]]++;
    std::cout << map[arr[i]] << ", ";
  }
  int twice_count = 0;
  for (int i = 0; i < n; i++) {
    twice_count += map[sum - arr[i]];
  }
}
