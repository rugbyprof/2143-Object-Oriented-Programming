```yaml
title: "C++ Templates Overview"
description: "A conceptual and practical guide to C++ templates"
tags: ["C++", "templates", "generics", "programming", "OOP"]
difficulty: "Intermediate"
```

## What Are Templates?

Templates are **blueprints** for creating classes or functions that can work with any type. Instead of writing separate functions/classes for `int`, `double`, `std::string`, etc., you write one **template** that the compiler uses to generate the specific version when needed.

Think of templates as:

- **Generics (in Java/C#)** but more powerful (and occasionally more cryptic).
- A **"mad scientist factory"**—the compiler churns out actual functions/classes on demand.

---

## Function Templates

A **function template** allows you to write a single function that works with many types.

```cpp
#include <iostream>
using namespace std;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    cout << add(3, 4) << endl;        // int version
    cout << add(3.5, 4.5) << endl;    // double version
    cout << add(string("Hi "), string("There")) << endl; // string version
}
```

The compiler **instantiates** a new version each time you call it with a new type.

---

## Class Templates

You can also use templates for classes, like building your own generic containers (before STL existed).

```cpp
#include <iostream>
using namespace std;

template <typename T>
class Box {
private:
    T value;
public:
    Box(T v) : value(v) {}
    T getValue() { return value; }
};

int main() {
    Box<int> intBox(42);
    Box<string> strBox("Hello");

    cout << intBox.getValue() << endl;
    cout << strBox.getValue() << endl;
}
```

This lets you avoid rewriting `BoxForInt`, `BoxForString`, etc.

---

## Multiple Parameters

Templates can take more than one type:

```cpp
template <typename T1, typename T2>
auto multiply(T1 a, T2 b) {
    return a * b;
}
```

Here, `auto` deduces the return type (C++11+).

---

## Non-Type Template Parameters

You can also pass **constants** as template parameters. This is super common in things like arrays.

```cpp
template <typename T, int SIZE>
class FixedArray {
    T data[SIZE];
public:
    int getSize() const { return SIZE; }
};
```

Usage:

```cpp
FixedArray<int, 10> arr;
cout << arr.getSize();  // prints 10
```

---

## Specialization

Sometimes you want a **general template**, but also a special case.

```cpp
template <typename T>
class Printer {
public:
    void print(T value) {
        cout << value << endl;
    }
};

// Specialization for bool
template <>
class Printer<bool> {
public:
    void print(bool value) {
        cout << (value ? "true" : "false") << endl;
    }
};
```

---

## Template Meta-Programming (TMP)

This is where things get _weird but powerful_. Templates can be used for compile-time calculations (pre-`constexpr`). For example:

```cpp
template <int N>
struct Factorial {
    static const int value = N * Factorial<N-1>::value;
};

template <>
struct Factorial<0> {
    static const int value = 1;
};

int main() {
    cout << Factorial<5>::value;  // 120
}
```

This runs **at compile time**. Yes, C++ lets you program your compiler. Nerd level: unlocked.

---

## Modern Enhancements

- **Type Deduction (`auto`, `decltype`)** simplifies template hell.
- **Concepts (C++20)** let you constrain templates for better error messages and safety.

```cpp
#include <concepts>

template <std::integral T>
T square(T x) {
    return x * x;
}
```

---

## TL;DR

- **Function templates** = write once, use with any type.
- **Class templates** = generic data structures.
- **Specialization** = override behavior for certain types.
- **Non-type params** = pass constants like array sizes.
- **TMP** = dark wizardry, compile-time computation.
- **Concepts (C++20)** = sanity checks for template users.

# 🚀 Real World Template Example

👉 Goal: _“Oh wow, one function works for all!”_

A swap function is pretty common for any sorting routine. If we want to sort integers, or strings, we need functions to match the type of data we are sorting:

```cpp
// swap integers
void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// swap strings
void swapValues(string &a, string &b) {
    int temp = a;
    a = b;
    b = temp;
}

.
.
.
// other swap functions with different data types
```

## One Function to Swap

- **Problem:** Write `swap` for `int`, `double`, `string`.
- **Solution:** Write a function template to sort many data types.
- **Examples:**

  ```cpp

  template <typename T>
  void swapValues(T &a, T &b) {
      T temp = a;
      a = b;
      b = temp;
  }
  ```

- **Exercises:**
  - Make a `min` and `max` function using templates.

---

## **Class Templates (Containers Lite)**

This is a bit of a weak example, but let's focus on the syntax.

- **Problem:** You need a `Box` for `int`, `Box` for `double`, `Box` for `string`.
- **Solution:** Use **class templates**.
- **Examples:**
  ```cpp
  template <typename T>
  class Box {
      T value;
  public:
      Box(T v) : value(v) {}
      T get() { return value; }
  };
  ```
- **Exercises:**
  - Make a `Box<int>` and `Box<std::string>`.
  - Write a `Pair<T1,T2>` class (like `std::pair`).

👉 You shoud see the relationship with **STL containers**. We will discuss this some more, but remember that my goals are to create data types that act like they are built in with the language. This is another step to make that happen.

---

## **STL in Action**

- **Show the magic:** `std::vector<int>`, `std::vector<std::string>`.
- STL containers are just **class templates** behind the scenes.
- Demo: sorting with `std::sort` (function template).
- **Exercises:**
  - Create a `std::vector` of ints and sort it.
  - Create a `std::vector` of strings and sort it.

👉 This is real-world use.

---

## **Multiple and Non-Type Parameters**

- **Multiple types:** `Pair<T1,T2>`.
- **Non-type params:** fixed-size array class.
  ```cpp
  template <typename T, int SIZE>
  class FixedArray {
      T data[SIZE];
  public:
      int size() const { return SIZE; }
  };
  ```
- **Exercises:**
  - Make a `Pair<int,string>`.
  - Make a `FixedArray<int,5>` and print its size.

👉 They realize templates can handle more than “one type”.

---

## **Specialization & Constraints**

- **Problem:** General template doesn’t always work (e.g., printing `bool`).
- **Solution:** Show **specialization**.
  ```cpp
  template <>
  class Printer<bool> {
      void print(bool value) {
          cout << (value ? "true" : "false");
      }
  };
  ```
- **C++20 concepts:** safer templates with constraints.
  ```cpp
  template <std::integral T>
  T square(T x) { return x*x; }
  ```

👉 STL has _rules_ for template types.”

---

## **Template Metaprogramming**

- Show factorial at compile time (`Factorial<5>::value`).
- Or constexpr as modern replacement.
- Keep this **lightweight**—just a taste.
- Frame it as: _“This is how libraries like Eigen or Boost work under the hood.”_

# 📘 Build Your Own Generic Stack

## 🎯 Goal

You will design and implement a **generic stack** class in C++ using **templates**. Then, you will test your stack against `std::stack` to see how the Standard Template Library (STL) solves the same problem.

The point isn’t just to make another stack—it’s to understand how **function templates, class templates, and specialization** work in the real world.

---

## 📋 Requirements

1. **Template Class**

   - Implement a class `Stack<T>` that works with **any data type**.
   - Support at least the following methods:
     - `push(const T&)` → add an element
     - `pop()` → remove the top element
     - `top()` → return (but don’t remove) the top element
     - `empty()` → check if stack is empty
     - `size()` → return number of elements

2. **Underlying Storage**

   - You may implement your stack using:
     - A **dynamic array** (`new[]` / `delete[]` or `std::vector`), OR
     - A **linked list** (struct `Node {T data; Node* next;}` style).

3. **Error Handling**

   - Decide what happens when calling `pop()` or `top()` on an empty stack.
     - Throw an exception, OR
     - Print an error and exit (old school).

4. **Comparison with STL**

   - Write a small program that:
     - Uses your `Stack<T>` with `int`, `double`, and `std::string`.
     - Uses `std::stack<T>` with the same types.
     - Demonstrates both stacks doing the same job.

5. **Bonus (Optional, for the bold)**
   - Add a **specialization** for `Stack<bool>` so that values are stored as bits (hint: `std::vector<bool>` is weird for this very reason).
   - Add a `print()` function template that prints the contents of the stack differently depending on type.

---

## 🧑‍💻 Starter Code

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
class Stack {
private:
    vector<T> data;
public:
    void push(const T& value) {
        data.push_back(value);
    }
    void pop() {
        if (!data.empty()) data.pop_back();
        else cerr << "Stack underflow!" << endl;
    }
    T top() {
        if (!data.empty()) return data.back();
        throw runtime_error("Empty stack!");
    }
    bool empty() const {
        return data.empty();
    }
    int size() const {
        return data.size();
    }
};

int main() {
    Stack<int> s;
    s.push(10);
    s.push(20);
    cout << "My stack top: " << s.top() << endl;

    std::stack<int> stlStack;
    stlStack.push(10);
    stlStack.push(20);
    cout << "STL stack top: " << stlStack.top() << endl;

    return 0;
}
```

---

## ✅ Deliverables

1. `stack.h` – Your class definition.
2. `main.cpp` – Test program comparing your stack with `std::stack`.
3. `README.md` – Short writeup explaining:
   - Your design decisions.
   - Comparison to STL (pros, cons, features STL has that you didn’t implement).

---

## 🏆 Learning Outcomes

By completing this assignment, students will:

- Understand how to write a **class template**.
- Gain appreciation for the STL’s generic containers.
- Experience how specialization/customization can make templates more powerful.
- Practice good testing and documentation habits.

---

# 🧍 Example: Sorting People by Last Name (No Templates Yet)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Person {
    string first;
    string last;
    int age;
};

// Comparator function just for Person
bool compareByLastName(const Person &a, const Person &b) {
    return a.last < b.last;
}

int main() {
    vector<Person> people = {
        {"Alice", "Smith", 30},
        {"Bob", "Jones", 25},
        {"Charlie", "Anderson", 35}
    };

    sort(people.begin(), people.end(), compareByLastName);

    for (const auto &p : people) {
        cout << p.last << ", " << p.first << " (" << p.age << ")" << endl;
    }
}
```

✔ Works fine, but… you’re locked into **only last name**. Want to sort by first name, or age? Time to rewrite another comparator. Boring.

---

# 🔧 Templated Comparator (Generic Approach)

We can make a **function template** that takes a _getter function_ (or lambda) for the field we want to sort on.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct Person {
    string first;
    string last;
    int age;
};

// Generic sort by field template
template <typename T, typename F>
void sortBy(vector<T> &items, F fieldGetter) {
    sort(items.begin(), items.end(),
         [&](const T &a, const T &b) {
             return fieldGetter(a) < fieldGetter(b);
         });
}

int main() {
    vector<Person> people = {
        {"Alice", "Smith", 30},
        {"Bob", "Jones", 25},
        {"Charlie", "Anderson", 35}
    };

    // Sort by last name
    sortBy(people, [](const Person &p){ return p.last; });

    cout << "Sorted by last name:\n";
    for (const auto &p : people)
        cout << p.last << ", " << p.first << " (" << p.age << ")\n";

    // Sort by first name
    sortBy(people, [](const Person &p){ return p.first; });

    cout << "\nSorted by first name:\n";
    for (const auto &p : people)
        cout << p.last << ", " << p.first << " (" << p.age << ")\n";

    // Sort by age
    sortBy(people, [](const Person &p){ return p.age; });

    cout << "\nSorted by age:\n";
    for (const auto &p : people)
        cout << p.last << ", " << p.first << " (" << p.age << ")\n";
}
```

---

# ✅ Key Points

1. **Without templates**: You hardcode a comparator like `compareByLastName`. Works, but limited.
2. **With templates**: You define `sortBy` that takes a **generic getter**. Now you can reuse the same template for _any field_.
3. This approach is essentially what STL does with `std::sort` + lambdas—you’re giving it a **custom comparison strategy**.
