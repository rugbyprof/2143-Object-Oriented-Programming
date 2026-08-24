# The `static` Keyword in C++

The word `static` appears in four distinct contexts in C++. Each one is different. This guide covers all four, with a focus on the two you'll use most in OOP: **static member variables** and **static member functions**.

---

## 1. Static Local Variables

Inside a function, `static` means "initialize once, persist forever."

```cpp
void countCalls() {
    static int count = 0;   // initialized only the first time this line runs
    count++;
    std::cout << "Called " << count << " times\n";
}
```

The variable lives for the entire program lifetime but is only visible inside `countCalls()`. Every call to the function shares the same `count`.

**When to use:** Rarely. Useful for simple memoization or a counter you don't want to expose. Avoid in multithreaded code.

---

## 2. Static Free Functions (File Scope)

Outside any class, `static` on a function means "only visible in this translation unit (.cpp file)."

```cpp
// helpers.cpp
static bool isValidRange(int val, int lo, int hi) {
    return val >= lo && val <= hi;
}
```

Nothing outside `helpers.cpp` can call `isValidRange`. This is a way to hide implementation details.

**When to use:** When you have helper functions that are an implementation detail of one .cpp file and shouldn't be callable from anywhere else. Modern C++ prefers anonymous namespaces for this, but `static` still works.

---

## 3. Static Member Variables

A static member variable belongs to the **class**, not to any individual object. There is exactly one copy, shared by all instances.

```cpp
class Widget {
public:
    static int instanceCount;   // declaration — one shared copy
    Widget()  { instanceCount++; }
    ~Widget() { instanceCount--; }
};

// Definition must appear in exactly one .cpp file:
int Widget::instanceCount = 0;
```

```cpp
Widget a, b, c;
std::cout << Widget::instanceCount;  // 3
```

Notice: accessed via `Widget::instanceCount`, not via an object. You can access it through an object (`a.instanceCount`) but that's misleading — it suggests the value belongs to `a`.

**When to use:**
- Tracking how many instances exist
- Shared configuration or constants (prefer `static const` or `static constexpr`)
- Caches or registries shared across all instances

---

## 4. Static Member Functions

A static member function belongs to the **class**, not to any object. It has no `this` pointer, so it cannot access non-static member variables.

```cpp
class MathUtils {
public:
    static int clamp(int val, int lo, int hi);
    static bool isPowerOfTwo(int n);
};

// Called on the class, not an object:
int x = MathUtils::clamp(300, 0, 255);
```

Because there is no `this`, a static method:
- Cannot read or write non-static member variables
- Cannot call non-static member functions
- Can be called without creating any object at all

**When to use:**
- **Factory methods** — create and return an instance of the class (see below)
- **Utility/helper methods** — operations logically grouped with the class but not tied to one instance
- **Named constructors** — different static methods that create objects in different ways

---

## The Factory Pattern

The most important use of `static` in OOP is the **static factory method**: a static function that constructs and returns an object of its own class.

```cpp
// Instead of:
Args args(argc, argv);   // constructor does all the work — hard to signal failure

// Prefer:
Args args = Args::parse(argc, argv);   // static factory — clear intent, can throw
```

Why this is better:
- Constructors can't have meaningful names. `Args::fromFile()`, `Args::defaults()`, and `Args::parse()` are self-documenting; three overloaded constructors are not.
- Constructors can't return `nullptr` or a sentinel. A factory method can.
- Constructors always produce an object. A factory can throw with a clear error message before anything is constructed.

---

## A Class Built Entirely From Static Methods

Some classes exist purely as a namespace for related operations — they are never instantiated. Making the constructor private enforces this.

```cpp
// PixelOps.h
#pragma once
#include "Filter.h"   // for Pixel

// A collection of stateless pixel-level operations.
// Never instantiate this class — use it like a namespace.
class PixelOps {
public:
    // Prevent construction entirely
    PixelOps() = delete;

    // Clamp a channel value to [0, 255]
    static int clamp(int val);

    // Convert an RGB pixel to its grayscale average
    static Pixel toGrayscale(const Pixel& p);

    // Add a brightness delta to a pixel, clamping each channel
    static Pixel brighten(const Pixel& p, int delta);

    // Blend two pixels: result = (a * t) + (b * (1-t)),  t in [0.0, 1.0]
    static Pixel blend(const Pixel& a, const Pixel& b, float t);
};
```

```cpp
// PixelOps.cpp
#include "PixelOps.h"
#include <algorithm>

int PixelOps::clamp(int val) {
    return std::max(0, std::min(255, val));
}

Pixel PixelOps::toGrayscale(const Pixel& p) {
    int avg = (p.r + p.g + p.b) / 3;
    return {avg, avg, avg};
}

Pixel PixelOps::brighten(const Pixel& p, int delta) {
    return {
        clamp(p.r + delta),
        clamp(p.g + delta),
        clamp(p.b + delta)
    };
}

Pixel PixelOps::blend(const Pixel& a, const Pixel& b, float t) {
    return {
        clamp(static_cast<int>(a.r * t + b.r * (1 - t))),
        clamp(static_cast<int>(a.g * t + b.g * (1 - t))),
        clamp(static_cast<int>(a.b * t + b.b * (1 - t)))
    };
}
```

Usage — no object, ever:

```cpp
Pixel p = {200, 100, 50};
Pixel gray  = PixelOps::toGrayscale(p);
Pixel light = PixelOps::brighten(p, 40);
Pixel mixed = PixelOps::blend(p, gray, 0.5f);
```

This pattern is common in utility libraries (`std::filesystem`, `std::chrono`, Java's `Math`, etc.).

---

## Quick Reference

| Context | What `static` means |
|---|---|
| Local variable | Initialize once, persist for program lifetime |
| Free function | Visible only within this .cpp file |
| Member variable | One shared copy for the entire class |
| Member function | No `this` — callable without an object |

---

## When NOT to Use Static

- Don't make a method static just because it doesn't happen to use `this` yet. If it's logically about one object's state, keep it a regular method.
- Don't use static members as a backdoor global variable. If you find yourself writing `static std::vector<Thing*> registry` in every class, reconsider your design.
- Don't use static to avoid passing arguments. A function that needs data should receive it as a parameter, not reach into shared state.

---

## Relevance to P02 and P03

In P02 you wrote (or saw) `Args::parse(argc, argv)` — a static factory method. The constructor stays simple (or private); all the complex work of reading `argv`, validating inputs, and throwing errors lives in the static method.

In P03, `PixelOps` above is an optional helper you could use inside your filter implementations. Every filter's `apply()` loop becomes a one-liner:

```cpp
void Brighten::apply(Grid& pixels) {
    for (Row& row : pixels)
        for (Pixel& p : row)
            p = PixelOps::brighten(p, delta);
}
```

The static utility class doesn't replace the `Filter` hierarchy — it just pulls the low-level math out of the loop so the loop reads cleanly.
