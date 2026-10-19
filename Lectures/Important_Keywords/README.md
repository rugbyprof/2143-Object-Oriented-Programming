# Modern C++: Expressing Intent and Catching Mistakes

Modern C++ provides ways to tell the compiler how your code is intended to work. These features help catch mistakes, clarify interfaces, and manage resources.

Some are keywords, some are special syntax, and others are library types. You do not need to learn them all at once. Start by understanding the problem each one solves.

## 1. `explicit`: Require Intentional Construction

An `explicit` constructor cannot be used to implicitly convert an argument into an object of its class.

```cpp
class Meters {
public:
    explicit Meters(double value)
        : value_(value) {}

private:
    double value_;
};
```

```cpp
Meters distance{10.0};    // Valid.
// Meters distance = 10.0; // Error.
```

This also affects function calls:

```cpp
void Walk(Meters distance);

// Walk(10.0);         // Error.
Walk(Meters{10.0});    // Valid.
```

**Why use it?** It makes construction visible when an automatic conversion could be confusing.

**Remember:** `explicit` does not prohibit ordinary conversions used to supply constructor arguments.

```cpp
Meters distance{10};  // Valid: int converts to double.
```

## 2. `= default`: Request the Compiler’s Implementation

Use `= default` to request the normal compiler-generated implementation of a special member function.

```cpp
class Player {
public:
    Player() = default;
    ~Player() = default;

private:
    int health_ = 100;
};
```

The default constructor uses the member initializer, so `health_` starts at `100`.

You will often see a defaulted virtual destructor:

```cpp
class Character {
public:
    virtual ~Character() = default;
};
```

Here, `virtual` enables correct destruction through a base-class pointer. `= default` asks the compiler to supply the destructor’s implementation.

## 3. `= delete`: Forbid an Operation

A deleted function cannot be used.

```cpp
class Animation {
public:
    Animation() = default;

    Animation(const Animation&) = delete;
    Animation& operator=(const Animation&) = delete;
};
```

```cpp
Animation first;

// Animation second = first;  // Error: copy construction is forbidden.

Animation third;
// third = first;             // Error: copy assignment is forbidden.
```

**Why use it?** Some objects manage resources that should not be copied, such as a running worker thread.

The syntax `= delete` does not free memory. It marks a function as unavailable.

Compare these declarations:

| Syntax                            | Meaning                                 |
| --------------------------------- | --------------------------------------- |
| `Player() = default;`             | Request the normal default constructor. |
| `Player(const Player&) = delete;` | Forbid copy construction.               |
| `virtual void Attack() = 0;`      | Declare a pure virtual function.        |

## 4. `override`: Check an Intended Override

Use `override` when a derived-class function is intended to override a virtual function.

```cpp
class Character {
public:
    virtual ~Character() = default;
    virtual void Attack() const = 0;
};

class Fighter : public Character {
public:
    void Attack() const override {
        // Perform a sword attack.
    }
};
```

The compiler checks that the function actually overrides a base-class function.

```cpp
// Missing const:
// void Attack() override;  // Error: does not override.
```

**Why use it?** Small differences in parameter types or qualifiers can accidentally create a different function. `override` catches the mismatch.

## 5. `final`: Prevent Further Inheritance or Overriding

Apply `final` to a class to prevent inheritance from it:

```cpp
class FireballAnimation final {
};

// class SpecialFireball : public FireballAnimation {}; // Error.
```

Apply it to a virtual function to prevent further overriding:

```cpp
class Fighter : public Character {
public:
    void Attack() const final {
        // Derived classes cannot override this function.
    }
};
```

**Why use it?** It expresses a deliberate restriction in your design.

`override` and `final` are identifiers with special meaning in these positions, rather than ordinary reserved keywords everywhere.

## 6. `nullptr`: Represent a Null Pointer

Use `nullptr` when a pointer does not point to an object.

```cpp
Character* target = nullptr;
```

It avoids the ambiguity of using `0` or `NULL`:

```cpp
void Inspect(int value);
void Inspect(Character* character);

Inspect(0);        // Calls Inspect(int).
Inspect(nullptr);  // Calls Inspect(Character*).
```

**Remember:** A pointer can still be null. Check it before dereferencing when necessary.

```cpp
if (target != nullptr) {
    target->Attack();
}
```

## 7. `enum class`: Keep Enumeration Values Scoped

A scoped enumeration keeps its enumerator names inside the enumeration’s scope.

```cpp
enum class Frame {
    Idle,
    Cast,
    Flight,
    Impact
};

Frame current = Frame::Cast;
```

A different enumeration can safely reuse those names:

```cpp
enum class PlayerState {
    Idle,
    Moving,
    Attacking
};
```

Scoped enumerations do not implicitly convert to integers:

```cpp
// int number = Frame::Cast;  // Error.
int number = static_cast<int>(Frame::Cast);
```

**Why use it?** It reduces name collisions and accidental mixing of unrelated values.

## 8. `constexpr`: Support Compile-Time Computation

Use `constexpr` for a variable that must be initialized with a constant expression:

```cpp
constexpr int kFlightSteps = 30;
```

A `constexpr` function can participate in compile-time evaluation:

```cpp
constexpr int Double(int value) {
    return value * 2;
}

constexpr int capacity = Double(10);
```

The same function can run at runtime:

```cpp
int input;
std::cin >> input;

int result = Double(input);
```

**Remember:** Declaring a function `constexpr` does not require every call to be evaluated during compilation.

## 9. `noexcept`: State That Exceptions Must Not Escape

Use `noexcept` to declare that a function must not allow an exception to escape.

```cpp
class Player {
public:
    int Health() const noexcept {
        return health_;
    }

private:
    int health_ = 100;
};
```

**Important:** `noexcept` does not catch exceptions. If an exception escapes the function, the program calls `std::terminate()`.

You will also encounter it on move operations:

```cpp
Widget(Widget&& other) noexcept;
```

Containers can consider whether moving an object may throw when deciding how to relocate elements.

Use `noexcept` when you can uphold its promise.

## 10. `[[nodiscard]]`: Call Attention to a Return Value

`[[nodiscard]]` is an attribute that encourages the compiler to warn when a result is discarded.

```cpp
[[nodiscard]]
bool SaveGame();
```

```cpp
SaveGame();  // A warning is encouraged.
```

A caller should usually examine the result:

```cpp
if (!SaveGame()) {
    std::cerr << "Save failed.\n";
}
```

**Why use it?** Ignoring a success indicator, error result, or newly produced value may be a mistake.

This attribute encourages a diagnostic; it does not force the caller to handle the result.

## 11. `auto`: Deduce a Type from an Initializer

`auto` asks the compiler to deduce a variable’s type.

```cpp
auto count = 10;       // int.
auto speed = 2.5;      // double.
auto name = "Thorin";  // const char*.
```

The variable still has a specific type checked at compile time.

It can simplify declarations:

```cpp
auto iterator = scores.begin();
```

Pay attention to whether you want a copy or a reference:

```cpp
auto copy = player;         // Creates a copy.
auto& reference = player;   // Refers to the existing object.
const auto& view = player;  // Refers to it through const access.
```

**Check your understanding:** Which declaration would let you modify the original `player` through a new name?

## 12. `concept` and `requires`: State Template Requirements

C++20 concepts let you describe requirements on template arguments.

```cpp
template <typename T>
concept AttackCapable = requires(T& object) {
    object.Attack();
};
```

Use the concept to constrain a template:

```cpp
template <AttackCapable T>
void TakeTurn(T& character) {
    character.Attack();
}
```

The compiler checks whether the required expression is valid.

**Remember:** This checks that `Attack()` can be called. It does not verify that the attack follows your game rules or calculates damage correctly.

## 13. Recognize Library Types Too

Not every modern C++ feature is a keyword. These are standard library templates:

| Type                 | Purpose                                                              | Header       |
| -------------------- | -------------------------------------------------------------------- | ------------ |
| `std::unique_ptr<T>` | Own an object and destroy it automatically.                          | `<memory>`   |
| `std::optional<T>`   | Represent a value that may be absent.                                | `<optional>` |
| `std::span<T>`       | Refer to a contiguous sequence without owning it.                    | `<span>`     |
| `std::jthread`       | Manage a thread with automatic joining and cooperative stop support. | `<thread>`   |
| `std::atomic<T>`     | Support atomic operations on shared values.                          | `<atomic>`   |

For example:

```cpp
auto player = std::make_unique<Fighter>();
player->Attack();
```

The `std::unique_ptr` owns the fighter and destroys it automatically when ownership ends.

Each type has limits you must understand:

- A `std::span` does not keep the underlying data alive.
- A `std::jthread` requests stopping cooperatively; worker code must respond to that request to stop early.
- Separate operations on multiple atomic variables do not automatically form one consistent transaction.

## 14. Read a Modern Declaration

Consider:

```cpp
class FireballAnimation final {
public:
    FireballAnimation() = default;

    FireballAnimation(const FireballAnimation&) = delete;
    FireballAnimation& operator=(const FireballAnimation&) = delete;

    [[nodiscard]]
    bool IsPlaying() const noexcept;

private:
    static constexpr int kFlightSteps = 30;
};
```

Read it as a set of design decisions:

- `final`: this class cannot be used as a base class.
- `= default`: request the normal default constructor.
- `= delete`: prevent copying.
- `[[nodiscard]]`: discarding the query’s result probably deserves a warning.
- `const`: the query cannot modify ordinary data members through this object.
- `noexcept`: an exception must not escape the query.
- `static constexpr`: the flight-step count is a compile-time constant associated with the class.

## 15. Practice

For each situation, identify the feature that best expresses the intent.

1. A derived function must match a virtual function in its base class.
2. An animation object must not be copied.
3. A number should become a `Meters` object only when construction is requested explicitly.
4. A pointer currently has no target.
5. Ignoring a save operation’s result probably indicates a mistake.
6. Two enumerations need to use the name `Idle` without a name collision.
7. A constant must be usable as a compile-time array size.
8. A template requires an object with a callable `Attack()` method.

Then explain the difference between:

```cpp
virtual ~Character() = default;
virtual void Attack() = 0;
Character(const Character&) = delete;
```

For every feature you encounter, ask: **What intention does this express, and what mistake can the compiler now detect?**