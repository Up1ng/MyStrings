# MyString - Copy-On-Write String Implementation

## Overview

MyString is a C++ string class that implements **copy-on-write (COW)** semantics for efficient memory management. This implementation provides reference-counted string objects that share memory until modification is required, optimizing performance for string copying and assignment operations.

## Features

- **Copy-on-Write Semantics**: Strings share memory until modified
- **Reference Counting**: Automatic memory management with reference tracking
- **Full String Operations**: Concatenation, comparison, indexing, and searching
- **Exception Safety**: Bounds checking with `std::out_of_range` exceptions
- **STL Compatibility**: Standard string interface patterns

## Class Interface

### Constructors
- `Mystring()` - Default constructor (empty string)
- `Mystring(const char *input)` - C-string constructor
- `Mystring(const Mystring &other)` - Copy constructor (increments reference count)

### Operators
- Assignment (`=`)
- Concatenation (`+`, `+=`)
- Comparison (`==`, `!=`, `<`, `>`, `<=`, `>=`)
- Indexing (`[]`) - both const and non-const versions

### Member Functions
- `Length()` - Get string length
- `Print()` - Output string to stdout
- `CountRef()` - Get reference count (for testing)
- `Clear()` - Clear string content
- `c_str()` - Get C-style string pointer
- `Find(char c)` - Find character position
- `Find(const Mystring& substr)` - Find substring position

## Key Implementation Details

### Copy-on-Write Mechanism
- Strings share internal buffers until modification
- `detach()` method creates unique copy when needed
- Reference counting tracks shared instances

### Memory Management
- Automatic deallocation when reference count reaches zero
- Safe self-assignment handling
- Proper null pointer handling in constructors

## Usage Example

```cpp
#include "MyString.hpp"

int main() {
    // Create strings with shared memory
    Mystring s1("Hello");
    Mystring s2 = s1;  // Shares buffer, refCount = 2
    
    // Modification triggers copy
    s2[0] = 'h';  // Now s1 and s2 have separate buffers
    
    // Concatenation
    Mystring s3 = s1 + " World";
    
    // Comparison
    if (s1 < s3) {
        // ...
    }
    
    return 0;
}
```

## Testing

The project includes comprehensive Google Tests covering:

- Basic construction and printing
- Copy semantics and reference counting
- All operator functionalities
- Copy-on-write behavior verification
- Edge cases (empty strings, self-assignment)
- String search operations

### Running Tests
```bash
g++ -std=c++11 MyString.cpp MyStringTests.cpp -lgtest -lgtest_main -pthread -o tests
./tests
```

## Performance Characteristics

- **Copy Operations**: O(1) time complexity (reference counting only)
- **Modification Operations**: O(n) time complexity (when copy required)
- **Memory Usage**: Efficient sharing reduces memory footprint for copied strings

## Notes

- The implementation follows RAII principles for resource management
- All methods provide strong exception safety guarantee
- The class is not thread-safe for concurrent modifications
- Designed for educational purposes to demonstrate COW semantics

## Files

- `MyString.hpp` - Class declaration and interface
- `MyString.cpp` - Implementation with COW semantics
- `MyStringTests.cpp` - Comprehensive test suite using Google Test
