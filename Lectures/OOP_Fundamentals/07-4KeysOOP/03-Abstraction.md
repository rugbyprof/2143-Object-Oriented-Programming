## Abstraction

**Abstraction** means exposing **what** an object does while hiding **how** it does it. You work with a simple, high-level interface and ignore the complicated details underneath.

You use abstraction every day: you drive a car with a steering wheel and pedals without knowing how fuel injection works. In code, you call `list.sort()` without knowing which sorting algorithm it uses.

In C++, abstraction is typically implemented using:

- **Abstract classes**: a class with at least one **pure virtual function** (`= 0`). A pure virtual function is declared but has no implementation in the base class. Every concrete derived class must provide one. You **cannot create objects** of an abstract class.
- **Interfaces**: C++ has no `interface` keyword (unlike Java or C#). An "interface" is just an abstract class containing **only** pure virtual functions (plus a virtual destructor) and no data.

### Abstraction vs. Encapsulation

These two are easy to confuse because they work together:

| | [Encapsulation](01-Encapsulation.md) | Abstraction |
| --- | --- | --- |
| Focus | **Protecting** the data | **Simplifying** the interface |
| Question it answers | "Who is allowed to touch this?" | "What does the user actually need to know?" |
| C++ tools | `private`, `public`, getters/setters | Abstract classes, pure virtual functions |

Encapsulation hides the *data*. Abstraction hides the *complexity*.

### Example of Abstraction in C++:

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Abstract class (contains at least one pure virtual function)
class Shape {
public:
    // Pure virtual functions: every concrete shape MUST implement these
    virtual double area() const = 0;
    virtual void draw() const = 0;

    // A regular virtual function CAN have a default implementation
    virtual void description() const {
        cout << "This is a shape with area " << area() << endl;
    }

    virtual ~Shape() {}   // Virtual destructor: required when deleting through Shape*
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }
    void draw() const override {
        cout << "Drawing a circle." << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }
    void draw() const override {
        cout << "Drawing a rectangle." << endl;
    }
    void description() const override {   // Optional: replace the default
        cout << "This is a " << width << "x" << height << " rectangle." << endl;
    }
};

int main() {
    // Shape s;   // Compile error: cannot instantiate abstract class 'Shape'

    vector<Shape*> shapes = { new Circle(2.0), new Rectangle(3.0, 4.0) };

    // This loop only knows about Shape. It has no idea how circles or rectangles work.
    for (Shape* s : shapes) {
        s->draw();
        s->description();
    }
    // Drawing a circle.
    // This is a shape with area 12.5664
    // Drawing a rectangle.
    // This is a 3x4 rectangle.

    for (Shape* s : shapes) {
        delete s;
    }
    return 0;
}
```

### Key Concepts in the Example:

1. **Abstract Class**:
   - `Shape` is abstract because it contains pure virtual functions (`area()` and `draw()`, marked `= 0`).
   - You can't create a `Shape` object, but you **can** have `Shape*` pointers and `Shape&` references that refer to derived objects.
2. **Concrete Derived Classes**:
   - `Circle` and `Rectangle` **must** implement `area()` and `draw()`. If a derived class forgets one, it is also abstract and can't be instantiated.
   - `description()` is *not* pure, so derived classes can use the default (`Circle`) or override it (`Rectangle`).
3. **Abstraction in Action**:
   - The loop in `main()` works entirely with the `Shape` interface. How a circle computes its area, or what data a rectangle stores, is hidden. **You know every `Shape` can be drawn and has an area, and that's all you need to know.**
   - Notice the default `description()` calls `area()`. The base class uses behavior it doesn't implement itself, and each derived class fills in its own version.

### A Pure Interface Example:

```cpp
class Printable {
public:
    virtual void print() const = 0;
    virtual ~Printable() {}
};

// Any class can "sign the contract" by inheriting and implementing print()
class Invoice : public Printable {
public:
    void print() const override { cout << "Invoice #1001" << endl; }
};
```

`Printable` is purely a **contract**: "if you are `Printable`, you promise to have a `print()` method."

### Benefits of Abstraction:

1. **Simplifies Complex Systems**: callers work at a high level (`s->draw()`) without worrying about implementation details.
2. **Flexibility and Maintainability**: add a `Triangle` later and none of the code that uses `Shape` has to change.
3. **Enforces a Contract**: pure virtual functions guarantee at compile time that every concrete shape implements the required methods.
4. **Reusability**: shared behavior (like the default `description()`) lives in the base class, and only unique behavior goes in derived classes.

### Summary:

Abstraction hides complex details behind a simple interface. In C++, it is achieved with **abstract classes** and **pure virtual functions** (`= 0`), which derived classes must implement. Abstract classes can't be instantiated, but pointers and references to them are how you write general code that works with every derived type. Abstraction relies on [polymorphism](02-Polymorphism.md) to call the right implementation at runtime.
