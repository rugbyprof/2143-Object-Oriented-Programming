```yaml
topic: "C++ Inheritance Overview"
course: "OOP / C++"
author: "ChatGPT"
notes: "High-level overview + examples; tone: casual, detailed, clever"
```

# 🧬 C++ Inheritance — The “Family Tree” You Actually Care About

Below is a clean, thorough rundown of **the different types of inheritance in C++**, why they matter, and little code snippets to make them stick.

---

# 🏠 1. **Single Inheritance**

**One parent → one child.**  
The most normal, drama-free relationship in the C++ family.

### ✔️ When you use it

When a class needs to _extend_ or _specialize_ one base class.

### 🧩 Example

```cpp
class Animal {
public:
    void speak() { cout << "Generic animal sound\n"; }
};

class Dog : public Animal {
public:
    void speak() { cout << "Woof!\n"; }
};
```

---

# 🏘️ 2. **Multiple Inheritance**

**One child → multiple parents.**  
Also known as “your class now has two moms and three wills.”

### ✔️ When you use it

When you want a class to combine _capabilities_ from different base classes (e.g., `Serializable` + `Renderable`, etc.).

### ⚠️ The infamous Diamond Problem

If two base classes share a common ancestor, ambiguity arises.  
C++ solves this with **virtual inheritance**.

### 🧩 Example

```cpp
class Printable {
public:
    void print() { cout << "printing...\n"; }
};

class Loggable {
public:
    void log() { cout << "logging...\n"; }
};

class Document : public Printable, public Loggable {};
```

---

# 💎 3. **Multilevel Inheritance**

**Grandparent → parent → child.**

### ✔️ When to use it

When building increasingly specialized types in layers.

### 🧩 Example

```cpp
class LivingThing { };

class Animal : public LivingThing { };

class Dog : public Animal { };
```

---

# 🧬 4. **Hierarchical Inheritance**

**One parent → multiple children.**

This is literally every “base class with multiple derived types” situation.

### 🧩 Example

```cpp
class Shape { };

class Circle : public Shape { };
class Rectangle : public Shape { };
class Triangle : public Shape { };
```

---

# 🔷 5. **Hybrid Inheritance**

A combination of the above — usually multiple + hierarchical or multilevel.

### ✔️ Why it comes up

Because real systems are messy, and you’ll eventually create a class diagram that looks like spaghetti.

### 🧩 Example involving multiple + hierarchical

```cpp
class A { };
class B : public A { };
class C : public A { };
class D : public B, public C { };  // hybrid, also diamond risk
```

---

# 🔹 6. **Virtual Inheritance**

Not a separate “type,” but a **modifier** that fixes the Diamond Problem.

If you have this:

```
      Animal
      /    \
   Dog    Cat
      \    /
      Chimera
```

Both `Dog` and `Cat` inherit `Animal`, so `Chimera` would have **two** `Animal` subobjects unless you use `virtual`.

### 🧩 Example

```cpp
class Animal {
public:
    int age;
};

class Dog : virtual public Animal { };
class Cat : virtual public Animal { };

// Chimera gets only one Animal subobject
class Chimera : public Dog, public Cat { };
```

---

# 🎓 Quick Comparison Table

| Type         | Description                     | Common Use                           |
| ------------ | ------------------------------- | ------------------------------------ |
| Single       | One base → one derived          | Simple specialization                |
| Multiple     | One class inherits from >1 base | Mix capabilities (interfaces/mixins) |
| Multilevel   | Chain of inheritance            | Layered specialization               |
| Hierarchical | One base → many derived         | Polymorphic families (e.g., shapes)  |
| Hybrid       | Any combination                 | Real-world complex models            |
| Virtual      | Fixes duplicate base classes    | Solves the diamond problem           |
