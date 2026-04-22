```yaml
title: Test 3
description: Test 2 Take-Home
due: 24 Apr 2026
slug: Exam_03
id: 12-T03
name: 12-T03
category: exam
date_assigned: 2026-04-17 12:00
date_due: 2026-04-24 11:00
resources: []
```

# 2143 OOP — Exam 3 Study Guide

**Course:** 2143 Object-Oriented Programming
**Prepared for:** Spring 2026 — Exam 3 Prep
**Coverage:** Topics under-tested on Exam 2 + new material for Exam 3

---

## How to Use This Guide

Each section contains:

- **Definition** — the clean, testable version
- **Key Concepts** — what you actually need to remember
- **Code Example** — a minimum working example
- **Practice Questions** — multiple choice, short answer, code analysis, and code writing

If you can answer every question in every section without peeking, you're ready. If you can't, you know exactly where to drill.

---

# PART 1 — Topics Under-Tested on Exam 2 (Fair Game Again)

## 1. Inheritance Hierarchies

### Definition

**Inheritance** is a mechanism where a new class (the _derived_ or _child_ class) acquires the properties and behaviors of an existing class (the _base_ or _parent_ class). It models an **"is-a"** relationship.

### Key Concepts

- Syntax: `class Derived : access-specifier Base { ... };`
- The access specifier (`public`, `protected`, `private`) controls how inherited members are exposed in the derived class.
- **`public` inheritance** is by far the most common and preserves the base class interface.
- Derived classes **cannot** access the `private` members of their base — only `public` and `protected`.
- Constructors run **top-down** (base first, then derived). Destructors run **bottom-up** (derived first, then base).

### Code Example

```cpp
class Animal {
protected:
    string name;
public:
    Animal(string n) : name(n) { cout << "Animal ctor\n"; }
    ~Animal() { cout << "Animal dtor\n"; }
    void eat() { cout << name << " eats.\n"; }
};

class Dog : public Animal {
public:
    Dog(string n) : Animal(n) { cout << "Dog ctor\n"; }
    ~Dog() { cout << "Dog dtor\n"; }
    void bark() { cout << name << " barks!\n"; }  // name is protected, so OK
};

int main() {
    Dog d("Rex");
    d.eat();   // inherited from Animal
    d.bark();  // defined in Dog
}
```

### Practice Questions

**MC1.** What is the output order when a `Dog` object is created and then goes out of scope?

- A. Dog ctor, Animal ctor, Dog dtor, Animal dtor
- B. Animal ctor, Dog ctor, Animal dtor, Dog dtor
- C. Animal ctor, Dog ctor, Dog dtor, Animal dtor
- D. Dog ctor, Animal ctor, Animal dtor, Dog dtor

**MC2.** If `Animal` has a `private` member `int age;`, which is true inside `Dog`?

- A. Dog can read and write `age` directly
- B. Dog can read but not write `age`
- C. Dog cannot access `age` directly at all
- D. Dog must use the `friend` keyword to access `age`

**Short Answer.** Explain the difference between `public` and `protected` inheritance in one sentence each.

**Code Writing.** Create a `Vehicle` base class with data `brand` and method `honk()`. Derive a `Car` class that adds `int doors` and method `drive()`. Show the constructor for `Car` calling the `Vehicle` constructor.

---

## 2. Abstract Classes & Pure Virtual Functions

### Definition

An **abstract class** is a class that **cannot be instantiated** because it contains at least one **pure virtual function** — a virtual function declared with `= 0` and no body. Abstract classes exist to define a common interface that derived classes must implement.

### Key Concepts

- Syntax for a pure virtual: `virtual returnType funcName(params) = 0;`
- A class with **even one** pure virtual function is abstract.
- Derived classes must **override** every pure virtual, or they remain abstract too.
- You can still have pointers and references to an abstract class — just not objects.
- Abstract classes can have data members and regular (non-pure) methods.

### Code Example

```cpp
class Shape {
public:
    virtual double area() const = 0;     // pure virtual — must be overridden
    virtual void draw() const = 0;       // pure virtual
    virtual ~Shape() {}                  // virtual dtor — always include!
    void describe() const {              // regular method — inherited as-is
        cout << "A shape with area " << area() << "\n";
    }
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    void draw() const override { cout << "drawing circle\n"; }
};

int main() {
    // Shape s;             // ERROR — cannot instantiate abstract class
    Shape* s = new Circle(5.0);
    s->describe();           // calls Circle::area() polymorphically
    delete s;
}
```

### Practice Questions

**MC1.** Which declaration makes a function pure virtual?

- A. `virtual void draw() const;`
- B. `virtual void draw() const = 0;`
- C. `void draw() const override;`
- D. ` virtual void draw() = 0;`

**MC2.** If `Shape` has a pure virtual `area()` and `Circle : public Shape` does _not_ override it, what happens?

- A. `Circle` compiles and inherits a default `area()`
- B. `Circle` is also abstract and cannot be instantiated
- C. The compiler throws a runtime error
- D. `Circle` instantiation produces undefined behavior

**Short Answer.** Why would you make a class abstract even though it "works"? Give one practical reason.

**Code Analysis.**

```cpp
class A {
public:
    virtual void f() = 0;
    void g() { cout << "g\n"; }
};

A a;     // LINE 1
A* p;    // LINE 2
```

Which line is illegal and why?

---

## 3. Virtual Destructors (Critical Topic)

### Definition

A **virtual destructor** is a destructor declared with the `virtual` keyword. It ensures that when an object is deleted through a base class pointer, the **derived class destructor runs first**, then the base class destructor — preventing resource leaks.

### Key Concepts

- **Rule:** Any class intended to be inherited from should have a virtual destructor.
- Without it, `delete basePtr;` only runs the base destructor — derived class resources leak.
- Abstract classes should _always_ have a virtual destructor (even if empty: `virtual ~Shape() {}`).
- This is one of the most common real-world bugs in C++ codebases.

### Code Example

```cpp
class Base {
public:
    Base()  { cout << "Base ctor\n"; }
    ~Base() { cout << "Base dtor\n"; }   // NOT virtual — bug!
};

class Derived : public Base {
    int* data;
public:
    Derived()  { data = new int[100]; cout << "Derived ctor\n"; }
    ~Derived() { delete[] data; cout << "Derived dtor\n"; }
};

int main() {
    Base* p = new Derived();
    delete p;   // Only "Base dtor" runs — Derived::data leaks!
}
```

**Fix:** Change `~Base()` to `virtual ~Base() { ... }`. Now both destructors run in the correct order.

### Practice Questions

**MC1.** When should a destructor be declared `virtual`?

- A. Always, for every class
- B. Only when the class has dynamic memory
- C. When the class is intended to be inherited from
- D. Only when the class uses operator overloading

**MC2.** What happens when `delete p;` runs on `Base* p = new Derived();` if `~Base()` is **not** virtual?

- A. Both destructors run correctly
- B. Only `~Derived()` runs
- C. Only `~Base()` runs, potentially leaking derived resources
- D. The program crashes

**Short Answer.** What's the minimum-effort virtual destructor you can write for an abstract base class?

---

## 4. The `protected` Access Modifier

### Definition

The **`protected`** access modifier makes members accessible to the class itself and to its derived classes, but **not** to outside code. It sits between `private` (only the class) and `public` (everyone).

### Key Concepts

- Derived classes can use `protected` members directly.
- External code (including `main`) cannot touch `protected` members.
- Use `protected` for data/helpers that subclasses genuinely need, but keep as private as you can get away with — `protected` still weakens encapsulation.

### Code Example

```cpp
class Account {
protected:
    double balance;
public:
    Account(double b) : balance(b) {}
    double getBalance() const { return balance; }
};

class Savings : public Account {
public:
    Savings(double b) : Account(b) {}
    void addInterest(double rate) {
        balance *= (1 + rate);   // OK — protected from inside derived
    }
};

int main() {
    Savings s(1000);
    s.addInterest(0.05);
    // s.balance = 0;   // ERROR — protected from outside
}
```

### Practice Questions

**MC1.** Which access modifier allows derived classes to access members but prevents external code from doing so?

- A. `private`
- B. `protected`
- C. `public`
- D. `friend`

**Short Answer.** Why might a senior developer prefer `private` data with `protected` getters over directly `protected` data?

---

## 5. Runtime Polymorphism (Deep Dive)

### Definition

**Runtime polymorphism** (also called **dynamic dispatch** or **late binding**) is the mechanism by which a call through a base class pointer or reference invokes the correct derived class function at runtime, based on the actual type of the object.

### Key Concepts

- Requires **`virtual`** functions in the base class.
- Requires a **pointer or reference** to the base type (`Base*` or `Base&`) — not by value.
- Calling `virtual` functions by value (object slicing) loses polymorphism.
- The **v-table** (vtable) is how the compiler implements this under the hood: a per-class table of function pointers.
- `override` keyword (C++11+) lets the compiler verify you're actually overriding.
- `final` keyword prevents further overriding.

### Code Example

```cpp
class Employee {
public:
    virtual double pay() const { return 0; }
    virtual ~Employee() {}
};

class Hourly : public Employee {
    double rate, hours;
public:
    Hourly(double r, double h) : rate(r), hours(h) {}
    double pay() const override { return rate * hours; }
};

class Salaried : public Employee {
    double salary;
public:
    Salaried(double s) : salary(s) {}
    double pay() const override { return salary / 26; }  // biweekly
};

void printPay(const Employee& e) {      // takes reference — polymorphism works
    cout << "Pay: " << e.pay() << "\n";
}

int main() {
    Hourly h(15.0, 40);
    Salaried s(52000);
    printPay(h);   // Hourly::pay
    printPay(s);   // Salaried::pay
}
```

### Practice Questions

**MC1.** Runtime polymorphism requires which of the following? (Choose all that apply.)

- A. The function must be declared `virtual` in the base class
- B. The call must be made through a base class pointer or reference
- C. The derived class must use the `override` keyword
- D. The base class must be abstract

**MC2.** What is object slicing?

- A. Removing members from an object at runtime
- B. When a derived object is assigned to a base object by value, losing the derived parts
- C. A compiler optimization
- D. Trimming a class's vtable

**Code Analysis.** Given the `Employee` hierarchy above, what does this print?

```cpp
Hourly h(20, 10);
Employee e = h;
cout << e.pay();
```

And why?

---

## 6.  Members & Static Methods

### Definition

A **static member** belongs to the class itself, not to any individual object. All instances share the same static member. A **static method** is a class-level function that can be called without an object and cannot access non-static members.

### Key Concepts

- Declared inside the class with `static`, **defined outside** the class (for data members).
- Accessed via `ClassName::member` — no object required.
- Common uses: object counters, constants, factory methods, singletons.
- Static methods have no `this` pointer.

### Code Example

```cpp
int count(){
    static int i=0;
    ++i;
    return i;
}

class Widget {
    static int count;           // declaration
    int id;
public:
    Widget() : id(++count) {}
    static int getCount() { return count; }   // static method
    int getId() const { return id; }
};

int Widget::count = 0;          // definition (required, outside class)

int main() {
    Widget a, b, c;
    cout << Widget::getCount();     // prints 3 — no object needed
}
```

### Practice Questions

**MC1.** Which of the following is **true** about static member functions?

- A. They have access to `this`
- B. They can only be called via an object
- C. They cannot access non-static data members directly
- D. Every class must have at least one

**Short Answer.** Where must a static data member be _defined_ (not declared)? Show the syntax.

**Code Writing.** Add a static `count` to the `Player` class so the game can ask "how many players exist?" without iterating.

---

## 7. Composition vs. Inheritance

### Definition

**Composition** ("has-a") is a design relationship where one class contains an instance of another as a member. **Inheritance** ("is-a") is when one class derives from another. Modern design advice: **prefer composition over inheritance** when possible.

### Key Concepts

- Composition is more flexible: you can swap parts at runtime.
- Inheritance creates tight coupling and can lead to fragile hierarchies (see: diamond problem).
- Good rule of thumb: if you'd say "a Car _is a_ Vehicle," use inheritance. If you'd say "a Car _has an_ Engine," use composition.

### Code Example

```cpp
// COMPOSITION — Car has-an Engine
class Engine {
public:
    void start() { cout << "Vroom!\n"; }
};

class Car {
    Engine engine;           // composition: Car owns an Engine
public:
    void drive() {
        engine.start();
        cout << "Driving.\n";
    }
};

// INHERITANCE — ElectricCar is-a Car
class ElectricCar : public Car {
public:
    void chargeBattery() { cout << "Charging.\n"; }
};
```

### Practice Questions

**MC1.** Which relationship is best modeled with **composition** rather than inheritance?

- A. A `Square` and a `Shape`
- B. A `House` and a `Room`
- C. A `Dog` and an `Animal`
- D. A `Manager` and an `Employee`

**Short Answer.** Give one scenario where inheritance is clearly the right choice, and one where composition is clearly better.

---

# PART 2 — New Material for Exam 3

## 8. Multiple Inheritance & the Diamond Problem

### Definition

**Multiple inheritance** is when a class inherits from more than one base class. The **diamond problem** arises when a class inherits from two classes that share a common base — creating ambiguity about which copy of the grandparent's members to use.

### Key Concepts

- Syntax: `class D : public B1, public B2 { ... };`
- **Virtual inheritance** solves the diamond problem: `class B : virtual public A { ... };`
- With virtual inheritance, only one copy of the shared base exists.
- Many languages (Java, C#) disallow multiple inheritance specifically to dodge this problem.

### Code Example

```cpp
class Device {
public:
    int id;
};

// Without virtual inheritance, Printer and Scanner each get their own Device copy
class Printer : virtual public Device { };
class Scanner : virtual public Device { };

// The diamond — resolved by virtual inheritance above
class Copier : public Printer, public Scanner {
public:
    void useId() { cout << id; }    // unambiguous thanks to 'virtual'
};
```

### Practice Questions

**MC1.** The diamond problem occurs when:

- A. A class has too many methods
- B. Two derived classes share a base class and a fourth class inherits from both
- C. Inheritance goes more than four levels deep
- D. Virtual functions conflict across classes

**MC2.** Which keyword is used to solve the diamond problem in C++?

- A. `abstract`
- B. `final`
- C. `virtual` (in the inheritance declaration)
- D. `override`

**Short Answer.** Why do Java and C# disallow multiple inheritance of classes? What do they offer instead?

---

## 9. Exception Handling (HIGH PRIORITY — INDUSTRY RELEVANT)

### Definition

**Exception handling** is a mechanism for responding to runtime errors in a structured, propagating way. Code that might fail is placed in a `try` block, errors are signaled with `throw`, and handled in one or more `catch` blocks.

### Key Concepts

- Three keywords: **`try`**, **`throw`**, **`catch`**.
- Exceptions propagate up the call stack until caught.
- Uncaught exceptions call `std::terminate()`.
- Catch by `const` reference to avoid slicing: `catch (const MyException& e)`.
- The standard hierarchy is rooted at `std::exception` — inherit from it for custom exceptions.
- Common standard exceptions: `std::runtime_error`, `std::logic_error`, `std::invalid_argument`, `std::out_of_range`, `std::bad_alloc`.
- `catch(...)` catches anything — use only at the outermost layer.
- Exceptions and RAII go hand in hand — destructors run during stack unwinding.

### Code Example — The Basics

```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

double divide(double a, double b) {
    if (b == 0)
        throw runtime_error("Division by zero!");
    return a / b;
}

int main() {
    try {
        cout << divide(10, 2) << "\n";   // 5
        cout << divide(10, 0) << "\n";   // throws
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << "\n";
    }
    catch (const exception& e) {
        cout << "General error: " << e.what() << "\n";
    }
    catch (...) {
        cout << "Unknown error\n";
    }
}
```

### Code Example — Custom Exceptions

```cpp
#include <stdexcept>
#include <string>

class InsufficientFundsError : public std::runtime_error {
    double attempted;
public:
    InsufficientFundsError(double amt)
        : std::runtime_error("Insufficient funds"), attempted(amt) {}
    double getAttempted() const { return attempted; }
};

class Account {
    double balance = 0;
public:
    void withdraw(double amt) {
        if (amt > balance)
            throw InsufficientFundsError(amt);
        balance -= amt;
    }
};

int main() {
    Account a;
    try {
        a.withdraw(500);
    }
    catch (const InsufficientFundsError& e) {
        cout << e.what() << " (tried " << e.getAttempted() << ")\n";
    }
}
```

### Code Example — Exception Safety and Stack Unwinding

```cpp
class Resource {
public:
    Resource()  { cout << "Resource acquired\n"; }
    ~Resource() { cout << "Resource released\n"; }
};

void risky() {
    Resource r;
    throw runtime_error("boom");
    // "Resource released" STILL prints — destructors run during unwinding
}

int main() {
    try { risky(); }
    catch (const exception& e) { cout << "Caught: " << e.what() << "\n"; }
}
```

### Practice Questions

**MC1.** Which keyword is used to signal that an error has occurred?

- A. `try`
- B. `catch`
- C. `throw`
- D. `error`

**MC2.** What happens to an exception that is never caught?

- A. It is silently ignored
- B. It becomes a warning at compile time
- C. `std::terminate()` is called, typically ending the program
- D. It becomes a return value of `main`

**MC3.** Why should you catch exceptions by `const` reference (e.g., `catch (const std::exception& e)`)?

- A. It's required by the compiler
- B. It avoids slicing derived exception types and avoids copying
- C. It makes the catch faster
- D. It's the only legal syntax

**MC4.** Which class is the typical base of the C++ standard exception hierarchy?

- A. `std::error`
- B. `std::runtime_error`
- C. `std::exception`
- D. `std::throwable`

**Short Answer.** List three standard library exceptions and briefly describe when each is used.

**Short Answer.** Explain what "stack unwinding" means and why it matters for RAII.

**Code Analysis.** What is the output?

```cpp
try {
    try {
        throw runtime_error("inner");
    }
    catch (const logic_error& e) {
        cout << "A: " << e.what() << "\n";
    }
}
catch (const exception& e) {
    cout << "B: " << e.what() << "\n";
}
```

**Code Writing.** Write a custom exception class `NegativeAgeException` that inherits from `std::invalid_argument`. Then write a `setAge(int a)` function that throws it when `a < 0`.

**Code Writing.** Write a program that tries to open a file (simulated — just check if a flag is false), throws a `FileNotFoundException` (custom, inheriting from `std::runtime_error`), and catches it with a useful message.

---

## 10. Templates (Function & Class Basics)

### Definition

**Templates** are C++'s mechanism for **generic programming** — writing code that works with any type, resolved at compile time. The compiler generates a concrete version of the template for each type used.

### Key Concepts

- **Function template** syntax: `template <typename T> T funcName(T a, T b) { ... }`
- **Class template** syntax: `template <typename T> class Box { T value; ... };`
- `typename` and `class` are interchangeable in template parameter lists.
- Instantiation happens at compile time — each type generates its own code.
- Templates usually live entirely in header files (definitions must be visible).

### Code Example — Function Template

```cpp
template <typename T>
T maxOf(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    cout << maxOf(3, 7) << "\n";          // int version
    cout << maxOf(3.14, 2.71) << "\n";    // double version
    cout << maxOf(string("apple"),
                  string("banana")) << "\n";  // string version
}
```

### Code Example — Class Template

```cpp
template <typename T>
class Stack {
    T data[100];
    int top = -1;
public:
    void push(T val) { data[++top] = val; }
    T pop() { return data[top--]; }
    bool empty() const { return top < 0; }
};

int main() {
    Stack<int> si;
    si.push(42);

    Stack<string> ss;
    ss.push("hello");
}
```

### Practice Questions

**MC1.** When are templates instantiated into actual code?

- A. At link time
- B. At compile time, once per distinct type used
- C. At run time, the first time they are called
- D. At program startup

**MC2.** Which is a correct function template declaration?

- A. `template T maxOf<T>(T a, T b);`
- B. `template <typename T> T maxOf(T a, T b);`
- C. `template<T> T maxOf(T a, T b);`
- D. `generic T maxOf(T a, T b);`

**Short Answer.** Why do template definitions typically live in header files instead of `.cpp` files?

**Code Writing.** Write a function template `swapVals` that swaps two values of any type by reference.

---

## 11. Smart Pointers (Modern C++ Memory Management)

### Definition

**Smart pointers** are objects that own and manage a dynamically allocated resource and automatically release it when they go out of scope — eliminating most manual `new`/`delete` bugs.

### Key Concepts

- Three main smart pointers (from `<memory>`):
  - **`std::unique_ptr<T>`** — sole owner, cannot be copied, can be moved. The default choice.
  - **`std::shared_ptr<T>`** — reference-counted shared ownership.
  - **`std::weak_ptr<T>`** — non-owning reference to a `shared_ptr`, used to break cycles.
- Prefer `std::make_unique<T>(args)` and `std::make_shared<T>(args)` over raw `new`.
- Smart pointers are an application of **RAII**: resource lifetime tied to object lifetime.
- Raw `new`/`delete` in modern C++ code is a code smell.

### Code Example

```cpp
#include <memory>

class Widget {
public:
    Widget()  { cout << "Widget ctor\n"; }
    ~Widget() { cout << "Widget dtor\n"; }
    void use() { cout << "using widget\n"; }
};

int main() {
    {
        auto u = std::make_unique<Widget>();  // sole owner
        u->use();
    }   // Widget auto-deleted here — no 'delete' needed

    {
        auto s1 = std::make_shared<Widget>();
        {
            auto s2 = s1;     // ref count = 2
        }                     // ref count = 1
    }                         // ref count = 0 — Widget destroyed
}
```

### Practice Questions

**MC1.** Which smart pointer represents **exclusive** ownership?

- A. `std::shared_ptr`
- B. `std::weak_ptr`
- C. `std::unique_ptr`
- D. `std::auto_ptr`

**MC2.** What is the main benefit of smart pointers over raw pointers?

- A. They're faster
- B. They automatically release the managed resource when they go out of scope
- C. They can never be null
- D. They allow multiple inheritance

**Short Answer.** What is the difference between `std::unique_ptr` and `std::shared_ptr` in one sentence?

---

## 12. RAII (Resource Acquisition Is Initialization)

### Definition

**RAII** is the C++ idiom of binding the lifetime of a resource (memory, file handle, lock, socket) to the lifetime of a stack-allocated object. Resources are acquired in the constructor and released in the destructor.

### Key Concepts

- RAII makes exception safety automatic — destructors run during stack unwinding.
- Smart pointers, `std::lock_guard`, `std::fstream`, and `std::vector` are all RAII types.
- Before RAII: manual `new`/`delete`, easy to leak on early return or exception.
- With RAII: leak-free by default.

### Code Example

```cpp
class FileHandle {
    FILE* f;
public:
    FileHandle(const char* name, const char* mode) {
        f = fopen(name, mode);
        if (!f) throw runtime_error("open failed");
    }
    ~FileHandle() {
        if (f) fclose(f);      // always closed, even on exception
    }
    FILE* get() { return f; }
};

void process() {
    FileHandle fh("data.txt", "r");
    // ... even if something throws here, fclose() runs automatically
}
```

### Practice Questions

**MC1.** RAII ties the lifetime of a resource to:

- A. The program's main thread
- B. The lifetime of an object (typically stack-allocated)
- C. A garbage collector
- D. A manually managed lifetime counter

**Short Answer.** Why does RAII make exception-safe code easier to write?

---

# Putting It All Together — Scenario Questions

These combine multiple topics and are typical of a comprehensive final or Exam 3.

**Scenario 1.** You are designing a `Shape` hierarchy with `Circle`, `Square`, and `Triangle`. All shapes need an `area()` method and a virtual destructor. An invalid dimension (negative) should throw a custom exception.

- Write the abstract `Shape` class.
- Write one derived class showing proper exception handling in its constructor.
- Show how `main()` uses smart pointers to manage a collection of shapes polymorphically.

**Scenario 2.** Write a `Stack<T>` template class that throws `std::out_of_range` on pop-when-empty. Demonstrate using it with `int` and `string`.

**Scenario 3.** Explain what a **virtual destructor**, **RAII**, and **smart pointers** have in common — what problem do they collectively solve? Write a short paragraph.

---

# Extra Practice — Mixed Formats by Topic

Use this section as a sample-question buffet. Each item shows a format the exam might use; topics are repeated across formats on purpose.

## Inheritance & Access Control

**Short Answer 1.** In one sentence each, describe what `public`, `protected`, and `private` _inheritance_ (the colon, not the member access) does to inherited members.

**Short Answer 2.** What is the order in which constructors and destructors execute for the hierarchy `A → B → C` when a `C` object is created and then destroyed?

**Trace the Output.**

```cpp
class A { public: A(){cout<<"A ";} ~A(){cout<<"~A ";} };
class B : public A { public: B(){cout<<"B ";} ~B(){cout<<"~B ";} };
class C : public B { public: C(){cout<<"C ";} ~C(){cout<<"~C ";} };

int main() { C c; }
```

**Find the Bug.**

```cpp
class Base {
private:
    int secret;
public:
    Base(int s) : secret(s) {}
};

class Derived : public Base {
public:
    Derived(int s) : Base(s) {}
    void reveal() { cout << secret; }   // <-- bug?
};
```

What's wrong, and what's the minimum fix?

**Fill in the Blank.** A class member declared \***\*\_\_\*\*** is accessible inside the class and its derived classes, but not from outside.

---

## Abstract Classes & Pure Virtuals

**Short Answer 1.** What makes a class "abstract" in C++?

**Short Answer 2.** Can an abstract class have a constructor? If so, what is it for, given that you can't instantiate the class directly?

**Trace the Output / Predict the Error.**

```cpp
class Animal {
public:
    virtual void speak() = 0;
};

int main() {
    Animal a;          // Line 1
    Animal* p;         // Line 2
    p->speak();        // Line 3
}
```

Identify which lines compile, which don't, and which is undefined behavior.

**Code Snippet.** Convert the following concrete class into an abstract base class with `area()` made pure virtual:

```cpp
class Shape {
public:
    double area() { return 0; }
};
```

**Compare/Contrast.** What's the difference between an _abstract class_ and an _interface_? (C++ doesn't have a dedicated `interface` keyword — what's the convention?)

---

## Virtual Destructors

**Short Answer 1.** Why does a base class destructor often need to be virtual?

**Short Answer 2.** Is there ever a reason **not** to make a destructor virtual? Briefly explain.

**Find the Bug.**

```cpp
class Animal {
public:
    ~Animal() { cout << "Animal\n"; }
};
class Dog : public Animal {
    int* tricks;
public:
    Dog() { tricks = new int[10]; }
    ~Dog() { delete[] tricks; cout << "Dog\n"; }
};

int main() {
    Animal* a = new Dog();
    delete a;
}
```

What prints, what leaks, and how do you fix it?

**Multiple Choice.** Adding `virtual` to a destructor:

- A. Slows the class down significantly
- B. Adds a vtable pointer to instances of the class (small memory cost)
- C. Prevents derived classes from defining their own destructor
- D. Is required for all classes

---

## Polymorphism & Dynamic Dispatch

**Short Answer 1.** Define **late binding** in your own words.

**Short Answer 2.** Why doesn't polymorphism work when you pass an object **by value**?

**Trace the Output.**

```cpp
class Base {
public:
    virtual void greet() { cout << "Hello from Base\n"; }
};
class Derived : public Base {
public:
    void greet() override { cout << "Hello from Derived\n"; }
};

void test1(Base b)  { b.greet(); }
void test2(Base& b) { b.greet(); }
void test3(Base* b) { b->greet(); }

int main() {
    Derived d;
    test1(d);
    test2(d);
    test3(&d);
}
```

**Code Writing.** Write a function `printAll(vector<Shape*> shapes)` that calls `area()` on every shape polymorphically.

**Fill in the Blank.** The hidden table of function pointers used to implement runtime polymorphism is called the \***\*\_\_\*\***.

---

## Static Members

**Short Answer.** Why can't a static method access a class's non-static data members directly?

**Code Snippet.** Add the missing line of code so this compiles and links:

```cpp
class Counter {
    static int total;
public:
    Counter() { ++total; }
    static int getTotal() { return total; }
};

// MISSING LINE HERE

int main() {
    Counter a, b;
    cout << Counter::getTotal();
}
```

**Multiple Choice.** Which of the following can a `static` method access?

- A. Non-static data members of the class
- B. The `this` pointer
- C. Other static members of the class
- D. Both A and C

---

## Composition vs. Inheritance

**Short Answer 1.** Read each phrase and label it as **composition** ("has-a") or **inheritance** ("is-a"):

- A `Library` and `Book`
- A `SportsCar` and a `Car`
- A `Computer` and a `CPU`
- A `Square` and a `Shape`

**Short Answer 2.** What's the principle "favor composition over inheritance" really warning you about?

**Code Writing.** Refactor this inheritance into composition:

```cpp
class Engine {
public:
    void start() { /* ... */ }
};

class Car : public Engine {  // <-- not really an "is-a"
public:
    void drive() { start(); }
};
```

---

## Multiple Inheritance & Diamond

**Short Answer.** In one sentence, what is the diamond problem?

**Trace the Output.**

```cpp
class A { public: int x = 1; };
class B : public A { };
class C : public A { };
class D : public B, public C { };

int main() {
    D d;
    cout << d.x;       // What happens here?
}
```

**Code Snippet — Add the Fix.** Modify the inheritance above so `d.x` is unambiguous and only one copy of `A` exists in `D`.

**Multiple Choice.** Which statement about virtual inheritance is true?

- A. It eliminates all forms of method overriding
- B. It ensures only one copy of a shared base class exists in the derived hierarchy
- C. It is required for all multiple inheritance
- D. It's a synonym for `final`

---

## Exception Handling

**Short Answer 1.** What is the difference between `throw` and `throws`? (Trick question — only one exists in C++. Which?)

**Short Answer 2.** What does `e.what()` return, and what type is it?

**Short Answer 3.** Why is it considered bad practice to catch exceptions by value (`catch (std::exception e)`) instead of by const reference?

**Short Answer 4.** What is the difference between `std::logic_error` and `std::runtime_error` conceptually?

**Trace the Output.**

```cpp
try {
    throw 42;
}
catch (const char*) { cout << "string\n"; }
catch (double)      { cout << "double\n"; }
catch (int)         { cout << "int\n"; }
catch (...)         { cout << "any\n"; }
```

**Trace the Output — Order Matters.**

```cpp
try {
    throw runtime_error("oops");
}
catch (const exception& e) { cout << "exception\n"; }
catch (const runtime_error& e) { cout << "runtime\n"; }
```

What prints? What's the lesson about catch ordering?

**Find the Bug.**

```cpp
double safeDivide(double a, double b) {
    try {
        if (b == 0) throw "div zero";
        return a / b;
    }
    catch (exception& e) {
        cout << e.what();
        return 0;
    }
}
```

This compiles but `catch` never fires. Why?

**Code Writing 1.** Write a function `parseAge(const string& s)` that converts the string to an `int` and throws a `std::invalid_argument` if the value is negative.

**Code Writing 2.** Build a custom exception class `OutOfStockException` that inherits from `std::runtime_error`, stores the product name, and exposes a `getProduct()` method.

**Code Writing 3.** Write a try/catch block that handles three different exception types: `std::out_of_range`, `std::invalid_argument`, and a catch-all `std::exception` — in the correct order.

**Conceptual / Industry Question.** Many production C++ codebases use exceptions, but some (like LLVM and Google's style guide) discourage them. Give one reasonable argument for each side.

---

## Templates

**Short Answer 1.** Why must template _definitions_ live in header files?

**Short Answer 2.** What's the difference between `template <typename T>` and `template <class T>`?

**Trace the Output.**

```cpp
template <typename T>
T mystery(T a, T b) { return a + b; }

int main() {
    cout << mystery(2, 3) << "\n";
    cout << mystery(2.5, 3.5) << "\n";
    cout << mystery(string("foo"), string("bar")) << "\n";
}
```

**Find the Bug.**

```cpp
template <typename T>
T addThem(T a, T b) { return a + b; }

int main() {
    cout << addThem(3, 4.5);   // <-- compiler complains, why?
}
```

**Code Writing 1.** Write a function template `printArray(T arr[], int size)` that prints any array.

**Code Writing 2.** Sketch a template class `Pair<T, U>` that holds two values of possibly different types and has a `swap()` method that swaps them — wait, can it? Why or why not?

---

## Smart Pointers & RAII

**Short Answer 1.** What does "RAII" stand for, and what problem does it solve?

**Short Answer 2.** Why can't `std::unique_ptr` be copied? What can you do instead?

**Short Answer 3.** When would you reach for a `std::weak_ptr`?

**Multiple Choice.** Which of the following code snippets is a memory leak?

- A. `auto p = std::make_unique<int>(5);`
- B. `int* p = new int(5);` (no delete shown)
- C. `auto p = std::make_shared<int>(5);`
- D. `std::vector<int> v(5);`

**Find the Bug.**

```cpp
void process() {
    Widget* w = new Widget();
    if (!w->isReady()) return;     // <-- problem
    w->use();
    delete w;
}
```

How does converting to `std::unique_ptr` fix it?

**Code Writing.** Rewrite this raw-pointer code using `std::unique_ptr`:

```cpp
Shape* s = new Circle(3.0);
s->draw();
delete s;
```

**Conceptual Question.** Modern C++ guidance says: "If you're writing `new` or `delete`, you're probably doing it wrong." Why?

---

## Vocabulary & Matching (Quick-Hit Style)

These are the kind of low-stakes points that pad an exam without much grading effort.

**Define each in one short sentence:**

1. Encapsulation
2. Polymorphism
3. Inheritance
4. Abstraction
5. Composition
6. Virtual function
7. Pure virtual function
8. Abstract class
9. Friend
10. Static member
11. Template
12. Exception
13. RAII
14. Slicing
15. vtable

**Matching.** Match each term to the closest description.

| Term          | Description                                              |
| ------------- | -------------------------------------------------------- |
| 1. `virtual`  | A. Marks a method as the default polymorphic version     |
| 2. `override` | B. Compiler-enforced check that you're really overriding |
| 3. `final`    | C. Prevents further overriding or inheritance            |
| 4. `= 0`      | D. Makes a virtual function pure                         |
| 5. `friend`   | E. Grants access to private members of another class     |
| 6. `throw`    | F. Signals that an exceptional situation has occurred    |
| 7. `catch`    | G. Handles a thrown exception                            |
| 8. `template` | H. Begins a generic definition                           |

---

## "What Would You Do?" — Design Judgment

These reward students who _think_ about design, not just memorize syntax.

**Q1.** You inherit a project where every class derives from a single `GodObject` base. Why is this a problem?

**Q2.** A teammate wraps every line in a try/catch block. Why is this overkill, and where should exceptions actually live?

**Q3.** You see this in code review:

```cpp
class Widget { /* ... */ };
Widget* makeWidget() { return new Widget(); }
```

Suggest a one-line improvement and explain it.

**Q4.** A junior dev says "I'll just make every member `public` so I don't have to write getters and setters." What's your one-paragraph response?

**Q5.** A class manages a `FILE*`. The destructor closes it. The class doesn't define a copy constructor. What's the bug waiting to happen?

---

# Master Topic Checklist

Use this right before the exam. If you can't explain any line below in one sentence plus a code example, revisit that section.

- [ ] Inheritance syntax and access specifiers
- [ ] Construction/destruction order in a hierarchy
- [ ] Abstract classes and pure virtual functions
- [ ] Why `override` and `final` exist
- [ ] Virtual destructors — when and why
- [ ] `protected` access
- [ ] Runtime polymorphism and object slicing
- [ ] Static members and static methods
- [ ] Composition vs. inheritance ("has-a" vs. "is-a")
- [ ] Multiple inheritance and the diamond problem
- [ ] `virtual` inheritance as the diamond solution
- [ ] `try`, `throw`, `catch` basics
- [ ] The `std::exception` hierarchy
- [ ] Writing custom exception classes
- [ ] Stack unwinding and exception safety
- [ ] Function templates
- [ ] Class templates
- [ ] `std::unique_ptr` vs. `std::shared_ptr`
- [ ] RAII as an idiom

---

_Good luck. If you've worked through every code example and answered every question in this guide, you're in great shape._
