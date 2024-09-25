## Maps - Introduction and Overview

### Introduction to Maps

`std::map` is an associative container in C++ that stores elements as **key-value pairs**. It allows you to efficiently retrieve values by their associated keys. Each key in the map is unique, and the elements are stored in **sorted order** based on the key. Internally, the map is implemented as a **red-black tree**, providing **logarithmic time complexity** (`O(log n)`) for insertion, lookup, and deletion.

### Example Code Files

    - **COMING SOON**

### Methods and Features of Maps

Below is an overview of commonly used methods and features available in `std::map`.

---

### Capacity Methods

These methods deal with checking the size and capacity of the map.

| **Name**     | **Description**                                                 |
| ------------ | --------------------------------------------------------------- |
| `size()`     | Returns the number of key-value pairs currently in the map.     |
| `max_size()` | Returns the maximum number of elements the map can hold.        |
| `empty()`    | Returns whether the map is empty (`true` if no elements exist). |

---

### Element Access Methods

These methods allow you to access the elements in the map.

| **Name**     | **Description**                                                               |
| ------------ | ----------------------------------------------------------------------------- |
| `operator[]` | Accesses or inserts an element based on a key (e.g., `myMap[key]`).           |
| `at(key)`    | Accesses the value associated with a key, throwing an exception if not found. |
| `find(key)`  | Returns an iterator to the element matching the key, or `end()` if not found. |

---

### Iterator Methods

These methods return iterators, allowing you to traverse the map.

| **Name**    | **Description**                                                       |
| ----------- | --------------------------------------------------------------------- |
| `begin()`   | Returns an iterator to the first element in the map (smallest key).   |
| `end()`     | Returns an iterator to the position after the last element.           |
| `rbegin()`  | Returns a reverse iterator to the last element (largest key).         |
| `rend()`    | Returns a reverse iterator to the position before the first element.  |
| `cbegin()`  | Returns a constant iterator to the first element (C++11 and newer).   |
| `cend()`    | Returns a constant iterator to the position after the last element.   |
| `crbegin()` | Returns a constant reverse iterator to the last element.              |
| `crend()`   | Returns a constant reverse iterator to the position before the first. |

---

### Modifiers

These methods allow you to insert, erase, or manipulate elements within the map.

| **Name**              | **Description**                                                              |
| --------------------- | ---------------------------------------------------------------------------- |
| `insert(pair)`        | Inserts a key-value pair into the map.                                       |
| `erase(key)`          | Removes the element with the specified key.                                  |
| `swap(map2)`          | Swaps the contents of the current map with another map of the same type.     |
| `clear()`             | Removes all elements from the map.                                           |
| `emplace(key, value)` | Inserts a new key-value pair into the map in place, without copying objects. |

---

### Operations

These methods provide additional map operations.

| **Name**           | **Description**                                                                  |
| ------------------ | -------------------------------------------------------------------------------- |
| `count(key)`       | Returns the number of elements with the specified key (always 0 or 1 for `map`). |
| `lower_bound(key)` | Returns an iterator to the first element not less than the given key.            |
| `upper_bound(key)` | Returns an iterator to the first element greater than the given key.             |
| `equal_range(key)` | Returns a pair of iterators defining the range of elements matching the key.     |

---

### Usage Examples

Here are some basic usage examples to illustrate the concepts:

1. **Basic Insertion and Access**:

   ```cpp
   std::map<int, std::string> myMap;
   myMap[1] = "Apple";
   myMap[2] = "Banana";

   std::cout << myMap[1];  // Outputs: Apple
   ```

2. **Traversing a Map with an Iterator**:

   ```cpp
   for (auto it = myMap.begin(); it != myMap.end(); ++it) {
       std::cout << it->first << ": " << it->second << std::endl;
   }
   ```

3. **Checking for a Key**:

   ```cpp
   if (myMap.find(1) != myMap.end()) {
       std::cout << "Key 1 exists in the map." << std::endl;
   }
   ```

4. **Erasing an Element**:
   ```cpp
   myMap.erase(2);  // Removes the key-value pair with key 2
   ```

---

This document provides a concise reference to `std::map` methods and functionality. Use it as a guide for managing associative key-value data in your C++ projects.
