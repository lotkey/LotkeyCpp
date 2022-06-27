#pragma once

#include "lotkey/string/string.hpp"

#include <sstream>

namespace lk {
/// Converts t to a lk::string using streams
/// operator<< must be defined for class T
template <class T> string to_string(T const &t);

template <class T> string to_string(T const &t) {
  string str;
  std::stringstream ss;
  ss << t;
  ss >> str;
  return str;
}
} // namespace lk