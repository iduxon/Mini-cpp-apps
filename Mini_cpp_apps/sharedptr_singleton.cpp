#include <memory>
#include <mutex>

// stays alive while it is being used
template <typename T> std::shared_ptr<T> dynamic_singleton() {
  // has to be weak so we cant claim ownership,and it can automatically destroy
  static std::weak_ptr<T> s_instance;

  static std::mutex s_mutex;
  std::lock_guard<std::mutex> singleton_lock(s_mutex);

  // cant access what weak ptr is pointing to,we have to make it shared_ptr:
  auto result = s_instance.lock();

  if (s_instance.expired()) {
    result = std::make_shared<T>();
    s_instance = result;
  }
  return result;
}
