```yaml
title: "Understanding the vtable in C++"
topic: "Dynamic Polymorphism and Virtual Functions"
summary: "A vtable (virtual table) is the behind-the-scenes mechanism C++ uses to implement runtime polymorphism — it maps virtual function calls to the correct function implementation at runtime."
keywords:
  [
    "vtable",
    "virtual function",
    "dynamic dispatch",
    "runtime polymorphism",
    "C++",
  ]
```

---

### 🎩 The Elevator Pitch

The **vtable** is basically the **menu of virtual functions** your object carries around.
When you call a virtual function, C++ looks it up in this menu to decide **which actual function to execute** — even if the pointer type doesn’t match the real object type.

It’s like your class’s personal “phonebook” of function addresses.

---

### 🧱 How It’s Built

When you mark at least one method in a class as `virtual`, the compiler secretly adds two things:

1. A **vtable** (virtual table) — a hidden static table containing **function pointers** for that class’s virtual methods.
2. A hidden **vptr** (virtual pointer) inside each object — it points to that class’s vtable.

Here’s the invisible magic:

```cpp
class Base {
public:
    virtual void speak() { std::cout << "Base speaks\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void speak() override { std::cout << "Derived speaks\n"; }
};
```

Behind the scenes:

| Class     | vtable contents                         |
| :-------- | :-------------------------------------- |
| `Base`    | `&Base::speak`, `&Base::~Base`          |
| `Derived` | `&Derived::speak`, `&Derived::~Derived` |

When you construct a `Derived` object, its constructor makes sure the `vptr` (invisible member) points to **Derived’s** vtable, not Base’s.

---

### 🧠 The Mental Model

```cpp
Base* b = new Derived();
b->speak();  // Which one?
```

At runtime:

1. The compiler sees `b->speak()` is **virtual**.
2. It follows `b`’s **vptr** → which points to Derived’s vtable.
3. It calls whatever function pointer is stored there (`Derived::speak`).

Voilà! Dynamic dispatch.

---

### 🕵️ Under the Hood Example (Conceptual)

Let's peek at what the compiler _might_ do internally:

```cpp
// Pseudo-code (not real C++)
struct Base_vtable {
    void (*speak_ptr)(Base*);
    void (*destructor_ptr)(Base*);
};

Base_vtable Base_vtbl = {
    &Base::speak,
    &Base::~Base
};

Base_vtable Derived_vtbl = {
    &Derived::speak,
    &Derived::~Derived
};

struct Base {
    Base_vtable* vptr;
};

struct Derived : Base {
    Derived() { vptr = &Derived_vtbl; }
};
```

When you call `b->speak()`, it’s really:

```cpp
b->vptr->speak_ptr(b);
```

That’s the **vtable call**.

---

### ⚡ When It Matters

| Situation                                   | Does it use vtable? | Notes                                     |
| ------------------------------------------- | ------------------- | ----------------------------------------- |
| Non-virtual function                        | ❌ No               | Direct compile-time binding               |
| Virtual function via base pointer/reference | ✅ Yes              | Dynamic dispatch                          |
| Object (not pointer/ref)                    | ❌ No               | Calls resolved at compile-time            |
| Virtual destructor                          | ✅ Yes              | Ensures derived destructors run correctly |

---

### 💣 Common Misunderstandings

- **Vtables aren’t part of the C++ standard** — they’re just how _every compiler on Earth_ happens to implement polymorphism.
- **No vtable = no runtime polymorphism.** Templates, overloading, and static polymorphism (CRTP, `constexpr` tricks) do _not_ use vtables.
- Each polymorphic class typically has **one vtable**, shared among all its instances.

---

### 🧩 Memory and Performance Impact

Each object gains one hidden pointer (usually 8 bytes on 64-bit).
Each class with virtuals gets one vtable in static memory.
Calling a virtual function takes:

- One pointer dereference (vptr lookup)
- One indirect jump (through the vtable function pointer)

That’s roughly one extra level of indirection — negligible for most uses, but significant in tight inner loops.

---

### 🔧 Vtable and Destructors

If you make a base class destructor **virtual**, deleting through a base pointer calls the correct destructor chain via the vtable:

```cpp
Base* b = new Derived();
delete b;  // Calls Derived::~Derived then Base::~Base via vtable
```

Without a virtual destructor → _undefined behavior_ city 🏙️ (only the base part gets destroyed).

---

### 🔬 Fun Demo

Try this:

```cpp
#include <iostream>
using namespace std;

class A {
public:
    virtual void foo() { cout << "A::foo\n"; }
};
class B : public A {
public:
    void foo() override { cout << "B::foo\n"; }
};

int main() {
    A a;
    B b;
    cout << "A vtable address: " << *(void**)&a << endl;
    cout << "B vtable address: " << *(void**)&b << endl;
}
```

You’ll see **two different addresses** printed — that’s the vtable pointer each object holds.

---

### 🧙‍♂️ TL;DR Summary

| Concept              | Explanation                                                 |
| :------------------- | :---------------------------------------------------------- |
| **vtable**           | Table of function pointers for virtual methods              |
| **vptr**             | Hidden pointer in each object, points to its class’s vtable |
| **Dynamic dispatch** | Runtime decision of which overridden function to call       |
| **Cost**             | One pointer per object, one indirection per virtual call    |
| **No vtable?**       | No polymorphism magic. Everything’s static.                 |

---
