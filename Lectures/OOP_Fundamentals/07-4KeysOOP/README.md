## The 4 Keys of OOP

Object-oriented programming rests on four core principles. Each has its own page:

| # | Principle | One-line idea | Key C++ tools |
| --- | --- | --- | --- |
| 1 | [Encapsulation](01-Encapsulation.md) | Keep data private and control access to it | `private`, `public`, getters/setters |
| 2 | [Polymorphism](02-Polymorphism.md) | One interface, many behaviors | Overloading, `virtual`, `override` |
| 3 | [Abstraction](03-Abstraction.md) | Show *what* an object does, hide *how* | Abstract classes, pure virtual functions (`= 0`) |
| 4 | [Inheritance](04-Inheritance.md) | Build new classes from existing ones ("is-a") | `class Derived : public Base`, `virtual` inheritance |

### How They Fit Together

- **Encapsulation** protects each object's data.
- **Inheritance** lets classes share and extend behavior.
- **Abstraction** defines a common interface (usually an abstract base class).
- **Polymorphism** lets code written against that interface work with every derived class at runtime.

A typical design uses all four at once: an abstract `Shape` base class (**abstraction**) with private data in each derived class (**encapsulation**), `Circle` and `Rectangle` deriving from it (**inheritance**), and a `vector<Shape*>` that calls `draw()` on each one (**polymorphism**).
