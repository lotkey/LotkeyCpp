#include "lotkey/string/string.hpp"

namespace lk {
string::deref::deref(string &str, size_t index)
    : m_str{str}, m_index{index}, m_char{m_str.m_str[m_str.m_start + index]} {
  str.throw_if_out_of_bounds(index);
}

string::deref::operator char() const { return m_char; }

char &string::deref::operator=(char c) const {
  if (!m_str.is_sole_owner()) {
    m_str.copy_and_shrink();
  }
  return m_str.m_str[m_str.m_start + m_index] = c;
}
} // namespace lk