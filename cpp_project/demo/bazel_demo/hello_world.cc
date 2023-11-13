#include <iostream>
#include <string>
#include <vector>

#include "absl/strings/str_join.h"
#include "absl/random/random.h"

int main() {
  std::vector<std::string> v = {"foo", "bar", "baz"};
  std::string s = absl::StrJoin(v, "-");

  absl::BitGen bitgen;

  std::cout << "Joined string: " << s << "\n";
  std::cout << "Number: " << absl::Uniform(bitgen, 0, 1.0) << "\n"; 

  return 0;
}