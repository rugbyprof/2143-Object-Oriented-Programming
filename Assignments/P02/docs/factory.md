```
title: Constructors vs. Static Factory Methods
language: C++
level: Intermediate OOP
topics:
  - Constructors
  - Static Factory Methods
  - Encapsulation
  - Object Validation
  - std::optional
  - std::expected
  - Polymorphism
  - Factory Design Pattern
  - Smart Pointers
format: Extended Teaching Handout
```

# Constructors vs. Static Factory Methods in C++

## An Extended Guide with Examples, Design Decisions, and Common Pitfalls

Your original `factory.md` has a particularly effective teaching progression: start with a constructor that works perfectly well, then introduce situations where a constructor becomes inconvenient.

I'd preserve that structure. The original uses `Args::parse()`, `Image::load()`, and eventually `FilterFactory::create()` to show how object creation becomes more sophisticated as requirements change.

The expanded version below adds several dimensions:

- More complete, compilable C++ examples.
- A clearer distinction between `static` functions and factory methods.
- Constructor overloading versus named factories.
- Private constructors and object invariants.
- Failure handling with `std::optional` and C++23 `std::expected`.
- Polymorphic factories using inheritance and smart pointers.
- Factory functions versus the formal Factory Method design pattern.
- When factories are unnecessary or actively make code worse.
- Student exercises and discussion questions.

The most important distinction to reinforce is that factories do not replace constructors. They provide another way to control how constructors are used.

# Part 1 — Understanding the Problem

## 1. Constructors: The Normal Starting Point

A constructor initializes an object when it is created.

Consider a simple `Image` class:

```
#include <iostream>
#include <vector>
#include <stdexcept>

class Image {
private:
    int width_;
    int height_;
    std::vector<unsigned char> pixels_;

public:
    Image(int width, int height)
        : width_(width),
          height_(height) {

        if (width <= 0 || height <= 0) {
            throw std::invalid_argument(
                "Image dimensions must be positive"
            );
        }

        pixels_.resize(
            static_cast<std::size_t>(width) * height * 3,
            0
        );
    }

    int width() const {
        return width_;
    }

    int height() const {
        return height_;
    }
};

int main() {
    Image img(640, 480);

    std::cout << img.width() << " x "
              << img.height() << '\n';
}
```

Output:

```
640 x 480
```

The constructor performs three responsibilities:

1. Receives initialization values.
2. Validates those values.
3. Initializes the object's internal state.

This is perfectly reasonable C++.

In fact, constructors should generally be the default choice when creating an object requires straightforward initialization.

### What is an object invariant?

An invariant is a condition that must remain true for every valid object.

For this `Image` class:

$$ width > 0 \quad \&\& \quad height > 0 $$

The constructor establishes that invariant.

A factory can help enforce invariants, but the factory mechanism itself does not magically guarantee correctness.

## 2. The First Limitation: Constructors Have No Descriptive Names

Suppose an image can be created in several ways:

```
Image a(640, 480);
Image b("photo.png");
Image c("https://example.com/photo.png");
```

What does each constructor do?

The first is fairly obvious. The other two are ambiguous.

Worse, these two constructor declarations cannot coexist:

```
Image(const std::string& filename);
Image(const std::string& url);
```

They have identical signatures. Parameter names do not participate in overload resolution.

We could create wrapper types:

```
struct FilePath {
    std::string value;
};

struct Url {
    std::string value;
};

Image(FilePath path);
Image(Url url);
```

This is a legitimate alternative, especially when strongly typed interfaces are desirable.

But another solution is to use named functions:

```
Image blank = Image::createBlank(640, 480);
Image local = Image::load("photo.png");
Image remote = Image::download("https://example.com/photo.png");
```

The function names explain the intent without requiring readers to inspect the class declaration.

This is our first motivation for a factory: a meaningful name for a particular creation operation.

# Part 2 — What Makes a Static Factory Method?

## 3. Understanding `static` Member Functions

Before discussing factories, it helps to understand the `static` keyword.

A normal member function operates on a particular object:

```
class Counter {
private:
    int value_ = 0;

public:
    void increment() {
        ++value_;
    }

    int value() const {
        return value_;
    }
};
```

Usage:

```
Counter c;
c.increment();
```

The function `increment()` implicitly receives the current object through `this`.

A static member function does not operate on an implicit object:

```
class Counter {
public:
    static Counter create() {
        return Counter{};
    }
};
```

Usage:

```
Counter c = Counter::create();
```

Notice that `create()` is called through the class name.

No existing `Counter` object is required.

A static member function:

- Belongs to the class's scope.
- Has no `this` pointer.
- Can access private members of its class.
- Can create and return objects.
- Cannot directly access non-static data members without an object.

The last two properties make static member functions particularly useful for factories.

## 4. A Complete Static Factory Example

Consider a `Temperature` class.

We want to store temperatures internally in Celsius but allow construction from either Celsius or Fahrenheit.

Both inputs are `double`, so overloaded constructors cannot distinguish their meaning.

```
#include <iostream>

class Temperature {
private:
    double celsius_;

    explicit Temperature(double celsius)
        : celsius_(celsius) {}

public:
    static Temperature fromCelsius(double c) {
        return Temperature(c);
    }

    static Temperature fromFahrenheit(double f) {
        return Temperature((f - 32.0) * 5.0 / 9.0);
    }

    double celsius() const {
        return celsius_;
    }

    double fahrenheit() const {
        return celsius_ * 9.0 / 5.0 + 32.0;
    }
};

int main() {
    Temperature a = Temperature::fromCelsius(25);
    Temperature b = Temperature::fromFahrenheit(77);

    std::cout << a.celsius() << '\n';
    std::cout << b.celsius() << '\n';
}
```

Output:

```
25
25
```

### Why this design works

The constructor is private, so outside code cannot directly create a `Temperature`.

```
Temperature t(25);  // Compilation error
```

Instead, callers must use one of the named factories.

```
Temperature t = Temperature::fromFahrenheit(77);
```

The factory interprets the input and delegates actual object construction to the constructor.

Object creation flow

`Temperature::fromFahrenheit(77)`

Convert Fahrenheit to Celsius

Private constructor `Temperature(25)`

Valid `Temperature` object returned

### Important observations

The factory is not a constructor. It is a regular function that happens to create and return an object.

The constructor still does the actual construction.

Also, `explicit` prevents implicit conversion through the one-argument constructor, but it is not what makes the constructor inaccessible. The `private` access specifier does that.

This example demonstrates how named factories can make an API both safer and easier to understand.

# Part 3 — Factories and Failure Handling

## 5. The Second Limitation: Constructors Cannot Return a Failure Value

Suppose a program needs a `Port` object representing a TCP port number.

Valid port numbers range from 0 through 65535, although applications may impose narrower requirements.

A constructor could throw an exception:

```
class Port {
private:
    int number_;

public:
    explicit Port(int number) : number_(number) {
        if (number < 0 || number > 65535) {
            throw std::invalid_argument("Invalid port");
        }
    }
};
```

This is entirely valid.

However, sometimes invalid input is expected rather than exceptional.

For example, an application might be reading user-entered port numbers from a configuration file.

A factory can return `std::optional<Port>` instead.

## 6. Returning `std::optional<T>`

`std::optional<T>` was introduced in C++17.

It represents one of two states:

- A value of type `T` exists.
- No value exists.

Here is a complete example:

```
#include <iostream>
#include <optional>

class Port {
private:
    int number_;

    explicit Port(int number) : number_(number) {}

public:
    static std::optional<Port> create(int number) {
        if (number < 0 || number > 65535) {
            return std::nullopt;
        }

        return Port(number);
    }

    int value() const {
        return number_;
    }
};

int main() {
    auto good = Port::create(8080);
    auto bad = Port::create(70000);

    if (good) {
        std::cout << "Port: " << good->value() << '\n';
    }

    if (!bad) {
        std::cout << "Invalid port number\n";
    }
}
```

Output:

```
Port: 8080
Invalid port number
```

Notice the key line:

```
return std::nullopt;
```

A constructor cannot do this.

A factory can because its return type is an ordinary function return type.

### Why the private constructor matters

Without a private constructor, a caller could bypass the factory:

```
Port p(70000);
```

With a private constructor, the caller must use `Port::create()`.

That establishes a single controlled creation path for ordinary callers.

### What does `auto` represent?

```
auto good = Port::create(8080);
```

The compiler deduces:

```
std::optional<Port> good = Port::create(8080);
```

This is not a pointer. `std::optional` stores a value in its own storage when engaged.

However, `std::optional` provides pointer-like operations:

```
good->value();
(*good).value();
```

Both access the contained `Port`, provided it exists.

## 7. Going Further: `std::expected` in C++23

`std::optional` can tell us that creation failed.

It cannot directly explain why.

For more informative error handling, C++23 introduces `std::expected<T, E>`.

Here, `T` is the successful result type and `E` is the error type.

```
#include <expected>
#include <string>
#include <iostream>

class Port {
private:
    int number_;

    explicit Port(int number) : number_(number) {}

public:
    static std::expected<Port, std::string>
    create(int number) {

        if (number < 0) {
            return std::unexpected(
                "Port number cannot be negative"
            );
        }

        if (number > 65535) {
            return std::unexpected(
                "Port number exceeds 65535"
            );
        }

        return Port(number);
    }

    int value() const {
        return number_;
    }
};

int main() {
    auto result = Port::create(70000);

    if (!result) {
        std::cout << result.error() << '\n';
        return 1;
    }

    std::cout << result->value() << '\n';
}
```

Output:

```
Port number exceeds 65535
```

Compile with a compiler and standard library that support C++23 `std::expected`:

```
g++ -std=c++23 main.cpp -o demo
```

Not every compiler/standard-library combination supports every C++23 feature yet, so check the installed toolchain.

### Comparing three approaches

| Technique                         | Success | Failure     |
| --------------------------------- | ------- | ----------- |
| Constructor with exception        | Object  | Throws      |
| Factory returning `optional<T>`   | Object  | No value    |
| Factory returning `expected<T,E>` | Object  | Error value |

There is no universally correct choice.

Use exceptions when failure is appropriately modeled as an exception. Use `optional` when absence is expected and needs no explanation. Use `expected` when the caller needs to understand or handle a specific failure.

# Part 4 — Factories and Runtime Polymorphism

## 8. The Third Limitation: Choosing a Type at Runtime

This is where factories become particularly valuable in an object-oriented programming course.

Suppose an image-processing program supports several filters:

- Grayscale
- Blur
- Invert

Each filter has a different implementation, but the rest of the program should be able to treat all filters uniformly.

We begin with an abstract base class.

```
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

class Filter {
public:
    virtual ~Filter() = default;

    virtual void apply() const = 0;
};
```

Next, create concrete subclasses.

```
class Grayscale : public Filter {
public:
    void apply() const override {
        std::cout << "Applying grayscale\n";
    }
};

class Blur : public Filter {
public:
    void apply() const override {
        std::cout << "Applying blur\n";
    }
};

class Invert : public Filter {
public:
    void apply() const override {
        std::cout << "Applying invert\n";
    }
};
```

Without a factory, the calling code must decide which object to create.

```
std::unique_ptr<Filter> filter;

if (name == "grayscale") {
    filter = std::make_unique<Grayscale>();
}
else if (name == "blur") {
    filter = std::make_unique<Blur>();
}
else if (name == "invert") {
    filter = std::make_unique<Invert>();
}
```

This works.

But imagine repeating this logic in multiple places throughout the program. Adding a new filter would require changing every one of those locations.

A factory centralizes the decision.

## 9. Creating a Dedicated Factory Class

```
class FilterFactory {
public:
    static std::unique_ptr<Filter>
    create(const std::string& name) {

        if (name == "grayscale") {
            return std::make_unique<Grayscale>();
        }

        if (name == "blur") {
            return std::make_unique<Blur>();
        }

        if (name == "invert") {
            return std::make_unique<Invert>();
        }

        throw std::invalid_argument(
            "Unknown filter: " + name
        );
    }
};
```

The caller becomes much simpler:

```
int main() {
    auto filter = FilterFactory::create("blur");

    filter->apply();
}
```

Output:

```
Applying blur
```

The caller knows only that it has a `Filter`.

It does not need to know whether the object is a `Blur`, `Invert`, or `Grayscale`.

That is runtime polymorphism.

Polymorphic factory structure

`FilterFactory::create(name)`

Select concrete type using `name`

Grayscale

Blur

Invert

`std::unique_ptr<Filter>`

Common return type, regardless of concrete subclass

### Why return a pointer?

We cannot return an abstract `Filter` by value:

```
Filter create();  // Invalid: Filter is abstract
```

Even if `Filter` were concrete, returning a derived object as a base object by value would cause object slicing.

For example:

```
class Animal {
public:
    virtual ~Animal() = default;

    virtual void speak() const {
        std::cout << "Animal\n";
    }
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof\n";
    }
};

Animal makeAnimal() {
    return Dog{};  // Dog portion is sliced away
}
```

Calling `speak()` on the returned `Animal` produces:

```
Animal
```

The `Dog` portion has been lost.

Returning a pointer to the base class preserves the dynamic type.

### Why `std::unique_ptr` instead of a raw pointer?

An older C++ implementation might use:

```
static Filter* create(const std::string& name) {
    if (name == "blur") {
        return new Blur();
    }

    return nullptr;
}
```

The caller must then remember:

```
Filter* f = FilterFactory::create("blur");

f->apply();

delete f;
```

If `delete` is forgotten, the allocation leaks.

The modern version:

```
auto f = FilterFactory::create("blur");
f->apply();
```

automatically destroys the object when its owning `unique_ptr` is destroyed.

For a factory that creates a polymorphic object with one owner, `std::unique_ptr` is generally the best default.

# Part 5 — A More Advanced Factory: Registration

## 10. Eliminating the Long `if` / `else if` Chain

The preceding factory has one weakness.

Every time a new filter is added, the factory must be modified.

For a small application, that is completely acceptable.

For a larger application, we can use a registry.

A registry maps names to functions that create objects.

```
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include <utility>

class FilterRegistry {
public:
    using Creator =
        std::function<std::unique_ptr<Filter>()>;

private:
    std::unordered_map<std::string, Creator> creators_;

public:
    void registerFilter(
        std::string name,
        Creator creator
    ) {
        creators_[std::move(name)] = std::move(creator);
    }

    std::unique_ptr<Filter>
    create(const std::string& name) const {

        auto it = creators_.find(name);

        if (it == creators_.end()) {
            throw std::invalid_argument(
                "Unknown filter: " + name
            );
        }

        return it->second();
    }
};
```

Usage:

```
int main() {
    FilterRegistry registry;

    registry.registerFilter(
        "blur",
        []() {
            return std::make_unique<Blur>();
        }
    );

    registry.registerFilter(
        "invert",
        []() {
            return std::make_unique<Invert>();
        }
    );

    auto filter = registry.create("blur");

    filter->apply();
}
```

The factory no longer contains explicit knowledge of every subclass.

Instead, subclasses are registered with the factory.

### What is the lambda doing?

Consider:

```
[]() {
    return std::make_unique<Blur>();
}
```

This is an unnamed function object.

Its job is to create a `Blur` whenever called.

The registry stores that callable and invokes it later.

The lambda is not executed during registration.

It is executed when the caller requests the corresponding filter.

This distinction matters because it allows the factory to create multiple independent objects.

```
auto a = registry.create("blur");
auto b = registry.create("blur");
```

Both objects are separate instances.

### Why use a registry?

Registration becomes useful when:

- An application supports plugins.
- Subclasses are spread across many source files.
- Users can select implementations through configuration.
- New implementations should not require editing a central decision statement.

However, a registry adds complexity and has its own design considerations, including duplicate names, initialization order, and error handling.

For three filters, an `if` statement is probably better.

For dozens of filters, registration becomes attractive.

Abstraction should eliminate a real problem, not merely demonstrate that the programmer knows how to use `std::function`.

# Part 6 — Factory Methods vs. Factory Design Patterns

## 11. The Word "Factory" Is Overloaded

The original document correctly distinguishes a static factory method from a polymorphic factory.

There is one more important distinction worth teaching: the formal Factory Method pattern from the Gang of Four design patterns is not identical to a static factory method.

These terms are often used loosely, which can confuse students.

| Concept                  | Main idea                                     | Typical example                                 |
| ------------------------ | --------------------------------------------- | ----------------------------------------------- |
| Constructor              | Initialize a particular class                 | `Image(640,480)`                                |
| Static factory method    | Named class-level creation function           | `Image::load(path)`                             |
| Simple factory           | Select a concrete implementation              | `FilterFactory::create(name)`                   |
| Factory Method pattern   | Subclasses override a virtual creation method | `Creator::makeFilter()`                         |
| Abstract Factory pattern | Create families of related objects            | `GUIFactory::createButton()` and `createMenu()` |

A simple factory is a common design technique, but it is not one of the original GoF patterns by that name.

## 12. The Formal Factory Method Pattern

Imagine a system where different image-processing pipelines decide which filter to create.

Instead of using a static function, we define a base creator class with a virtual factory method.

```
class FilterCreator {
public:
    virtual ~FilterCreator() = default;

    virtual std::unique_ptr<Filter>
    makeFilter() const = 0;

    void process() const {
        auto filter = makeFilter();
        filter->apply();
    }
};
```

Now subclasses determine the concrete type:

```
class BlurCreator : public FilterCreator {
public:
    std::unique_ptr<Filter>
    makeFilter() const override {
        return std::make_unique<Blur>();
    }
};

class InvertCreator : public FilterCreator {
public:
    std::unique_ptr<Filter>
    makeFilter() const override {
        return std::make_unique<Invert>();
    }
};
```

Usage:

```
int main() {
    BlurCreator creator;
    creator.process();
}
```

Output:

```
Applying blur
```

The interesting detail is that `process()` is implemented in the base class.

The base class defines the algorithm:

```
void process() const {
    auto filter = makeFilter();
    filter->apply();
}
```

But it delegates the choice of which concrete filter to instantiate to a subclass.

This is the central idea of the Factory Method pattern:

A base class defines a creation interface, and subclasses decide which concrete product to instantiate.

The pattern is useful when a framework defines a general workflow but allows subclasses to customize the objects used by that workflow.

It is not necessary merely because a class needs to create another object.

# Part 7 — Factories, Validation, and Encapsulation

## 13. A Factory Is Not Automatically a Validation Mechanism

Consider:

```
class Student {
public:
    int id;

    Student(int studentId) : id(studentId) {}

    static Student create(int studentId) {
        return Student(studentId);
    }
};
```

The factory provides no additional protection.

Both of these work:

```
Student a(-100);
Student b = Student::create(-100);
```

And because `id` is public, callers can mutate the object after creation.

```
b.id = -999;
```

A factory does not prevent invalid objects unless the class is designed to enforce its invariants.

## 14. Designing a Class That Cannot Be Created Invalidly

```
#include <optional>

class Student {
private:
    int id_;

    explicit Student(int id) : id_(id) {}

public:
    static std::optional<Student> create(int id) {
        if (id <= 0) {
            return std::nullopt;
        }

        return Student(id);
    }

    int id() const {
        return id_;
    }
};
```

Now consider these operations:

```
auto a = Student::create(1234);  // Valid
auto b = Student::create(-10);   // Empty optional

Student c(1234);                 // Compilation error
Student d;                       // Compilation error
```

The class establishes the invariant:

\\[ id > 0 \\]

And outside callers cannot bypass the validation using an ordinary constructor.

There is also no public setter that would allow the ID to become invalid later.

This illustrates a broader OOP principle:

Make invalid states difficult or impossible to represent through the public interface.

### An important subtlety: copying

The class above still has an implicitly generated copy constructor.

```
auto a = Student::create(1234);

if (a) {
    Student copy = *a;
}
```

This is fine because copying an already-valid `Student` preserves the invariant.

The goal is not necessarily to force every object creation expression through the factory.

The goal is to ensure that every publicly accessible creation path produces a valid object.

# Part 8 — Factories and Object Lifetime

## 15. Returning Objects by Value

A common concern is that this factory creates unnecessary copies:

```
static Image create(int width, int height) {
    return Image(width, height);
}
```

In C++17 and later, this form benefits from guaranteed copy elision.

The returned prvalue initializes the destination object directly.

```
Image img = Image::create(640, 480);
```

There is no required intermediate copy or move of the `Image`.

This is an important reason not to automatically use pointers for every factory.

### Compare the alternatives

```
static Image create() {
    return Image(640, 480);
}
```

Returns an object by value.

```
static std::unique_ptr<Image> create() {
    return std::make_unique<Image>(640, 480);
}
```

Returns an owning pointer to a dynamically allocated object.

Neither is inherently better in every situation.

The first is usually preferable for ordinary value-like objects.

The second is appropriate when dynamic lifetime or polymorphism is required.

### Named Return Value Optimization

Consider:

```
static Image create() {
    Image img(640, 480);

    // Additional work on img

    return img;
}
```

Compilers commonly apply Named Return Value Optimization (NRVO).

However, unlike returning a temporary directly, NRVO is not guaranteed by the language.

If NRVO is not performed, a move may be used when the type supports it.

For students, the useful rule is:

Return ordinary objects by value unless there is a concrete reason to use dynamic allocation or indirection.

# Part 9 — When Not to Use a Factory

## 16. The Danger of Overengineering

Consider this class:

```
class Point {
public:
    double x;
    double y;

    Point(double x, double y)
        : x(x), y(y) {}
};
```

A factory version could look like:

```
class Point {
public:
    double x;
    double y;

    static Point create(double x, double y) {
        return Point(x, y);
    }

private:
    Point(double x, double y)
        : x(x), y(y) {}
};
```

But what have we gained?

Compare:

```
Point p(3.0, 4.0);
```

with:

```
Point p = Point::create(3.0, 4.0);
```

The factory provides no meaningful additional behavior, validation, or clarity.

It simply adds another function.

A factory is useful when it solves a problem.

It is not automatically a more sophisticated or more object-oriented design.

### A practical decision table

| Situation                                     | Preferred starting point                   |
| --------------------------------------------- | ------------------------------------------ |
| Simple initialization                         | Constructor                                |
| Several meanings for the same parameter types | Named factory                              |
| Parsing external input                        | Factory or separate parser                 |
| Creation can legitimately fail                | Factory returning `optional` or `expected` |
| Creation requires file I/O                    | Named factory or loader function           |
| Runtime selection among subclasses            | Polymorphic factory                        |
| Large extensible collection of subclasses     | Registry-based factory                     |
| Framework subclasses customize creation       | Factory Method pattern                     |
| Plain value object with obvious arguments     | Constructor                                |

One nuance worth mentioning: a free function such as `parseArgs()` or `loadImage()` can sometimes be just as appropriate as a static factory. Not every creation operation must belong to the class being created.

# Part 10 — Connecting Back to P02 and P03

## 17. `Args::parse()` — A Factory for Command-Line Arguments

Your original document uses:

```
Args args = Args::parse(argc, argv);
```

This is a useful teaching example because the class is interpreting information from outside the program.

Consider:

```
./imgtool input.png output.png --grayscale --blur
```

The parser must:

1. Identify the input filename.
2. Identify the output filename.
3. Interpret the remaining command-line arguments.
4. Validate recognized operations.
5. Construct a valid `Args` object.

A simplified implementation might look like:

```
#include <string>
#include <stdexcept>

class Args {
private:
    std::string input_;
    std::string output_;

    Args(std::string input, std::string output)
        : input_(std::move(input)),
          output_(std::move(output)) {}

public:
    static Args parse(int argc, char* argv[]) {
        if (argc < 3) {
            throw std::invalid_argument(
                "Expected input and output filenames"
            );
        }

        return Args(argv[1], argv[2]);
    }

    const std::string& input() const {
        return input_;
    }

    const std::string& output() const {
        return output_;
    }
};
```

The factory's job is to interpret the external representation and translate it into the internal representation.

The constructor's job is to initialize the members.

This separation becomes especially valuable when the input format changes.

For example, the program could eventually support:

```
Args::parse(argc, argv);
Args::fromConfig("settings.json");
Args::fromEnvironment();
```

All three factories could create the same `Args` type from different sources.

The class does not need three ambiguous constructors.

## 18. `Image::load()` — A Factory for Resource Acquisition

The second example:

```
Image img = Image::load("images/Hulda.png");
```

demonstrates a different motivation.

The caller does not know the image dimensions before loading the file.

The factory must discover them.

Conceptually:

```
Image Image::load(const std::string& filename) {
    // Decode file and determine width and height.
    // Throw or return an error if decoding fails.

    int width = /* decoded width */;
    int height = /* decoded height */;

    Image img(width, height);

    // Copy decoded pixels into img.

    return img;
}
```

This is intentionally pseudocode: a real implementation needs an image decoder and pixel-copying logic.

The important distinction is:

```
Image blank(640, 480);
```

The caller supplies the dimensions.

```
Image loaded = Image::load("photo.png");
```

The factory discovers the dimensions.

That is a meaningful separation of responsibilities.

## 19. `FilterFactory::create()` — A Factory for Polymorphism

P03 introduces another level:

```
auto filter = FilterFactory::create(operation);
```

Now the factory must determine not only how to initialize an object, but which class to instantiate.

The progression is:

Stage 1 — Constructor

`Image(640, 480)`

Known class, known initialization values

Stage 2 — Static factory

`Image::load("photo.png")`

Known class, values discovered through external processing

Stage 3 — Polymorphic factory

`FilterFactory::create(operation)`

Concrete class selected at runtime

Stage 4 — Registry factory

`registry.create("blur")`

Available implementations are configured or registered separately

These are related techniques, but each addresses a different design problem.

# Part 11 — Student Exercises

## Exercise 1 — Named Constructors

Create a `Distance` class that internally stores meters.

Requirements:

- The constructor must be private.
- Implement `fromMeters(double)`.
- Implement `fromFeet(double)`.
- Implement `fromMiles(double)`.
- Provide `meters()` and `feet()` accessors.

Test:

```
auto a = Distance::fromMiles(1);
auto b = Distance::fromFeet(5280);
```

Both objects should represent approximately the same distance.

Discussion: Why are three overloaded constructors taking `double` not possible?

## Exercise 2 — Validated Factory

Create a `Percentage` class whose value must be between 0 and 100 inclusive.

Requirements:

- Use a private constructor.
- Provide `static std::optional<Percentage> create(double)`.
- Return `std::nullopt` for invalid values.
- Do not provide a setter that permits invalid values.

Test the following inputs:

```
-1
0
45.5
100
101
```

Discussion: Does making the constructor private automatically guarantee validity? What other design choices matter?

## Exercise 3 — Polymorphic Factory

Create an abstract `Shape` class with:

```
virtual double area() const = 0;
```

Implement:

```
Circle
Rectangle
Square
```

Create a factory:

```
static std::unique_ptr<Shape>
create(const std::string& type, double a, double b);
```

Use the following interpretation:

| Type      | `a`    | `b`     |
| --------- | ------ | ------- |
| Circle    | Radius | Ignored |
| Rectangle | Width  | Height  |
| Square    | Side   | Ignored |

Students should decide how to handle unknown shape names and invalid dimensions.

Discussion: What is potentially problematic about using a generic pair of doubles for every shape?

## Exercise 4 — Refactoring a Factory

Begin with an `if` / `else if` factory that creates three filter subclasses.

Refactor it into a registry using:

```
std::unordered_map<
    std::string,
    std::function<std::unique_ptr<Filter>()>
>
```

Add a fourth filter without modifying the registry's `create()` implementation.

Discussion: Does this improve maintainability for a small project? At what scale does the added abstraction become worthwhile?

# Part 12 — Knowledge Check

C++ Factory Methods — Quick Quiz

0 of 5 answered

1\. Why can't a constructor return std::optional\<Image>?

Constructors are always static

Constructors have no return type

optional cannot contain class objects

Constructors cannot perform validation

2\. What does a private constructor contribute to a validated factory?

It automatically checks every field

It prevents ordinary external code from directly invoking that constructor

It disables all copying

It forces heap allocation

3\. Which return type is generally appropriate for a factory selecting among polymorphic Filter subclasses with exclusive ownership?

Filter by value

Filter& to a local variable

std::unique_ptr\<Filter>

void\*

4\. What is the principal advantage of a registry-based factory?

It removes all runtime overhead

It allows implementations to be registered without changing the factory's selection code

It makes constructors unnecessary

It guarantees thread safety

5\. Which statement about C++17 guaranteed copy elision is correct?

All factory return statements avoid moves

Returning a temporary such as return Image(640,480) directly constructs the result

Factories must always return pointers

NRVO is mandatory for named local variables

# Final Summary

A constructor is the fundamental C++ mechanism for initializing an object. A factory is an ordinary function that controls or organizes the process of creating an object.

Factories become useful when object creation requires meaningful names, external interpretation, recoverable failure handling, runtime selection of subclasses, or centralized creation policy.

The design decision should be driven by the requirements, not by the desire to use a pattern.

A good rule for students to remember:

> Use constructors to initialize objects. Use factories when deciding how, whether, or what to construct deserves its own interface.

One final technical nuance from the original document: a constructor can fail by throwing an exception, and it can delegate to other constructors, but it cannot return an alternative value. Also, an `Args::parse()` implementation that calls `exit()` on errors is a valid design choice, not a special factory capability. A constructor could do the same, although terminating the process from reusable class code is often undesirable.

The original handout's central argument remains sound: start with a constructor, identify a concrete limitation, and introduce the simplest factory mechanism that addresses it.