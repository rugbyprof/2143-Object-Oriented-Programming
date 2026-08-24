## Quick Intro To Vectors and Maps

### STL Vectors (std::vector)

#### Purpose:

`std::vector` is a dynamic array in C++ that automatically resizes as elements are added or removed. Unlike arrays, vectors can grow or shrink in size during runtime. They are part of the C++ Standard Template Library (STL) and are widely used because of their flexibility and ease of use.

#### Key Features:

1. **Dynamic Resizing**: The vector can automatically resize itself as elements are added or removed. This removes the need to manage memory manually.
2. **Random Access**: Like arrays, vectors allow constant-time random access to elements using the `[]` operator or `at()`.
3. **Efficient Insertion and Deletion**: Insertion and deletion at the end of the vector are efficient (`O(1)`), but at other positions, it could take `O(n)` due to shifting elements.

#### Basic Syntax:

```cpp
#include <vector>

std::vector<int> myVector;  // Create an empty vector of integers
myVector.push_back(10);     // Add an element
int value = myVector[0];    // Access an element at index 0
```

#### Traversal:

You can traverse a vector using:

1. **Index-based loop**:

   ```cpp
   for (size_t i = 0; i < myVector.size(); ++i) {
       std::cout << myVector[i] << " ";
   }
   ```

2. **Range-based for loop** (C++11 onwards):

   ```cpp
   for (const auto& val : myVector) {
       std::cout << val << " ";
   }
   ```

3. **Iterator**:
   ```cpp
   for (auto it = myVector.begin(); it != myVector.end(); ++it) {
       std::cout << *it << " ";
   }
   ```

### STL Maps (std::map)

#### Purpose:

`std::map` is an associative container that stores elements in key-value pairs. It automatically sorts elements based on the key and ensures that each key is unique. It provides fast lookups, insertions, and deletions based on the key using binary search trees (usually implemented as red-black trees).

#### Key Features:

1. **Key-Value Pairs**: Maps store elements as pairs, where each element is a key associated with a value.
2. **Sorted Keys**: The keys are sorted automatically, usually in ascending order.
3. **Efficient Lookup**: Maps provide logarithmic time complexity (`O(log n)`) for insertions, deletions, and lookups.

#### Basic Syntax:

```cpp
#include <map>

std::map<int, std::string> myMap;
myMap[1] = "Apple";     // Insert a key-value pair
myMap[2] = "Banana";    // Insert another key-value pair
std::string fruit = myMap[1];  // Access value by key (returns "Apple")
```

#### Traversal:

You can traverse a map using:

1. **Range-based for loop** (C++11 onwards):

   ```cpp
   for (const auto& pair : myMap) {
       std::cout << pair.first << ": " << pair.second << std::endl;
   }
   ```

2. **Iterator**:
   ```cpp
   for (auto it = myMap.begin(); it != myMap.end(); ++it) {
       std::cout << it->first << ": " << it->second << std::endl;
   }
   ```

### Key Differences:

- **Vectors** are indexed by integer positions and provide **random access** to elements, while **maps** are accessed via **keys** and provide **logarithmic access** based on the key.
- **Vectors** store elements in the order they are inserted, while **maps** store elements sorted by their keys.

Both containers are fundamental to C++ programming, providing efficient ways to store and manage collections of data.
