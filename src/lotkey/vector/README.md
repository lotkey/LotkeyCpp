# lk::vector
*Inherits from std::vector.*
```cpp
#include "lotkey/vector/vector.hpp"
```

---
```cpp
std::vector::iterator lk::vector::find(T const& t) const;
```
Searches for an element equal to `t`.

## Parameters
`t`:
- The value to search for

## Returns
An iterator to the element, or `std::string::end()` if not found.

---
```cpp
std::vector::iterator lk::vector::find_if(UnaryPredicate p) const;
```
Searches for an element for which `p({element})` returns `true`.

## Parameters
`p`:
- Predicate to search with

## Returns
An iterator to the element, or `std::string::end()` if not found.

---
```cpp
std::vector::iterator lk::vector::find_if_not(T const& t, UnaryPredicate p) const;
```
Searches for an element for which `p({element})` returns `false`.

## Parameters
`p`:
- Predicate to search with

## Returns
An iterator to the element, or `std::string::end()` if not found.