#pragma once

#include <algorithm>
#include <vector>

namespace lk {
template <class T, class Alloc = std::allocator<T>>
class vector : public std::vector<T, Alloc> {
public:
  auto find(T const &t) const {
    return std::find(this->begin(), this->end(), t);
  }

  template <class UnaryPredicate> auto find_if(UnaryPredicate p) const {
    return std::find_if(this->begin(), this->end(), p);
  }

  template <class UnaryPredicate> auto find_if_not(UnaryPredicate p) const {
    return std::find_if_not(this->begin(), this->end(), p);
  }

  bool contains(T const &t) const { return find(t) != this->end(); }

private:
};
} // namespace lk