#include "string.hpp"

#include <memory>

namespace lk {
map<char *, size_t> string::s_ref_counts;

string::string() : m_str{empty_str()}, m_len{0}, m_start{0} {}

string::string(char const c) : m_str{add_reference(2)}, m_len{1}, m_start{0} {
  m_str[0] = c;
  m_str[1] = '\0';
}

string::string(char const *c_str) : m_len{strlen(c_str)}, m_start{0} {
  m_str = add_copy_reference(c_str);
}

string::string(string const &str) : m_len{str.m_len}, m_start{str.m_start} {
  m_str = add_reference(str.m_str);
}

string::string(string &&str)
    : m_str{str.m_str}, m_len{str.m_len}, m_start{str.m_start} {
  str.m_str = nullptr;
  str.m_len = 0;
  str.m_start = 0;
}

string::string(char *str, size_t size, size_t substr_start, size_t substr_size)
    : m_str{str}, m_len{size}, m_start{substr_start} {
  m_str = add_reference(str);
}

string::~string() { clear(); }

string &string::operator=(string const &str) {
  m_str = add_reference(str.m_str);
  m_len = str.m_len;
  m_start = str.m_start;
  return *this;
}

string &string::operator=(string &&str) {
  m_str = str.m_str;
  m_len = str.m_len;
  m_start = str.m_start;
  str.m_str = nullptr;
  str.m_len = 0;
  str.m_start = 0;
  return *this;
}

size_t string::length() const { return m_len; }

void string::clear() {
  remove_reference(m_str);
  m_len = 0;
  m_str = empty_str();
  m_start = 0;
}

bool string::empty() const { return m_len == 0; }

string::deref const string::operator[](size_t index) { return at(index); }

char string::operator[](size_t index) const { return at(index); }

string::deref const string::at(size_t index) { return deref{*this, index}; }

char string::at(size_t index) const {
  throw_if_out_of_bounds(index);
  return m_str[m_start + index];
}

string::deref const string::back() { return at(m_len - 1); }

char string::back() const { return at(m_len - 1); }

string::deref const string::front() { return at(0); }

char string::front() const { return at(0); }

string &string::operator+=(string const &str) {
  size_t new_size = m_len + str.m_len;
  auto *tmp = m_str;
  m_str = add_reference(new_size + 1);
  memcpy(m_str, tmp + m_start, m_len);
  memcpy(m_str + m_len, str.m_str + str.m_start, str.m_len);
  m_str[new_size] = '\0';
  remove_reference(tmp);
  m_len = new_size;
  m_start = 0;
  return *this;
}

string &string::push_back(char c) {
  auto *tmp = m_str;
  m_len++;
  m_str = add_reference(m_len + 1);
  memcpy(m_str, tmp + m_start, m_len - 1);
  remove_reference(tmp);
  m_str[m_len - 1] = c;
  m_str[m_len] = '\0';
  return *this;
}

string &string::pop_back() {
  if (is_sole_owner()) {
    m_str[m_start + m_len - 1] = '\0';
  }
  m_len--;
  return *this;
}

string &string::pop_front() {
  m_len--;
  m_start++;
  return *this;
}

string &string::insert(size_t pos, string const &str) {
  size_t new_len = m_len + str.m_len;
  char *new_str = new char[new_len + 1];
  memcpy(new_str, m_str + m_start, m_len);
  memcpy(new_str, str.m_str + str.m_start, str.m_len);
  new_str[new_len] = '\0';
  remove_reference(m_str);
  m_str = new_str;
  m_len = new_len;
  m_start = 0;
  return *this;
}

char const *string::c_str() {
  if (m_str[m_start + m_len] != '\0') {
    copy_and_shrink();
  }
  return m_str;
}

char *string::make_c_str() const {
  char *c_str = new char[m_len + 1];
  memcpy(c_str, m_str + m_start, m_len);
  c_str[m_len] = '\0';
  return c_str;
}

string string::substring(size_t start) const {
  throw_if_out_of_bounds(start);
  return string(m_str, m_len, m_start + start, m_len - start);
}

string string::substring(size_t start, size_t len) const {
  throw_if_out_of_bounds(start);
  throw_if_out_of_bounds(start + len);
  return string(m_str, m_len, m_start + start, len);
}

size_t string::find_first_of(char c) const {
  for (size_t i = 0; i < m_len; i++) {
    if (at(i) == c) {
      return i;
    }
  }
  return npos;
}

size_t string::find_last_of(char c) const {
  for (size_t i = m_len - 1; i >= 0 && i != npos; i--) {
    if (at(i) == c) {
      return i;
    }
  }
  return npos;
}

size_t string::find_first_not_of(char c) const {
  for (size_t i = 0; i < m_len; i++) {
    if (at(i) != c) {
      return i;
    }
  }
  return npos;
}

size_t string::find_last_not_of(char c) const {
  for (size_t i = m_len - 1; i >= 0 && i != npos; i--) {
    if (at(i) != c) {
      return i;
    }
  }
  return npos;
}

string string::operator+(string const &str) const {
  string new_str{*this};
  new_str += str;
  return new_str;
}

bool string::operator>(string const &str) const {
  for (size_t i = 0; i < m_len && i < str.m_len; i++) {
    if (at(i) != str.at(i)) {
      return at(i) > str.at(i);
    }
  }
  return m_len < str.m_len;
}

bool string::operator<(string const &str) const {
  for (size_t i = 0; i < m_len && i < str.m_len; i++) {
    if (at(i) != str.at(i)) {
      return at(i) < str.at(i);
    }
  }
  return m_len > str.m_len;
}

bool string::operator>=(string const &str) const {
  for (size_t i = 0; i < m_len && i < str.m_len; i++) {
    if (at(i) != str.at(i)) {
      return at(i) > str.at(i);
    }
  }
  return m_len <= str.m_len;
}

bool string::operator<=(string const &str) const {
  for (size_t i = 0; i < m_len && i < str.m_len; i++) {
    if (at(i) != str.at(i)) {
      return at(i) < str.at(i);
    }
  }
  return m_len >= str.m_len;
}

bool string::operator==(string const &str) const {
  if (m_len != str.m_len) {
    return false;
  }
  for (size_t i = 0; i < m_len; i++) {
    if (at(i) != str.at(i)) {
      return false;
    }
  }
  return true;
}

bool string::operator!=(string const &str) const { return !(*this == str); }

bool string::is_sole_owner() const { return s_ref_counts[m_str] == 1; }

void string::throw_if_out_of_bounds(size_t index) const {
  if (index > m_len - m_start) {
    throw std::runtime_error("String index(" + std::to_string(index) +
                             ") out of bounds[0-" +
                             std::to_string(m_len - m_start - 1) + "].");
  }
}

void string::copy_and_shrink() {
  char *new_str = new char[m_len + 1];
  memcpy(new_str, m_str + m_start, m_len);
  new_str[m_len] = '\0';
  remove_reference(m_str);
  m_str = new_str;
  m_start = 0;
}

char *string::add_copy_reference(char const *c_str) {
  if (c_str == nullptr) {
    return nullptr;
  }
  size_t len = strlen(c_str);
  char *new_str = new char[len + 1];
  memcpy(new_str, c_str, len);
  new_str[len] = '\0';
  s_ref_counts[new_str] = 1;
  return new_str;
}

char *string::add_reference(char *c_str) {
  if (c_str == nullptr) {
    return nullptr;
  }
  s_ref_counts.insert({c_str, 0});
  s_ref_counts[c_str]++;
  return c_str;
}

char *string::empty_str() {
  std::unique_ptr<char> empty_str{std::make_unique<char>()};
  if (!empty_str) {
    *empty_str = '\0';
  }
  return empty_str.get();
}

char *string::add_reference(size_t size) {
  char *str = new char[size];
  return add_reference(str);
}

void string::remove_reference(char *c_str) {
  if (c_str == nullptr) {
    return;
  }
  s_ref_counts[c_str]--;
  if (s_ref_counts.at(c_str) == 0) {
    delete[] c_str;
    s_ref_counts.erase(c_str);
  }
}
} // namespace lk

std::istream &operator>>(std::istream &is, lk::string &str) {
  char c;
  is >> c;
  while (c != '\0') {
    str += c;
    is >> c;
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, lk::string const &str) {
  for (size_t i = 0; i < str.length(); i++) {
    os << str[i];
  }
  os << '\0';
  return os;
}