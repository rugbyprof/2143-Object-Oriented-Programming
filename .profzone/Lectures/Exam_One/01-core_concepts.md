# Core Concepts of OOP (C++)

OOP is how we stop writing “code soup” and start writing **systems**. The big three your students need to own are:

- **Encapsulation**
- **Inheritance**
- **Polymorphism**

And then we’ll connect that straight into why even “simple” structures like **stack/queue** deserve a class.

---

## 1) Encapsulation  
> **Hide the guts. Expose a clean interface. Keep invariants safe.**

Encapsulation = put **data + the functions that manage it** inside a class, and restrict direct access to internal state.

### Why it matters:
- Prevents “creative” misuse (a.k.a. students)
- Enforces rules (invariants)
- Makes changes safer (implementation can evolve)

### C++ Example (private state + safe methods)

```cpp
#include <string>
#include <stdexcept>

class BankAccount {
private:
    std::string owner;
    double balance;  // hidden internal state

public:
    BankAccount(const std::string& ownerName, double starting = 0.0)
        : owner(ownerName), balance(starting) {}

    void deposit(double amount) {
        if (amount <= 0) throw std::invalid_argument("Deposit must be positive.");
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) throw std::invalid_argument("Withdraw must be positive.");
        if (amount > balance) throw std::runtime_error("Insufficient funds.");
        balance -= amount;
    }

    double getBalance() const {
        return balance;
    }
};
```

Key point: `balance` is **private**, so nobody can do `account.balance = -999;` and ruin your day.

---

## 2) Inheritance  
> **Reuse existing code by extending a base type (“is-a” relationship).**

Inheritance lets a derived class **reuse** and **specialize** a base class.

### Why it matters:
- Reduces duplication
- Models hierarchies naturally
- Enables polymorphism (next section)

### C++ Example (base + derived)

```cpp
#include <string>

class Animal {
public:
    virtual std::string speak() const {
        return "Some sound";
    }

    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    std::string speak() const override {
        return "Woof";
    }
};
```

`Dog` **is an** `Animal`. It inherits the interface and can override behavior.

---

## 3) Polymorphism  
> **Same interface, different behavior** (chosen at runtime via virtual dispatch).

Polymorphism means you can treat different derived objects as the same base type, and when you call a virtual method, the **right** version runs.

### Why it matters:
- Cleaner code (no giant `if(type==...)` ladders)
- Extensible designs (add new derived types without rewriting loops)
- Decouples “what” from “how”

### C++ Example (runtime polymorphism)

```cpp
#include <iostream>
#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>());
    animals.push_back(std::make_unique<Animal>());

    for (const auto& a : animals) {
        std::cout << a->speak() << "\n";
    }
}
```

Output:
```
Woof
Some sound
```

Same call: `speak()`  
Different behavior depending on actual object type. That’s polymorphism.

---

# Segue: Why Use a Class for a Stack or Queue?

Because otherwise it’s not a stack/queue — it’s a container **cosplaying** as one.

## The Problem With “Just Use a Vector”
You *can* do:

```cpp
std::vector<int> s;
s.push_back(10);
s.push_back(20);
s.pop_back();
```

But nothing stops this:

```cpp
s.insert(s.begin(), 999);  // Congrats, you invented chaos.
s[0] = -12345;             // Your “stack” is now emotional damage.
```

The point of a Stack/Queue is not “it holds stuff.”
It’s: **it enforces a behavioral contract**.

---

# A Proper Stack Class (Encapsulation + Contract)

```cpp
#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
private:
    std::vector<T> items;

public:
    void push(const T& value) {
        items.push_back(value);
    }

    void pop() {
        if (items.empty()) throw std::runtime_error("Pop from empty stack.");
        items.pop_back();
    }

    T& top() {
        if (items.empty()) throw std::runtime_error("Top of empty stack.");
        return items.back();
    }

    const T& top() const {
        if (items.empty()) throw std::runtime_error("Top of empty stack.");
        return items.back();
    }

    bool empty() const {
        return items.empty();
    }

    size_t size() const {
        return items.size();
    }
};
```

### What you gained (and why it’s exam-worthy):

✅ **Encapsulation:** internal structure hidden (`items` is private)  
✅ **Correctness:** only stack operations allowed (`push/pop/top`)  
✅ **Maintainability:** you can swap `vector` for `deque` later with minimal changes  
✅ **Clarity:** callers think in *stack operations*, not container hacks  
✅ **Reusability:** template works for any type `T`

---

# Queue Class (same story, different behavior)

```cpp
#include <deque>
#include <stdexcept>

template <typename T>
class Queue {
private:
    std::deque<T> items;

public:
    void enqueue(const T& value) {
        items.push_back(value);
    }

    void dequeue() {
        if (items.empty()) throw std::runtime_error("Dequeue from empty queue.");
        items.pop_front();
    }

    T& front() {
        if (items.empty()) throw std::runtime_error("Front of empty queue.");
        return items.front();
    }

    bool empty() const {
        return items.empty();
    }

    size_t size() const {
        return items.size();
    }
};
```

---

# The “Why OOP Here?” Summary (the punchline)

Using a class for Stack/Queue turns a raw container into an **ADT (Abstract Data Type)**:

- **Encapsulation:** protects the internal representation
- **Invariants:** prevents illegal operations and states
- **Swappable implementations:** change internals without changing usage
- **Better APIs:** clearer, safer, easier to test

In short:

> A `vector` can *store* stack data…  
> A `Stack` class can *be* a stack.
