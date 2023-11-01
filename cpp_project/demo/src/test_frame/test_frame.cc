
#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include "value_traits.h"

void test_key_generator() {
  KeyGenerator kg;
  auto v1 = kg.GenKey(1);
  std::cout << v1.str << std::endl;
  v1 = kg.GenKey(1, 3.0, true);
  std::cout << v1.str << std::endl;
  // v1 = kg.GenKey(1, 3.0, true, "hello");
}


int test_chrono() {
  std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>
      tp = std::chrono::time_point_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now());
  auto epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
      tp.time_since_epoch());
  auto before = epoch - std::chrono::milliseconds(1000 * 60 * 60 * 24 * 600);
  auto it = before.count();
  std::cout << "before:" << before.count() << ", epoch:" << epoch.count()
            << std::endl;
  return 0;
}
int main(int argc, char *argv[]) {

  test_key_generator();

  return 0;
}