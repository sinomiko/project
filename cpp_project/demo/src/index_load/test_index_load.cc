#include <atomic>
#include <chrono> // std::chrono::milliseconds
#include <cstdlib>
#include <future> // std::async, std::future
#include <gflags/gflags.h>
#include <iostream>
#include <sstream>
#include <thread> // std::this_thread::sleep_for
#include <vector>

using namespace std;

#ifndef GFLAGS_NAMESPACE
#define GFLAGS_NAMESPACE gflags
#endif

DEFINE_string(a, "0.0.0.0:8118", "Program address.");
DEFINE_string(c, "./config.cfg", "Program config file.");
DEFINE_string(v, "", "Full index version");
DEFINE_string(t, "", "Realtime kafka topic");
DEFINE_string(s, "", "Realtime kafka kafka start offset");
DEFINE_string(p, "", "Full version path");
DEFINE_string(r, "", "kafka config");

static std::string UsageString(const char *program_name) {
  std::stringstream ss;
  ss << " Usage:\n\n";
  ss << "  Run:\n  ";
  ss << program_name;
  ss << " -c config.cfg [--daemon|-d] [--pidfile pidfile] \n";
  return ss.str();
}

bool Start(int argc, char **argv) {
  GFLAGS_NAMESPACE::SetVersionString("1.0.0");
  GFLAGS_NAMESPACE::SetUsageMessage(UsageString(argv[0]));
  GFLAGS_NAMESPACE::ParseCommandLineFlags(&argc, &argv, true);
  std::cout << "22 flags_a:" << FLAGS_a << std::endl;
  return true;
}

int testGlags(int argc, char *argv[]) {
  std::cout << "11 flags_a:" << FLAGS_a << std::endl;

  int ii = 0;

  // 显示参数的个数
  printf("argc is %d\n", argc);

  // 列出全部的参数
  for (ii = 0; ii < argc; ii++) {
    printf("argv[%d] is %s\n", ii, argv[ii]);
  }
  std::cout << "test" << std::endl;
  int new_argc = 9;
  std::vector<char *> new_argv;
  new_argv.push_back(argv[0]);
  new_argv.push_back("-p");
  new_argv.push_back("ppppp");
  new_argv.push_back("-r");
  new_argv.push_back("rrrrr");
  new_argv.push_back("-c");
  new_argv.push_back("ccccc");
  new_argv.push_back("-a");
  std::string addr = "0.0.0.0:" + std::to_string(8888);
  new_argv.push_back((char *)addr.c_str());
  if (!Start(new_argc, new_argv.data())) {

    return 1;
  }
  return 0;
}

int LoadIndex(int i) {
  std::this_thread::sleep_for(std::chrono::seconds(30));
  return 0;
}

std::atomic<bool> g_index_loading(false);

bool is_prime(int x) {
  // for (int i=2; i<x; ++i) if (x%i==0) return false;
  std::cout << "is_prime:" << x << "\n" << std::flush;

  std::this_thread::sleep_for(std::chrono::milliseconds(x));
  g_index_loading.store(false);

  return true;
}

bool load_thread(int x, int y) {
  std::cout << "load_thread...\n" << std::flush;
  if (g_index_loading.load()) {
    std::cout << "loading...\n" << std::flush;

    return false;
  }

  g_index_loading.store(true);
  std::thread t(is_prime, x);
  t.detach();
  std::this_thread::sleep_for(std::chrono::milliseconds(y));

  std::cout << "load_thread after \n" << std::flush;
  return true;
}

void test_index_load() {
  bool ret = load_thread(1000, 10);
  std::cout << "ret:" << ret << "\n" << std::flush;
  // std::this_thread::sleep_for (std::chrono::milliseconds(50));

  ret = load_thread(1, 1);
  std::cout << "ret:" << ret << "\n" << std::flush;
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  ret = load_thread(1, 200);
  std::cout << "ret:" << ret << "\n" << std::flush;

  std::string value = "14443434343434343434";
  uint64_t a;
  char *end;
  a = strtoull(value.c_str(), &end, 10);
  std::cout << "UInt64: " << a << "\n";
}


int main(int argc, char *argv[]) {

  test_index_load();

  return 0;
}