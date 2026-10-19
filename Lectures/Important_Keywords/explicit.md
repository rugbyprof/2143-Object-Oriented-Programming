# Understanding `explicit` in C++

The keyword `explicit` prevents a constructor from being used for an **implicit conversion into an object of its class**.

It does not prevent templates from accepting different types, and it does not block every numeric conversion.

## 1. Start with the `Box` Template

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

These two features have separate jobs:

- `template <typename T>` lets you choose the stored type.
- `explicit` controls whether the constructor can automatically convert a value into a box.

When you use `Box<int>`, its constructor effectively looks like this:

```cpp
explicit Box(const int& value);
```

## 2. Constructing an Object Directly

An `explicit` constructor supports direct initialization:

```cpp
Box<int> first{42};   // OK: direct-list-initialization.
Box<int> second(42);  // OK: direct-initialization.
```

In both cases, you directly request construction of a `Box<int>`.

However, this declaration is rejected:

```cpp
Box<int> third = 42;  // Error: constructor is explicit.
```

This form is called **copy-initialization**. It would require the constructor to provide an implicit conversion from `int` to `Box<int>`.

Despite its name, copy-initialization does not necessarily mean a copy constructor is called.

**Check your understanding:** Which declarations compile?

```cpp
Box<int> a{10};
Box<int> b(10);
Box<int> c = 10;
```

## 3. What Changes Without `explicit`?

Suppose you remove the keyword:

```cpp
template <typename T>
class Box {
public:
    Box(const T& value)
        : value_(value) {}

private:
    T value_;
};
```

Now the compiler can use the constructor to convert a value into a box automatically:

```cpp
Box<int> number = 42;  // OK without explicit.
```

The constructor is acting as a **converting constructor**.

This behavior can be convenient, but it can also allow conversions you did not intend.

## 4. Why Function Arguments Make This Important

Using the original class with its `explicit` constructor:

```cpp
#include <iostream>

void Display(const Box<int>& box) {
    std::cout << box.Get() << '\n';
}
```

Compare these calls:

```cpp
Display(42);            // Error: implicit conversion is blocked.
Display(Box<int>{42});  // OK: you construct the box directly.
```

Without `explicit`, the compiler could accept `Display(42)` by constructing a temporary `Box<int>` and passing it to the function.

With `explicit`, the call must make that construction visible.

**Think about it:** If a function expects a box, should passing an ordinary integer automatically create one? Your answer depends on what the class represents.

## 5. `explicit` Does Not Block Every Conversion

This is valid:

```cpp
Box<double> measurement{42};
```

You directly requested a `Box<double>`. Its constructor accepts a `const double&`, so the integer `42` can be converted to a `double` to supply that argument.

There are two separate questions:

| Question                                                  | What controls it?                       |
| --------------------------------------------------------- | --------------------------------------- |
| Can an integer automatically become a `Box<int>`?         | Whether the constructor is `explicit`.  |
| Can an integer supply a constructor’s `double` parameter? | The ordinary argument-conversion rules. |

`explicit` controls the first kind of conversion. It does not generally prohibit conversions used to supply the constructor’s parameters.

## 6. Templates Do Not Remove Type Rules

A template lets you create related types:

```cpp
Box<int> score{100};
Box<double> temperature{72.5};
Box<std::string> name{std::string{"Thorin"}};
```

Each instantiation still has specific parameter types.

For example:

```cpp
Box<double>
```

has a constructor that accepts:

```cpp
const double&
```

Templates provide flexibility when selecting a type. They do not make every conversion valid or desirable.

**Check your understanding:** Why can `Box<double>{42}` work even though the constructor is `explicit`?

## 7. Ordinary Member Functions Are Unaffected

The `explicit` keyword on the constructor does not change `Set()`:

```cpp
Box<double> measurement{0.0};

measurement.Set(42);  // OK: int converts to double.
```

`Set()` accepts a `const double&` for this instantiation. Its argument follows the usual function-call conversion rules.

Similarly, `explicit` does not prevent copying an existing box:

```cpp
Box<int> original{42};
Box<int> copy = original;  // OK: uses the copy constructor.
```

The constructor marked `explicit` accepts a stored value. The compiler-generated copy constructor accepts another box. They are different constructors.

## 8. A Practical Example: Units

Consider a class representing a distance:

```cpp
class Meters {
public:
    explicit Meters(double value)
        : value_(value) {}

    double Value() const {
        return value_;
    }

private:
    double value_;
};
```

A function expects a distance in meters:

```cpp
void Walk(Meters distance);
```

With `explicit`:

```cpp
Walk(10.0);          // Error.
Walk(Meters{10.0});  // OK.
```

Requiring `Meters{10.0}` makes the unit visible at the call site. This is useful when an ordinary number could represent meters, feet, seconds, or something else.

A common starting point is to mark constructors callable with one argument `explicit`, unless you deliberately want automatic conversion into the class.

## 9. Practice

Using the original `Box` class, label each statement **valid** or **invalid** and explain why.

```cpp
Box<int> a{7};              // A
Box<int> b = 7;             // B
Box<double> c{7};           // C
Box<int> d = a;             // D

c.Set(12);                  // E

Display(7);                // F
Display(Box<int>{7});       // G
```

Then answer:

1. What conversion does `explicit` prevent in statement B?
2. Why does statement C still allow an `int` argument?
3. Why is statement D different from statement B?
4. What would change if you removed `explicit` from the constructor?
5. Give an example of a class where automatic conversion would be useful—or confusing.