#pragma once

#include <algorithm>
#include <vector>

namespace lk {
template <class T, class Alloc = std::allocator<T>>
class vector : public std::vector<T, Alloc> {
public:
  auto const find(T const &t) const {
    return std::find(this->begin(), this->end(), t);
  }
  bool contains(T const &t) const { return find(t) != this->end(); }

private:
};
} // namespace lk