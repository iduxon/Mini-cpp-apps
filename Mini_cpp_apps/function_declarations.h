#ifndef FUNCTION_DECLARATIONS_H
#define FUNCTION_DECLARATIONS_H
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#define UNUSED(x) ((void)x)

#ifdef QT_DEBUG
#define osErrorFatal(usrMsg)                                                   \
  osErrorFatalImpl((usrMsg), __FILE__, __func__, __LINE__)
#define osAssert(expr, usrMsg)                                                 \
  do {                                                                         \
    if (!(expr))                                                               \
      osErrorFatal(usrMsg);                                                    \
    \
                                                                          \
  } while (0)

void osErrorFatalImpl(const char *usrMsg, const char *fileName,
                      const char *funcName, const int lineNum) {
  perror(usrMsg);
  std::cerr << "File: " << fileName << "\nFunction: " << funcName
            << "\nLine: " << lineNum << std::endl;
  exit(EXIT_FAILURE);
}

#endif

void arb_selection_move();

template <typename T> bool equal_to(const T &left, const T &right);
int plus(int left, int right);
template <typename T, typename Inner = typename T::value_type>
extern int count_adj_equals(const T &xs);

template <typename T, typename Inner = typename T::value_type>
int is_sorted(const T &xs);

template <typename T> class equality {
public:
  bool operator==(const T &other) const;
  bool operator!=(const T &other) const;
};

template <typename T> void partition(std::vector<T> &xs);

std::vector<std::string> split(const std::string &str);

#include "equality.cpp"

#endif // FUNCTION_DECLARATIONS_H
