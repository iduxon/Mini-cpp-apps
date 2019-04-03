#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "function_declarations.h"
#include <memory>
#include <utility>
// Generic linked list

template <typename T> class linkedlist {
public:
  linkedlist();

  linkedlist(std::initializer_list<T> values) {
    for (const auto &value : values)
      push_front(value);
  }

  void push_back(const T &value) {
    auto new_element = std::make_unique<element>(value);

    if (!m_start)
      m_start = std::move(new_element);
    else {
      auto e = m_start.get();
      while (e->next)
        e = e->next.get();
      e->next = std::move(new_element);
    }
    m_size++;
  }

  void push_front(const T &value) {
    auto new_element = std::make_unique<element>(value, std::move(m_start));
    m_start = std::move(new_element);
    m_size++;
  }

  void pop_front() {
    auto old_start = std::move(m_start);
    m_start = std::move(old_start->next);
    m_size--;
  }

  void pop_back() {
    auto e = m_start.get();
    while (e->next->next) {
      e = e->next.get();
    }
    auto old_back = std::move(e->next.get());
    e->next = nullptr;
    m_size--;
  }

  linkedlist(const linkedlist &other) {
    for (size_t i = 0; i < other.m_size; i++)
      push_front(other[i]);
  }

  linkedlist(linkedlist &&other)
      : m_start(std::move(other.m_start)), m_size(other.m_size) {
    other.m_size = 0;
  }

  // copy or move constructor will be called
  // due to unique ptr,one object is destroyed
  linkedlist &operator=(linkedlist other) {
    std::swap(m_start, other.m_start);
    std::swap(m_size, other.m_size);
    return *this;
  }

  T &operator[](size_t index) { return at(index)->value; }
  const T &operator[](const size_t index) const { return at(index)->value; }

  size_t size() const { return m_size; }

  ~linkedlist() {
    while (m_start) {
      pop_front();
    }
  }

private:
  struct element {
    element(T value, std::unique_ptr<element> &&next = nullptr)
        : value(value), next(std::move(next)) {}
    T value;
    std::unique_ptr<element> next;
  };

  element *at(size_t index) const {
    if (!m_start || index > m_size)
      return nullptr;

    auto e = m_start.get();

    for (size_t i = 0; i < index; i++) {
      e = e->next.get();
      if (!e)
        return nullptr;
    }
    return e;
  }

  std::unique_ptr<element> m_start;
  size_t m_size = 0;
};

#endif // LINKEDLIST_H
