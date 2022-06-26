#pragma once

#include <map>

namespace lk {
template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<std::pair<const Key, T>>>
class map : public std::map<Key, T, Compare, Alloc> {
public:
  bool contains(Key const &key) const { return this->find(key) != this->end(); }

private:
};
} // namespace lk