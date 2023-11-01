#include <iostream>
#include <unistd.h>

struct Noisy {
  Noisy() { std::cout << "constructed at " << this << '\n'; }
  Noisy(const Noisy &) { std::cout << "copy-constructed\n"; }
  Noisy(Noisy &&) { std::cout << "move-constructed\n"; }
  ~Noisy() { std::cout << "destructed at " << this << '\n'; }
};

template <typename T> struct Wrapper {
  Wrapper(T t_) : t(t_) {
    std::cout << "Wrapper constructed at " << this << '\n';
  }
  Wrapper() { std::cout << "Wrapper constructed at " << this << '\n'; }
  Wrapper(const Wrapper &) { std::cout << "Wrapper copy-constructed\n"; }
  Wrapper(Wrapper &&) { std::cout << "Wrapper move-constructed\n"; }
  ~Wrapper() { std::cout << "Wrapper destructed at " << this << '\n'; }
  T t;
};

template <typename T> struct WrapperNew {
  WrapperNew() { std::cout << "WrapperNew constructed at " << this << '\n'; }
  // WrapperNew(T&& t_) :t(t_) { std::cout << "WrapperNew t copy constructed at
  // " << this << '\n'; }
  WrapperNew(T &&t_) : t(std::move(t_)) {
    std::cout << "WrapperNew constructed at " << this << '\n';
  }
  WrapperNew(const WrapperNew &) {
    std::cout << "WrapperNew copy-constructed\n";
  }
  WrapperNew(WrapperNew &&) { std::cout << "WrapperNew move-constructed\n"; }
  ~WrapperNew() { std::cout << "WrapperNew destructed at " << this << '\n'; }
  T t;
};

Noisy f() {
  Noisy v = Noisy(); // copy elision when initializing v
                     // from a temporary (until C++17) / prvalue (since C++17)
  return v; // NRVO from v to the result object (not guaranteed, even in C++17)
} // if optimization is disabled, the move constructor is called
auto foo1(Noisy arg) {
  std::cout << "&arg = " << &arg << '\n';
  return Wrapper<Noisy>(arg);
}

auto foo2(Noisy arg) {
  std::cout << "&arg = " << &arg << '\n';
  return WrapperNew<Noisy>(std::forward<Noisy>(arg));
}

int main() {
  {
    Noisy v = f();

    std::cout << "&v = " << &v << '\n';
  }
  std::cout << "==================\n";
  usleep(100);
  /*
constructed at 0x7fffe3c60720
&v = 0x7fffe3c60720
destructed at 0x7fffe3c60720
  */

  {

    Wrapper<Noisy> t = Wrapper<Noisy>(f());
    std::cout << "&t = " << &t << '\n';
    /*
constructed at 0x7fffe3c60738
copy-constructed
Wrapper constructed at 0x7fffe3c60718
destructed at 0x7fffe3c60738
&t = 0x7fffe3c60718
Wrapper destructed at 0x7fffe3c60718
destructed at 0x7fffe3c60718
    */
  }
  std::cout << "==================\n";
  usleep(100);
  {

    Wrapper<Noisy> t = foo1(f());
    std::cout << "&t = " << &t << '\n';
    /*
constructed at 0x7fffe3c60730
&arg = 0x7fffe3c60730
copy-constructed
copy-constructed
Wrapper constructed at 0x7fffe3c60718
destructed at 0x7fffe3c606f0
destructed at 0x7fffe3c60730
&t = 0x7fffe3c60718
Wrapper destructed at 0x7fffe3c60718
destructed at 0x7fffe3c60718
    */
  }
  std::cout << "==================\n";
  usleep(100);
  {
    WrapperNew<Noisy> t = foo2(f());
    std::cout << "&t = " << &t << '\n';
    /*
constructed at 0x7fffe3c60728
&arg = 0x7fffe3c60728
move-constructed
WrapperNew constructed at 0x7fffe3c60720
destructed at 0x7fffe3c60728
&t = 0x7fffe3c60720
WrapperNew destructed at 0x7fffe3c60720
destructed at 0x7fffe3c60720
    */
  }
  std::cout << "==================\n";
  usleep(100);
}