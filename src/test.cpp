#include "lotkey/string/from_string.hpp"
#include "lotkey/string/string.hpp"

#include <iostream>
#include <sstream>

template <typename T> void compare(T const &t1, T const &t2);

int main() {
  std::stringstream ss;
  ss << 1 << "hehe";
  lk::string s;
  ss >> s;
  std::cout << s << std::endl;
}

template <typename T> void compare(T const &t1, T const &t2) {
  std::cout << t1 << " > " << t2 << " = " << (t1 > t2) << std::endl;
  std::cout << t1 << " < " << t2 << " = " << (t1 < t2) << std::endl;
  std::cout << t1 << " >= " << t2 << " = " << (t1 >= t2) << std::endl;
  std::cout << t1 << " <= " << t2 << " = " << (t1 <= t2) << std::endl;
  std::cout << t1 << " == " << t2 << " = " << (t1 == t2) << std::endl;
  std::cout << t1 << " != " << t2 << " = " << (t1 != t2) << std::endl;
}