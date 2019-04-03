#include "function_declarations.h"
#include "raii.h"
#include <fstream>
#include <map>

void string_to_lower(std::string &str) {
  std::transform(str.begin(), str.end(), str.begin(), tolower);
}

class compare_ignorecase {
public:
  bool operator()(std::string left, std::string right) const {
    string_to_lower(left);
    string_to_lower(right);

    return left < right;
  }
};

void vocab(std::map<std::string, std::string, compare_ignorecase> &words,
           std::string fpath) {
  UNUSED(fpath);
  // change to fpath for file wanted
  std::ifstream in("C:\\Git\\Mini-cpp-apps\\Mini_cpp_apps\\words",
                   std::ifstream::in);
  std::string word;
  std::string definition;

  while (in >> word) {
    std::getline(in, definition);
    words[word] = definition;
  }

  std::string query;
  while (std::cin >> query) {
    auto lower = words.lower_bound(query);
    // first word out of querry scope
    (*query.rbegin())++;
    auto upper = words.lower_bound(query);
    for (; lower != upper; lower++) {
      std::cout << lower->first << " -> " << lower->second << std::endl;
    }
  }
}
