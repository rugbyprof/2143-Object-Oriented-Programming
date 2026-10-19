# C++ Templates: Writing Code That Works with Different Types

Templates let you write a function or class once and use it with different types. You will begin with templates you already recognize, build your own, and then compare them with runtime polymorphism.

## 1. You Have Probably Already Used Templates

Consider these declarations:

```cpp
#include <string>
#include <vector>

std::vector<int> scores;
std::vector<std::string> names;
```

`std::vector` is a **class template**. The type inside the angle brackets tells it what kind of element to store.

```cpp
std::vector<int>
//          ^^^
//       Type argument
```

`std::vector<int>` and `std::vector<std::string>` provide the same general container operations, but store different element types.

Each is a distinct type:

```cpp
std::vector<int> numbers;
std::vector<double> measurements;

// numbers = measurements;  // Error: incompatible vector types.
```

**Think about it:** What stays the same between these vectors? What changes?

## 2. Use a Function Template to Eliminate Duplication

Suppose you need a function that returns the larger of two values:

```cpp
int Larger(int first, int second) {
    return first > second ? first : second;
}

double Larger(double first, double second) {
    return first > second ? first : second;
}
```

Both functions follow the same algorithm. Only their types differ.

You can express that shared algorithm with a **function template**:

```cpp
template <typename T>
T Larger(T first, T second) {
    return first > second ? first : second;
}
```

`T` is a **template type parameter**. It represents a type that will be selected at compile time.

```cpp
int score = Larger(85, 92);
double temperature = Larger(72.5, 68.3);
```

The compiler uses the template to instantiate the needed functions.

You may also encounter this spelling:

```cpp
template <class T>
```

Here, `class` means the same thing as `typename`. It does not restrict `T` to class types; `int` and `double` still work.

**Try it:** Call `Larger()` with two `std::string` objects. What determines which string is larger?

## 3. Understand Type Deduction

Usually, the compiler determines `T` from your function arguments:

```cpp
Larger(4, 9);       // T is int.
Larger(4.5, 9.2);   // T is double.
```

This process is called **template argument deduction**.

What happens here?

```cpp
// Larger(4, 9.2);
```

The first argument suggests `T` should be `int`. The second suggests it should be `double`. The compiler cannot deduce one consistent type for this template.

You can specify the type explicitly:

```cpp
Larger<double>(4, 9.2);
```

Now both parameters are `double`, and `4` is converted accordingly.

You can also make the argument types match:

```cpp
Larger(4.0, 9.2);
Larger(static_cast<double>(4), 9.2);
```

**Check your understanding:** How does `Larger<double>(4, 9)` differ from `Larger(4, 9)`?

## 4. Create a Class Template

A class template lets you reuse a class design with different types.

```cpp
template <typename T>
class Box {
public:
    explicit Box(const T& value)
        : value_(value) {}

    const T& Get() const {
        return value_;
    }

    void Set(const T& value) {
        value_ = value;
    }

private:
    T value_;
};
```

Create objects:

```cpp
Box<int> lives{3};
Box<std::string> player_name{"Thorin"};

lives.Set(5);
player_name.Set("Malakai");
```

Your existing OOP principles still apply:

- The data member is private.
- Public methods provide access to the object.
- The constructor initializes the object.
- The template parameter determines the stored type.

In `Box<int>`, `value_` is an `int`. In `Box<std::string>`, it is a `std::string`.

**Try it:** Add this method:

```cpp
T Replace(const T& new_value);
```

It should store the new value and return the old one.

## 5. Use More Than One Type Parameter

A template can accept multiple types:

```cpp
template <typename Key, typename Value>
class Entry {
public:
    Entry(const Key& key, const Value& value)
        : key_(key), value_(value) {}

    const Key& GetKey() const {
        return key_;
    }

    const Value& GetValue() const {
        return value_;
    }

private:
    Key key_;
    Value value_;
};
```

You choose each type separately:

```cpp
Entry<std::string, int> player_score{"Thorin", 100};
Entry<int, std::string> student{1042, "Jordan"};
```

Notice that template parameter names do not have to be single letters. `Key` and `Value` explain their roles more clearly than `T` and `U`.

You will see the same idea in the standard library:

```cpp
#include <map>
#include <utility>

std::pair<std::string, int> score{"Thorin", 100};
std::map<std::string, int> scores;
```

**Think about it:** What flexibility would you lose if `Entry` used one type parameter for both its key and value?

## 6. Recognize What a Template Requires

A template does not automatically work with every type.

Look again at `Larger()`:

```cpp
template <typename T>
T Larger(T first, T second) {
    return first > second ? first : second;
}
```

The expression below must be valid for the chosen type:

```cpp
first > second
```

Consider this class:

```cpp
struct Player {
    std::string name;
    int score;
};
```

This call fails because you have not defined how to compare two players:

```cpp
// Larger(Player{"A", 10}, Player{"B", 20});
```

You can define that comparison:

```cpp
bool operator>(const Player& left, const Player& right) {
    return left.score > right.score;
}
```

Now the template can compare players by score:

```cpp
Player winner = Larger(
    Player{"Thorin", 85},
    Player{"Malakai", 92}
);
```

A template’s implementation establishes requirements on its type arguments. You need to understand those requirements to use the template correctly.

**Check your understanding:** If a template calls `item.Print()`, what must the chosen type provide?

## 7. Pass a Compile-Time Value to a Template

Template parameters can represent values as well as types.

```cpp
#include <array>
#include <cstddef>

template <typename T, std::size_t N>
class FixedInventory {
public:
    T& At(std::size_t index) {
        return items_.at(index);
    }

    constexpr std::size_t Capacity() const {
        return N;
    }

private:
    std::array<T, N> items_{};
};
```

Use it like this:

```cpp
FixedInventory<std::string, 4> inventory;

inventory.At(0) = "Longsword";
inventory.At(1) = "Shield";
```

Here:

- `T` is a **type template parameter**.
- `N` is a **non-type template parameter**.
- `4` is a compile-time value that determines the inventory’s capacity.

The capacity is also part of the resulting type:

```cpp
FixedInventory<int, 4> small;
FixedInventory<int, 8> large;

// small = large;  // Error: these are different types.
```

Compare this with passing a capacity to a constructor. A constructor argument can be chosen at runtime. The template argument `N` must be known at compile time.

**Try it:** Create a fixed inventory that stores three `double` values.

## 8. Supply a Default Template Argument

A template can provide a default type:

```cpp
template <typename T = int>
class Counter {
public:
    void Increment() {
        ++value_;
    }

    T Value() const {
        return value_;
    }

private:
    T value_{};
};
```

You can accept the default or supply another type:

```cpp
Counter<> ordinary;
Counter<long long> large;

ordinary.Increment();
large.Increment();
```

`Counter<>` uses `int`.

Remember the distinction:

```cpp
template <typename T = int>  // Default template type argument.
```

```cpp
void Print(int count = 1);   // Default function argument.
```

The first supplies a type. The second supplies a value for a function call.

**Think about it:** Would `Counter<std::string>` support `Increment()`? Examine the operation used inside that method.

## 9. Put Template Definitions Where the Compiler Can See Them

In ordinary projects, place your template definitions in headers. The compiler generally needs to see the definitions when it instantiates the template.

You can define methods inside the class, as you have already seen, or below it in the same header:

```cpp
// Box.h
#pragma once

template <typename T>
class Box {
public:
    explicit Box(const T& value);
    const T& Get() const;

private:
    T value_;
};

template <typename T>
Box<T>::Box(const T& value)
    : value_(value) {}

template <typename T>
const T& Box<T>::Get() const {
    return value_;
}
```

Look carefully at the out-of-class method definition:

```cpp
template <typename T>
const T& Box<T>::Get() const
```

You must declare the template parameter again and identify the class as `Box<T>`.

Moving these definitions into an ordinary `.cpp` file can cause linker errors when other source files try to use the template. Explicit instantiation can support other arrangements, but keeping definitions in the header is the appropriate starting point.

**Check your understanding:** Why does the compiler need more than the declaration of `Box<T>::Get()` when generating code for a new instantiation?

## 10. Compare Templates with Runtime Polymorphism

Templates and virtual functions both let you write code that works with different types, but they do so differently.

| Templates                                                      | Virtual functions                                                     |
| -------------------------------------------------------------- | --------------------------------------------------------------------- |
| Template arguments are selected at compile time.               | Virtual dispatch selects an override at runtime.                      |
| Types do not need a shared base class.                         | Runtime dispatch uses a shared base interface.                        |
| Different template arguments produce different instantiations. | Different derived objects can be accessed through the same base type. |

### Using a template

```cpp
#include <iostream>

struct Fighter {
    void Attack() {
        std::cout << "Sword swing!\n";
    }
};

struct Mage {
    void Attack() {
        std::cout << "Fireball!\n";
    }
};

template <typename CharacterType>
void TakeTurn(CharacterType& character) {
    character.Attack();
}
```

Both types work because both provide the required operation:

```cpp
Fighter fighter;
Mage mage;

TakeTurn(fighter);
TakeTurn(mage);
```

`Fighter` and `Mage` do not need to inherit from a common class.

### Using runtime polymorphism

Here is a separate design using a base class:

```cpp
class Character {
public:
    virtual ~Character() = default;
    virtual void Attack() = 0;
};

class Fighter : public Character {
public:
    void Attack() override {
        std::cout << "Sword swing!\n";
    }
};

class Mage : public Character {
public:
    void Attack() override {
        std::cout << "Fireball!\n";
    }
};

void TakeTurn(Character& character) {
    character.Attack();
}
```

The function receives a `Character&`. The actual object determines which `Attack()` runs.

**Think about it:** Your battle engine needs to store different character classes together and choose the next attacker during gameplay. How would a common base interface help?

Templates and virtual functions can also work together. For example, `std::vector<std::unique_ptr<Character>>` uses templates to store objects accessed through a runtime-polymorphic interface.

## 11. Express Requirements with C++20 Concepts

Earlier, you discovered template requirements by examining the operations in the function body. C++20 **concepts** let you state some requirements explicitly.

```cpp
#include <concepts>

template <std::integral T>
T DoubleValue(T value) {
    return value * 2;
}
```

`std::integral` restricts this template to integral types:

```cpp
DoubleValue(5);       // Valid.
// DoubleValue(2.5);  // Error: double does not satisfy std::integral.
```

You can also define a concept:

```cpp
template <typename T>
concept AttackCapable = requires(T& character) {
    character.Attack();
};

template <AttackCapable T>
void TakeTurn(T& character) {
    character.Attack();
}
```

`AttackCapable` checks whether calling `Attack()` on a `T&` is valid.

It does not check whether the attack makes sense, deals the correct damage, or follows your game rules. You still need to design and test that behavior.

**Try it:** Define a `Printable` concept that requires an object to have a callable `Print()` method.

## 12. Put It Together: Build a History Class

Implement the following class template:

```cpp
#include <cstddef>
#include <vector>

template <typename T>
class History {
public:
    void Add(const T& item);
    const T& Latest() const;
    std::size_t Size() const;

private:
    std::vector<T> items_;
};
```

Your class should support different kinds of history:

```cpp
History<int> damage_history;
History<std::string> battle_messages;
History<AttackResult> attack_history;
```

For the final example, use the `AttackResult` type from your battle project.

Complete these tasks:

1. Implement all three methods in the header.
2. Decide what `Latest()` should do when the history is empty, and implement that behavior.
3. Demonstrate your class with at least two different type arguments.
4. Explain why its template definitions belong in the header.
5. Explain why a template fits this class.
6. Explain whether a virtual base class would help this design, and why.

As you work, ask yourself: **Does the behavior stay the same while the stored type changes?** That is a strong indication that a template may be useful.