```yaml
title: Comprehensive Overview of C++ Templates
author: ChatGPT 🚀 (Edited by Griffin)
date: 2024-11-24
tags:
  - C++
  - Templates
  - STL
  - Generic Programming
  - Advanced C++
description: A detailed guide to C++ templates starting with STL usage (vectors, maps, pairs) and progressing to custom templated types, explaining key concepts and practical applications.
```

## Templates in C++

Here’s a comprehensive overview of templates in C++ starting with their use in the STL (Standard Template Library) and progressing to creating custom templated types. This will include some practical examples, common patterns, and key concepts.

### 1. What Are Templates?

Templates enable generic programming by allowing functions and classes to operate with generic types, eliminating redundancy and enhancing reusability.

There are two main types:

- Function Templates: For generic functions.
- Class Templates: For generic classes or structs.

### 2. Using Templates in the STL

The STL is heavily based on templates, providing generic containers, algorithms, and iterators. Here’s an overview of common STL components:

#### 2.1 Vectors

A `std::vector` is a dynamic array that can hold elements of any type.

- **Example:** Basic Usage

```cpp
#include <vector>
#include <iostream>

int main() {
std::vector<int> numbers = {1, 2, 3, 4, 5};
numbers.push_back(6); // Add an element

    for (int num : numbers) {
        std::cout << num << " ";
    }
    return 0;

}
```

- **Output:**

```bash
1 2 3 4 5 6
```

#### 2.2 Vectors of Vectors

A `std::vector<std::vector<T>>` can be used to represent a 2D grid or matrix.

- **Example:** 2D Grid

```cpp
#include <vector>
#include <iostream>

int main() {
std::vector<std::vector<int>> grid(3, std::vector<int>(4, 0)); // 3x4 grid initialized to 0

    grid[1][2] = 7;  // Modify an element

    for (const auto& row : grid) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    return 0;

}
```

- **Output:**

```bash
0 0 0 0
0 0 7 0
0 0 0 0
```

#### 2.3 Maps

A `std::map` stores key-value pairs, automatically sorted by the key.

- **Example:** Dictionary-Like Behavior

```cpp
#include <map>
#include <iostream>

int main() {
std::map<std::string, int> wordCount;
wordCount["hello"] = 5;
wordCount["world"] = 10;

    for (const auto& [key, value] : wordCount) {
        std::cout << key << ": " << value << std::endl;
    }
    return 0;

}
```

- **Output:**

```sh
hello: 5
world: 10
```

#### 2.4 Pairs

A `std::pair` holds two values of potentially different types.

- **Example:**Using Pairs

```cpp
#include <iostream>
#include <utility>

int main() {
std::pair<std::string, int> student("Alice", 90);

    std::cout << "Name: " << student.first << ", Score: " << student.second << std::endl;

    return 0;

}
```

- **Output:**

```sh
Name: Alice, Score: 90
```

#### 2.5 Combining STL Components

- **Example:**Vector of Pairs

```cpp
#include <vector>
#include <iostream>
#include <utility>

int main() {
    std::vector<std::pair<std::string, int>> students = {
        {"Alice", 90},
        {"Bob", 85},
        {"Charlie", 95}
    };

    for (const auto& student : students) {
        std::cout << "Name: " << student.first << ", Score: " << student.second << std::endl;
    }

    return 0;

}
```

- **Output:**

```sh
Name: Alice, Score: 90
Name: Bob, Score: 85
Name: Charlie, Score: 95
```

### 3. Creating Custom Templated Types

#### 3.1 Function Templates

Function templates allow you to define a generic function.

- **Example:**A Generic Max Function

```cpp
#include <iostream>

template <typename T>
T myMax(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << "Max of 3 and 7: " << myMax(3, 7) << std::endl;
    std::cout << "Max of 3.5 and 2.1: " << myMax(3.5, 2.1) << std::endl;
    return 0;
}
```

- **Output:**

```sh
Max of 3 and 7: 7
Max of 3.5 and 2.1: 3.5
```

#### 3.2 Class Templates

Class templates generalize class definitions for multiple data types.

- **Example:**A Generic Stack

```cpp
#include <iostream>
#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& value) {
        elements.push_back(value);
    }

    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }

    T top() const {
        if (!elements.empty()) {
            return elements.back();
        }
        throw std::runtime_error("Stack is empty");
    }

    bool empty() const {
        return elements.empty();
    }

};

int main() {
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    std::cout << "Top: " << intStack.top() << std::endl;
    intStack.pop();
    std::cout << "Top after pop: " << intStack.top() << std::endl;

    Stack<std::string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    std::cout << "Top of string stack: " << stringStack.top() << std::endl;

    return 0;

}
```

- **Output:**

```sh
Top: 20
Top after pop: 10
Top of string stack: World
```

#### 3.3 Template Specialization

Sometimes you need specific behavior for certain types.

- **Example:** Specialized Behavior for` std::string`

```cpp
#include <iostream>
#include <string>

template <typename T>
class Printer {
public:
    void print(const T& value) {
        std::cout << "Generic: " << value << std::endl;
    }
};

// Specialization for std::string
template <>
class Printer<std::string> {
public:
    void print(const std::string& value) {
        std::cout << "String: " << value << std::endl;
    }
};

int main() {
    Printer<int> intPrinter;
    intPrinter.print(42);

    Printer<std::string> stringPrinter;
    stringPrinter.print("Hello, World!");

    return 0;

}
```

- **Output:**

```sh
Generic: 42
String: Hello, World!
```

### 4. Key Concepts in Templates

- Type Deduction: C++ can deduce the template type from function arguments.
- Non-Type Template Parameters: Templates can take non-type parameters (e.g., integers).

```cpp
template <typename T, int size>
class Array {
    T data[size];
};
```

#### Template Metaprogramming:

- Advanced use of templates for compile-time computation.

### 5. Practical Advice

- Use templates to reduce code duplication for operations that differ only by type.
- Leverage STL containers and algorithms to simplify your code.
- Be cautious with template specialization to avoid overly complex designs.
