<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: false
id: L07-Templates
name: L07-Templates
title: NO TITLE
description: NO DESCRIPTION
category: Lectures
date_due:
  month: '11'
  day: '02'
  year: 2026
  hour: 9
```

</details>

# C++ Templates: Writing Code That Works with Different Types

Templates let you write a function or class once and use it with different types. You will begin with templates you already recognize, build your own, and then compare them with runtime polymorphism.

## Example Code Files

Each example compiles and runs on its own. Read them in order: each file adds one idea to the previous ones. Every file ends with a **Try it** block, so work through those as you go.

```bash
g++ -std=c++20 template_01.cpp -o template_01 && ./template_01
```

| File                               | Topic                                         | New ideas                                                     | README section |
| ---------------------------------- | --------------------------------------------- | ------------------------------------------------------------- | -------------- |
| [template_01.cpp](template_01.cpp) | From copy/paste to a function template        | `template <typename T>`, deduction, `Larger<double>(...)`     | 2, 3           |
| [template_02.cpp](template_02.cpp) | References, several types, requirements       | `T&` vs `const T&`, `<typename A, typename B>`, `operator>`   | 3, 6           |
| [template_03.cpp](template_03.cpp) | Your first class template                     | `Box<T>`, encapsulation, CTAD (`Box b{42};`)                  | 4              |
| [template_04.cpp](template_04.cpp) | Two type parameters, out-of-class definitions | `Entry<Key, Value>`, `Entry<K, V>::Method()`, friend `<<`     | 5, 9           |
| [template_05.cpp](template_05.cpp) | Non-type parameters and defaults              | `Inventory<T, Capacity>`, `Counter<T = int>`                  | 7, 8           |
| [template_06.cpp](template_06.cpp) | Building a generic container                  | `Stack<T>`, composition, exceptions                           | 4, 12          |
| [template_07.cpp](template_07.cpp) | An interface without inheritance              | Calling methods on `T`, "duck typing"                         | 6, 10          |
| [template_08.cpp](template_08.cpp) | Passing behavior as a template parameter      | Functors, lambdas, `SortedList<T, Compare>`, Strategy         | Edge Cases     |
| [template_09.cpp](template_09.cpp) | Specialization                                | Full and partial specialization, overload vs specialize       | Edge Cases     |
| [template_10.cpp](template_10.cpp) | Templates and inheritance together            | `vector<unique_ptr<Base>>`, factory `Spawn<Derived>()`        | 10             |
| [template_11.cpp](template_11.cpp) | Reusable behavior with base-class templates   | CRTP mixins, per-type `static` members                        | 10             |
| [template_12.cpp](template_12.cpp) | Concepts                                      | `concept`, `requires`, `template <Scorable T>`, `auto` params | 11             |
| [template_13.cpp](template_13.cpp) | Capstone: a generic battle roster             | Everything above in one design                                | 12             |

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

## Edge Cases

The current `Larger` already compiles for vectors, but it doesn't compare sums. `std::vector` has its own `operator>`, and it compares **lexicographically**, the way strings are compared: element by element until two elements differ.

```cpp
vector<int> a = {9, 1};      // sum 10
vector<int> b = {1, 2, 50};  // sum 53
Larger(a, b);                // returns a, because 9 > 1
```

So you need to say what "larger" means for a vector. There are three common ways to do it.

### 1. Overload `Larger` for vectors (recommended for teaching)

Add a second template that only accepts vectors. When both templates match, the compiler picks the more specialized one, so `vector<int>` arguments go to this version and everything else goes to the generic one.

```cpp
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

template <typename T>
T Larger(T first, T second) {
    return first > second ? first : second;
}

template <typename T>
vector<T> Larger(const vector<T>& first, const vector<T>& second) {
    T sumFirst = accumulate(first.begin(), first.end(), T{});
    T sumSecond = accumulate(second.begin(), second.end(), T{});
    return sumFirst > sumSecond ? first : second;
}

int main() {
    vector<int> a = {9, 1};
    vector<int> b = {1, 2, 50};

    cout << Larger(3, 7) << endl;           // generic version: 7

    vector<int> big = Larger(a, b);         // vector overload: b
    for (int x : big) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
```

Use `T{}` as the starting value, not `0`. A literal `0` makes `accumulate` add up `int`s, so a `vector<double>` sum gets truncated.

**A good point you should remember:** you can't *partially specialize* a function template, so `template<> Larger<vector<T>>` doesn't work for every `T`. Overloading is the right tool here.

### 2. Pass in how to compare

This keeps one template and lets the caller decide what "larger" means:

```cpp
template <typename T, typename Compare>
T Larger(const T& first, const T& second, Compare greater) {
    return greater(first, second) ? first : second;
}

auto bySum = [](const vector<int>& x, const vector<int>& y) {
    return accumulate(x.begin(), x.end(), 0) > accumulate(y.begin(), y.end(), 0);
};

Larger(a, b, bySum);
```

This is how the STL works: `sort`, `max`, and `max_element` all take comparators.

### 3. Give the type its own `operator>`

If the vector stands for something, like a `Scoreboard` or `Cart`, wrap it in a class and define `operator>` to compare sums. The original `Larger` then works unchanged. This ties back nicely to operator overloading, and the template just requires that `T` supports `>`.

## Templates in Your Own Designs

A template is a design decision, just like choosing inheritance or composition. Ask these questions when you are designing a class:

| Ask yourself                                                                | If yes, consider...                        | Example                       |
| --------------------------------------------------------------------------- | ------------------------------------------ | ----------------------------- |
| Does the behavior stay the same while the **stored type** changes?          | A class template                           | `Stack<T>`, `History<T>`      |
| Am I about to copy/paste a function and only change the types?              | A function template                        | `Larger<T>`, `Swap<T>`        |
| Do I need to mix **different** types together and decide at **runtime**?    | An abstract base class + virtual functions | A party of Fighters and Mages |
| Do several unrelated classes need the same ability (compare, count, print)? | A mixin base-class template (CRTP)         | `Comparable<Coin>`            |
| Should the user choose a **strategy** (ordering, filtering, scoring)?       | A template parameter for the behavior      | `SortedList<T, Compare>`      |
| Is the size or a setting fixed for the life of the program?                 | A non-type template parameter              | `Inventory<T, 10>`            |
| Does my template expect certain methods on `T`?                             | Write those down as a **concept**          | `template <Combatant T>`      |

Templates and inheritance are not rivals. A common, strong design uses both:

```text
Roster<Character>             <- template: same container logic for any type
   holds unique_ptr<Character> <- inheritance: Fighter, Mage, Rogue decided at runtime
   created by Spawn<Mage>()    <- template: one factory for every subclass
```

### Compile-time vs runtime polymorphism at a glance

|                             | Templates (static)                              | Virtual functions (dynamic)                   |
| --------------------------- | ----------------------------------------------- | --------------------------------------------- |
| Decided                     | When you compile                                | While the program runs                        |
| Shared base class needed?   | No, the type just needs the right operations    | Yes                                           |
| Mix types in one container? | No, `vector<T>` holds one `T`                   | Yes, through `Base*` / `unique_ptr<Base>`     |
| Interface written down as   | A concept (or a comment, before C++20)          | An abstract base class                        |
| Where errors appear         | At compile time, sometimes deep in the template | Some only at runtime (bad cast, null pointer) |
| Cost                        | More compiled code (one copy per type)          | A small cost per virtual call                 |

## Common Template Errors and What They Mean

| You see something like...                                              | It usually means...                                                        | Fix                                                               |
| ---------------------------------------------------------------------- | -------------------------------------------------------------------------- | ----------------------------------------------------------------- |
| `no matching function ... deduced conflicting types for parameter 'T'` | The arguments disagree about what `T` is (`Larger(4, 9.2)`)                | Make the types match, or write `Larger<double>(4, 9.2)`           |
| `invalid operands to binary expression` pointing **inside** a template | Your type doesn't support an operation the template uses (`>`, `<<`, `+=`) | Overload the operator for your type, or pick a different template |
| `no member named 'Score' in 'Monster'`                                 | The template calls a method your class doesn't have                        | Add the method, or write an adapter class                         |
| `undefined reference to Box<int>::Get()` (a **linker** error)          | The template's definitions are in a `.cpp` file the compiler couldn't see  | Move the definitions into the header                              |
| `use of class template 'Box' requires template arguments`              | You wrote `Box::Get()` instead of `Box<T>::Get()` outside the class        | Repeat `template <typename T>` and write `Box<T>::`               |
| `constraints not satisfied ... does not satisfy 'Scorable'`            | A concept rejected your type (good news: the error is on **your** line)    | Read the note that follows. It names the missing requirement.     |
| `non-type template argument is not a constant expression`              | You passed a normal variable as a value parameter (`Inventory<int, n>`)    | Use a literal or a `constexpr` variable                           |

**Reading tip:** template errors are long. Scroll to the **first** `error:` line, then look for the `note: in instantiation of ... requested here` line. That note points to the line in **your** code that caused the problem.

## Vocabulary

| Term                        | Meaning                                                                                    |
| --------------------------- | ------------------------------------------------------------------------------------------ |
| Template                    | A recipe the compiler uses to generate functions or classes                                |
| Template parameter          | The placeholder in the recipe: `T` in `template <typename T>`                              |
| Template argument           | What you fill in: `int` in `Box<int>`                                                      |
| Instantiation               | The real function or class the compiler generates, such as `Box<int>`                      |
| Argument deduction          | The compiler figures out `T` from the function arguments                                   |
| CTAD                        | Class template argument deduction: `Box b{42};` becomes `Box<int>` (C++17)                 |
| Non-type template parameter | A compile-time **value** parameter, like `size_t N`                                        |
| Specialization              | A custom version of a template for one specific type argument                              |
| Partial specialization      | A custom version for a family of types, like `Formatter<vector<T>>` (class templates only) |
| Function object (functor)   | An object of a class that overloads `operator()`, so it can be called like a function      |
| Concept                     | A named compile-time requirement on a type (C++20)                                         |
| CRTP                        | A class that inherits from a template of itself: `class Coin : public Comparable<Coin>`    |
| Static polymorphism         | Choosing behavior by type at compile time (templates)                                      |
| Dynamic polymorphism        | Choosing behavior by object at runtime (virtual functions)                                 |
