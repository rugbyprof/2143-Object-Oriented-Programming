```yaml
title: "C++ Constructors & Initialization Lists – Exam Study Summary"
course: "2143 – Object-Oriented Programming"
author: "ChatGPT for Terry"
date: 2026-02-18
tags: [C++, constructors, initialization-lists, default-constructor, overloading, exam-review]
```

# Constructors & Initialization Lists (C++)

Constructors answer one fundamental question:

> **How does an object become valid the moment it exists?**

If your object starts life half-formed and confused, your entire program will eventually pay for that decision.

---

# 1️⃣ What Is a Constructor?

A constructor is a special member function that:

- Has the **same name as the class**
- Has **no return type**
- Runs automatically when an object is created

### Basic Example

```cpp
class Person {
private:
    std::string name;
    int age;

public:
    Person(std::string n, int a) {
        name = n;
        age = a;
    }
};
```

When we do:

```cpp
Person p("Alice", 25);
```

The constructor runs immediately.

---

# 2️⃣ Does a Class Need a Constructor?

### Short Answer:
**No… unless you need control over initialization.**

### What actually happens?

If you do NOT define any constructor:

```cpp
class Foo {
    int x;
};
```

The compiler will generate a **default constructor automatically**.

BUT…

- It does **not initialize built-in types** (like `int`)
- `x` will contain garbage if not explicitly initialized

That’s how mysterious bugs are born.

---

### So when do you need a constructor?

You need one when:

- You must initialize data members
- You must enforce invariants
- Your class contains `const` members
- Your class contains references
- Your class contains objects without default constructors

In real programs?

Almost always.

---

# 3️⃣ Initialization Lists (The Correct Way)

You *can* assign inside the constructor body:

```cpp
Person(std::string n, int a) {
    name = n;
    age = a;
}
```

But this actually:

1. Default-constructs members first  
2. Then assigns new values  

That’s inefficient and sometimes illegal.

---

### Proper Way: Initialization List

```cpp
class Person {
private:
    std::string name;
    int age;

public:
    Person(const std::string& n, int a)
        : name(n), age(a)   // Initialization list
    {}
};
```

### Why This Is Better:

- Direct initialization
- Required for `const` members
- Required for references
- Required for some objects
- More efficient
- More correct

---

## 🚨 Example Where Initialization List Is REQUIRED

```cpp
class Example {
private:
    const int value;
    int& ref;

public:
    Example(int v, int& r)
        : value(v), ref(r)
    {}
};
```

You **cannot** assign to `const` or references later.  
They must be initialized before the constructor body runs.

---

# 4️⃣ What Is a Default Constructor?

A **default constructor** is a constructor that:

- Takes **no parameters**, OR
- Has all parameters with default values

### Example 1: Explicit Default Constructor

```cpp
class Dog {
public:
    Dog() {
        std::cout << "Dog created.\n";
    }
};
```

---

### Example 2: Constructor With Default Arguments

```cpp
class Dog {
private:
    std::string name;

public:
    Dog(std::string n = "Unnamed")
        : name(n)
    {}
};
```

This still counts as a default constructor because it can be called with no arguments:

```cpp
Dog d;   // OK
```

---

# 5️⃣ Why Overload Constructors?

Constructor overloading allows multiple ways to create an object.

Because real-world objects don’t always start the same way.

---

### Example

```cpp
class Rectangle {
private:
    int width;
    int height;

public:
    Rectangle() : width(0), height(0) {}

    Rectangle(int w, int h)
        : width(w), height(h) {}

    Rectangle(int side)
        : width(side), height(side) {}
};
```

Now we can do:

```cpp
Rectangle r1;          // 0 x 0
Rectangle r2(4, 5);    // 4 x 5
Rectangle r3(7);       // square
```

### Why this is powerful:

- Flexible object creation
- Clear intent
- Supports multiple valid starting states
- Avoids forcing awkward “dummy values”

---

# 6️⃣ Constructor Execution Order (Important for Exams)

When an object is created:

1. Base class constructors run first  
2. Member variables are initialized (in declaration order)  
3. Constructor body executes  

Even if your initialization list orders them differently,
**C++ initializes in the order they are declared in the class.**

That’s a favorite exam trap.

---

# 7️⃣ Key Takeaways (Exam-Worthy)

- Constructors ensure objects start in a valid state.
- Classes do NOT strictly require a constructor — but they often should have one.
- Initialization lists are the correct and efficient way to initialize members.
- Default constructor = callable with zero arguments.
- Constructor overloading provides flexibility and better design.
- Initialization order follows declaration order, not list order.

---

# 💡 Why This Matters in Data Structures

If you build:

```cpp
class Stack {
private:
    std::vector<int> data;
};
```

Without a constructor, you rely on defaults.

But what if:

- You want an initial capacity?
- You want to pre-load values?
- You want to enforce max size?

Constructor design determines how robust your structure is from birth.

