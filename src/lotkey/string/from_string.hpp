#pragma once

#include "lotkey/string/string.hpp"

#include <sstream>

namespace lk {
/// "Proxied" converter from string to some type using streams
/// Automatically deduces the type based on context
class from_string {
public:
  from_string() = delete;
  from_string(from_string const &) = delete;
  from_string(from_string &&) = delete;
  void operator=(from_string const &) = delete;
  void operator=(from_string &&) = delete;

  from_string(string const &str) : m_str{str} {}

  /// Implicit conversion
  template <class T> operator T() const;

private:
  string const &m_str;
};

template <class T> lk::from_string::operator T() const {
  T t;
  std::stringstream ss;
  ss << m_str;
  ss >> t;
  return t;
}
} // namespace lk