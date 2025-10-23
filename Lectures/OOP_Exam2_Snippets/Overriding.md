## Overriding A Method

**Overriding** in C++ is when a **derived class provides its own version of a virtual function** defined in a **base class**, using the **same function signature**.

It allows the derived class to change or extend the behavior of that function when called through a base class pointer or reference.

Example:

```cpp
class Base {
public:
    virtual void speak() { std::cout << "Base speaking\n"; }
};

class Derived : public Base {
public:
    void speak() override { std::cout << "Derived speaking\n"; }
};
```

Here, `Derived::speak()` **overrides** `Base::speak()`.

### ✅ Is It Just The Name?

Short Answer: NO!

To override a method in C++, 👉 **the function signature must match exactly** — not just the name.

That means:

- The **function name** must match.
- The **parameter types** (and their order) must match.
- The **const-ness** must match (e.g., `void foo() const` ≠ `void foo()`).
- The **return type** must match (or be _covariant_ — more on that below). (Not on Exam)
- The **function must be virtual** in the base class.

---

### ⚙️ **Example: Correct Override**

```cpp
#include <iostream>

class Animal {
public:
    virtual void speak() {           // virtual = can be overridden
        std::cout << "Animal sound\n";
    }
};

class Dog : public Animal {
public:
    void speak() override {          // ✅ same signature, overrides base
        std::cout << "Woof!\n";
    }
};
```

**Output:**

```cpp
Animal* a = new Dog();
a->speak();   // Woof!
```

Perfect override ✅

---

### 🚫 **Example: Wrong Signature (No Override Happens)**

```cpp
class Dog : public Animal {
public:
    void speak(std::string sound) {  // 🚫 different parameter list
        std::cout << sound << "\n";
    }
};
```

Even though the function name `speak` matches, the **signature is different** — it **hides** the base class version instead of overriding it.

**Result:**

```cpp
Animal* a = new Dog();
a->speak();           // Animal sound   (still calls base version!)
```

To make it obvious when you accidentally do this, always use the `override` keyword — the compiler will yell at you:

```cpp
void speak(std::string sound) override; // ❌ error: no function to override
```

---

### 🧠 **Covariant Return Types (Advanced Bonus)**

**Advanced topic, not on exam.**

There’s one small exception:  
You _can_ change the return type **if** it’s a _pointer or reference to a derived type_.

```cpp
class Animal {
public:
    virtual Animal* clone() const { return new Animal(*this); }
};

class Dog : public Animal {
public:
    Dog* clone() const override { return new Dog(*this); } // ✅ covariant return type
};
```

---

### 📘 **Summary Table**

| Rule            | Must Match?         | Notes                                          |
| --------------- | ------------------- | ---------------------------------------------- |
| Function name   | ✅ Yes              | Must be identical                              |
| Parameter list  | ✅ Yes              | Types and order must match                     |
| Const qualifier | ✅ Yes              | `void f()` ≠ `void f() const`                  |
| Return type     | ✅ Usually          | Can differ only if covariant                   |
| Virtual keyword | ⚠️ Required in base | Without it, you’re just hiding, not overriding |

---

Would you like me to show a quick example where _function hiding_ (same name, different signature) causes a subtle bug — and how to fix it with `using Base::functionName`? That’s another classic “gotcha” in C++.
