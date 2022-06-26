# LotkeyCpp
Lotkey C++ libraries

## lk::map

*Inherits from std::map*

---
```cpp
bool lk::map::contains(Key const& key) const;
```

### Parameters
`key`:
- Key to search for

### Returns
Whether the map contains a value for the provided key

## lk::string

*Reference-counting-based string implementation*

---
```cpp
lk::string::string();
```

Default constructor, string references the empty string.

---
```cpp
lk::string::string(char const c);
```

Constructs a string from a single character.

### Parameters
`c`:
- Character to construct a string with

---
```cpp
lk::string::string(char const *c_str);
```

Constructs a string from a C-string.

### Parameters
`c_str`:
- C-string to copy and create a string with

---
```cpp
lk::string::string(lk::string const &str);
```
Copy constructor.

### Parameters
`str`:
- string to copy a C-string substring reference from

---
```cpp
lk::string::string(lk::string &&str);
```
Move constructor.

### Parameters
`str`:
- string to move a C-string substring reference from

---
```cpp
lk::string::~string();
```
Removes a reference to the C-string, `delete[]`s the C-string if that was the only reference.

---
```cpp
lk::string &lk::string::operator=(lk::string const& str);
```
Copy assignment.

### Parameters
`str`:
- string to copy a C-string substring reference from

### Returns
A reference to the string for compound assignment

---
```cpp
lk::string &lk::string::operator=(lk::string &&str);
```
Move assignment.

### Parameters
`str`:
- string to move a C-string substring reference from

### Returns
A reference to the string for compound assignment

---
```cpp
size_t lk::string::length() const;
```

### Returns
The length of the C-style substring referenced.

---
```cpp
void lk::string::clear();
```
Removes a reference to the C-style string and references the empty string.

---
```cpp
bool lk::string::empty() const;
```

### Returns
Whether the string references the empty string.

---
```cpp
lk::string::deref const lk::string::operator[](size_t index);
lk::string::deref const lk::string::at(size_t index);
```

### Returns
A getter/setter of the string at `index`. If the user uses the getter/setter as a setter and the string is not the sole owner of its C-string, it will create a new C-string that it is the sole owner of and then set it.

Getter example:
```cpp
lk::string s{"test"};
char c;
c = s[0]; // Get
c = s.at(0); // Get
```

Setter example:
```cpp
lk::string s{"test"};
s[0] = 'c'; // Set
s.at(0) = 'c'; // Set
```

---
```cpp
char lk::string::operator[](size_t index) const;
char lk::string::at(size_t index) const;
```

### Parameters
`index`:
- Index of the character to return

### Returns
The character at `index`

---
```cpp
lk::string::deref const lk::string::back();
```

### Returns
A getter/setter of the last character in the C-style substring reference. If the user uses the getter/setter as a setter and the string is not the sole owner of its C-string, it will create a new C-string that it is the sole owner of and then set it.

---
```cpp
char const lk::string::back() const;
```

### Returns
The last character in the C-style substring reference

---
```cpp
lk::string::deref const lk::string::front();
```

### Returns
A getter/setter of the first character in the C-style substring reference. If the user uses the getter/setter as a setter and the string is not the sole owner of its C-string, it will create a new C-string that it is the sole owner of and then set it.

---
```cpp
char const lk::string::back() const;
```

### Returns
The first character in the C-style substring reference

---
```cpp
lk::string &lk::string::operator+=(lk::string const &str);
```
Appends `str` to the end of the string.

### Parameters
`str`:
- string to append

### Returns
A reference to the string for compound assignment

---
```cpp
lk::string &lk::string::push_back(char const c);
```
Appends `c` to the end of the string.

### Parameters
`c`:
- `char` to append

### Returns
A reference to the string for compound statements

---
```cpp
lk::string &lk::string::pop_back();
```
Shortens the C-style substring reference by one character. If the string is the sole owner of the C-string, then it replaces the popped character with the null character.

An example with sole-ownership:
```cpp
lk::string s{"test"};
s.pop_back();
```

The C-style substring reference before:
```
t e s t \0
^     ^
|     |
|     Reference to beginning of substring + length of substring
Reference to beginning of substring
```

The C-style substring reference after:
```
t e s \0 \0
^   ^
|   |
|   Reference to beginning of substring + length of substring
Reference to beginning of substring
```

An example without sole-ownership:
```cpp
lk::string s1{"test"};
lk::string s2{s1};
s1.pop_back();
```

`s1`'s and `s2`'s C-style substring reference before:
```
t e s t \0
^     ^
|     |
|     Reference to beginning of substring + length of substring
Reference to beginning of substring
```

`s1`'s C-style substring reference after:
```
t e s t \0
^   ^
|   |
|   Reference to beginning of substring + length of substring
Reference to beginning of substring
```

`s2`'s C-style substring reference is unchanged.

### Returns
A reference to the string for compound statements

---
```cpp
lk::string &lk::string::pop_front();
```
Pops the front character of the string by incrementing the reference to the beginning of the C-style substring.

### Returns
A reference to the string for compound statements

---
```cpp
lk::string &lk::string::insert(size_t pos, string const &str);
```
Inserts `str` at the `pos` index.

### Parameters
`pos`:
- Index to insert `str` at

`str`:
- String to insert at `pos`

### Returns
A reference to the string for compound statements

---
```cpp
char const *lk::string::c_str();
```

### Returns
The C-string being used by the string. This function is not `const` for the following scenario:

```cpp
lk::string s1{"test"};
lk::string s2{s1}; // Copies the reference to the C-string from s1
s2.pop_back(); // Shortens the substring reference by 1 char for s2, but cannot change the last character to '\0' because the string is referenced by s1 as well
std::cout << s2.c_str() << std::endl; // Would print "test" instead of "tes" if a new string was not created with the null terminator in the right position
```

---
```cpp
[[nodiscard]] char *lk::string::make_c_str() const;
```
Creates a C-style string that contains the contents of the substring referenced and null-terminated. It is marked `[[nodiscard]]` because the user is responsible for freeing the memory! Use `delete[]`.

Example:
```cpp
lk::string s{"test"};
char *c_str = s.make_c_str();
// Do something other than freeing the memory...
delete[] c_str; // Free the memory
c_str = nullptr;
```