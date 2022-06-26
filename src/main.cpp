#include "string.hpp"

#include <iostream>

template <typename T> void compare(T const &t1, T const &t2);

int main() {
  lk::string s1{"abc"};
  lk::string s2{s1};
  s1.pop_front();
  std::cout << s1 << std::endl;
  std::cout << s2 << std::endl;
}

template <typename T> void compare(T const &t1, T const &t2) {
  std::cout << t1 << " > " << t2 << " = " << (t1 > t2) << std::endl;
  std::cout << t1 << " < " << t2 << " = " << (t1 < t2) << std::endl;
  std::cout << t1 << " >= " << t2 << " = " << (t1 >= t2) << std::endl;
  std::cout << t1 << " <= " << t2 << " = " << (t1 <= t2) << std::endl;
  std::cout << t1 << " == " << t2 << " = " << (t1 == t2) << std::endl;
  std::cout << t1 << " != " << t2 << " = " << (t1 != t2) << std::endl;
}