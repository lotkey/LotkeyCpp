#pragma once

#include "lotkey/map/map.hpp"

#include <cstring>
#include <sstream>
#include <string>

namespace lk {
class string {
  friend class deref;

public:
  /// "Proxied" getter/setter
  class deref {
    friend class string;

  public:
    deref() = delete;
    deref(deref const &) = delete;
    deref(deref &&) = delete;
    void operator=(deref const &) = delete;
    void operator=(deref &&) = delete;
    /// Implicit getter
    operator char() const;
    /// Setter
    char &operator=(char c) const;

  private:
    string &m_str;
    size_t m_index;
    char m_char;

    deref(string &str, size_t index);
  };

  /// Default constructor, initializes to ""
  string();
  string(char c);
  string(int i);
  string(long l);
  string(long long ll);
  string(unsigned u);
  string(unsigned long ul);
  string(unsigned long long ull);
  string(float f);
  string(double d);
  string(long double ld);
  string(std::string const &);
  /// Copy-construct from c-string
  string(char const *c_str);
  /// Copy reference from string
  string(string const &str);
  /// Move reference from string
  string(string &&str);
  /// Remove reference to string
  ~string();
  /// Assign reference from string
  string &operator=(string const &str);
  /// Move reference from string
  string &operator=(string &&str);

  size_t length() const;
  void clear();
  /// @returns True if the string is empty, false otherwise
  bool empty() const;

  /// @param index Index of char to get/set
  /// @returns Getter/setter at the index
  deref const operator[](size_t index);
  /// @param index Index of char to get
  /// @returns char at the index
  char operator[](size_t index) const;
  /// @param index Index of char to get/set
  /// @returns Getter/setter at the index
  deref const at(size_t index);
  /// @param index Index of char to get
  /// @returns char at the index
  char at(size_t index) const;
  /// @returns Getter/setter of the last char
  deref const back();
  /// @returns The last char of the string
  char back() const;
  /// @returns Getter/setter of the first char
  deref const front();
  /// @returns The first char of the string
  char front() const;

  /// Appends string to the end of the string
  string &operator+=(string const &str);
  /// Appends a character to the end of the string
  string &push_back(string const &str);
  /// Removes the last character in the string
  string &pop_back();
  /// Removes the first character in the string
  string &pop_front();
  /// Inserts a string into the position
  string &insert(size_t pos, string const &str);

  /// Returns the address of the c-string used by the string.
  /// This may require creating a c-string if the c-string referenced by the
  /// string is owned by another string.
  char const *c_str();
  std::string std_str() const;
  /// Returns a NEW c-string with the contents of the string.
  /// YOU MUST CALL `delete[]` ON THE RETURNED C-STRING TO FREE THE MEMORY.
  [[nodiscard]] char *make_c_str() const;
  /// Returns a substring of the string, starting at `start`
  string substring(size_t start) const;
  /// Returns a substring of the string, starting at `start` and spanning `len`
  /// characters
  string substring(size_t start, size_t len) const;
  size_t find_first_of(char c) const;
  size_t find_last_of(char c) const;
  size_t find_first_not_of(char c) const;
  size_t find_last_not_of(char c) const;

  /// Returns a concatenated string
  string operator+(string const &str) const;
  bool operator>(string const &str) const;
  bool operator<(string const &str) const;
  bool operator>=(string const &str) const;
  bool operator<=(string const &str) const;
  bool operator==(string const &str) const;
  bool operator!=(string const &str) const;

  static constexpr size_t npos{(size_t)-1};

private:
  static map<char *, size_t> s_ref_counts;

  char *m_str = nullptr;
  size_t m_len = 0;
  size_t m_start = 0;

  [[nodiscard]] static char *add_copy_reference(char const *c_str);
  [[nodiscard]] static char *add_reference(char *c_str);
  [[nodiscard]] static char *add_reference(size_t size);
  static char *empty_str();
  static void remove_reference(char *c_str);

  string(char *str, size_t size, size_t substr_start, size_t substr_size);
  bool is_sole_owner() const;
  void throw_if_out_of_bounds(size_t index) const;
  void copy_and_shrink();
  template <class T> void stream_and_copy(T const &t);
};

template <class T> void string::stream_and_copy(T const &t) {
  clear();
  std::stringstream ss;
  ss << t;
  m_len = strlen(ss.str().c_str());
  m_str = add_copy_reference(ss.str().c_str());
  m_start = 0;
}
} // namespace lk

std::istream &operator>>(std::istream &is, lk::string &str);
std::ostream &operator<<(std::ostream &is, lk::string const &str);