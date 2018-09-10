#include <cstddef>
#include <cassert>
#include <iostream>
#include "my_array.h"

template<typename T, std::size_t N>
void test_core() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.empty();
  ca.empty();
  a.size();
  ca.size();

  a.at(0);
  ca.at(0);
  a[0];
  ca[0];
  (void)static_cast<const T &>(a[0]);
  (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.fill(T());

  a[0] = T();
  a[0] = a[0];
  a[0] = ca[0];
}

class NonCopyable {
 public:
  NonCopyable() {}
 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable);
};

int main() {
  test_core<int, 10>();
  test_core<bool, 10>();
  test_core<NonCopyable, 10>();

  test_assign<int, 10>();
  test_assign<bool, 10>();

  const std::size_t N = 10;
  my_array<bool, N> a;
  for (size_t i = 0; i < N; i++) {
    a[i] = (i % 3) & 1;
  }

  for (size_t i = 0; i + 1 < N; i++) {
    a[i] = a[i + 1];
    std::cerr << a[i] << ' ' << a[i + 1] << '\n';
    assert(a[i] == a[i + 1]);
  }
}