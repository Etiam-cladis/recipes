#include <array>
#include <chrono>
#include <iostream>

#include "ObjectPool/ObjectPool.hpp"

class ExpensiveObject {
public:
  ExpensiveObject() {}
  ~ExpensiveObject() = default;

private:
  std::array<double, 4 * 1024 * 1024> m_array;
};

int main() {
  const size_t NumberOfIterations{500'000};

  std::cout << "using pool..." << std::endl;
  ObjectPool<ExpensiveObject> pool;
  auto start1{std::chrono::steady_clock::now()};
  for (size_t i = 0; i < NumberOfIterations; ++i) {
    auto p = pool.acquiredObject();
  }
  auto end1{std::chrono::steady_clock::now()};
  auto diff1 = end1 - start1;
  std::cout << std::chrono::duration<double, std::milli>(diff1).count() << "ms"
            << std::endl;

  std::cout << "using new and delete..." << std::endl;
  auto start2{std::chrono::steady_clock::now()};
  for (size_t i = 0; i < NumberOfIterations; ++i) {
    auto *p = new ExpensiveObject;
    delete p;
    p = nullptr;
  }
  auto end2{std::chrono::steady_clock::now()};
  auto diff2 = end2 - start2;
  std::cout << std::chrono::duration<double, std::milli>(diff2).count() << "ms"
            << std::endl;
}