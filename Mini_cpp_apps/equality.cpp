#include "function_declarations.h"

template <typename T> bool equality<T>::operator==(const T &other) const {
  return !((T &)*this != other);
}

template <typename T> bool equality<T>::operator!=(const T &other) const {
  return !((T &)*this == other);
}
