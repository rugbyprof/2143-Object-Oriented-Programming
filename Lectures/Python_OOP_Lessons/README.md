# OOP Battle Arena — Python OOP Series

An eight-lesson, student-facing introduction to Python object-oriented programming. Each lesson includes learning objectives, runnable Python 3 examples, common mistakes, exercises, a mini-lab, and review questions.

| Number | File name                    | Description                                                                                                          |
| -----: | ---------------------------- | -------------------------------------------------------------------------------------------------------------------- |
|      1 | [Lesson_01.md](Lesson_01.md) | Classes, instance and class attributes, methods, `self`, `__init__`, inspection, and introductory dunders.           |
|      2 | [Lesson_02.md](Lesson_02.md) | Inheritance, method overriding, `super()`, polymorphism, composition, and a first look at the MRO.                   |
|      3 | [Lesson_03.md](Lesson_03.md) | Encapsulation conventions, properties, validation, read-only values, and name mangling.                              |
|      4 | [Lesson_04.md](Lesson_04.md) | Dunder protocols for representations, equality, hashing, ordering, operators, containers, iteration, and truthiness. |
|      5 | [Lesson_05.md](Lesson_05.md) | Docstrings, `help()`, introspection, annotations, and designing discoverable public APIs.                            |
|      6 | [Lesson_06.md](Lesson_06.md) | Class methods, static methods, decorators, alternate constructors, dataclasses, and frozen value objects.            |
|      7 | [Lesson_07.md](Lesson_07.md) | Modules, packages, imports, `__init__.py`, `__main__.py`, and organizing a runnable project.                         |
|      8 | [Lesson_08.md](Lesson_08.md) | Pythonic OOP design with composition, abstract base classes, protocols, type hints, and dependency injection.        |

## Lesson summaries

### [Lesson 1](Lesson_01.md) — Python’s Object Model: Classes, Attributes, Methods, and Dunders

Students begin by creating classes and instances, storing data in attributes, and writing methods with `self`. The lesson distinguishes instance attributes from class attributes, demonstrates the mutable class-attribute pitfall, and introduces `__init__`, `__dict__`, `type()`, `dir()`, `help()`, `__str__`, `__repr__`, and fundamental protocol methods.

### [Lesson 2](Lesson_02.md) — Inheritance Arena: Reuse, Overrides, `super()`, and Polymorphism

Students learn when a subclass genuinely “is a” specialized version of a parent class. They practice extending initialization with `super()`, overriding methods safely, using polymorphism in loops, choosing composition where it fits better, and reading a simple multiple-inheritance method resolution order.

### [Lesson 3](Lesson_03.md) — Guarded Gate: Encapsulation, Properties, and Validation

Students use underscore conventions and `@property` to protect an object’s valid state without abandoning Python’s natural attribute syntax. The lesson covers getters, setters, read-only computed properties, validation choices, recursion pitfalls, deleters, and the limits of double-underscore name mangling.

### [Lesson 4](Lesson_04.md) — Secret Handshakes: Dunder Protocols, Operators, and Iteration

Students make custom objects behave naturally with Python’s built-in syntax. They implement representations, equality, hashing, sorting, addition-like operations, `len()`, membership tests, indexing, iteration, and truthiness—while learning when a protocol would clarify rather than confuse a design.

### [Lesson 5](Lesson_05.md) — Field Guide: Docstrings, `help()`, Introspection, and Clear APIs

Students learn to make classes understandable to their future selves and other programmers. Topics include docstrings, `help()`, `dir()`, `vars()`, `__dict__`, dynamic attribute helpers, `inspect`, type annotations, and how to define a small, stable public API.

### [Lesson 6](Lesson_06.md) — Class Workshop: Class Methods, Static Methods, Decorators, and Dataclasses

Students distinguish behavior tied to an instance, a class, or neither. They build alternate constructors with `@classmethod`, evaluate when `@staticmethod` is appropriate, see the mechanics of decorators, and use `@dataclass`, `default_factory`, `__post_init__`, and `frozen=True` for practical value objects.

### [Lesson 7](Lesson_07.md) — Map Room: Modules, Packages, Imports, and `__main__`

Students move beyond a single file and organize an OOP project into focused modules and packages. The lesson explains clear import styles, `__init__.py`, relative imports, the main guard, `__main__.py`, import-time behavior, circular imports, and running packages with `python -m`.

### [Lesson 8](Lesson_08.md) — Pythonic OOP Design: Composition, Abstract Classes, Protocols, and Type Hints

Students finish by choosing designs intentionally. They compare composition and inheritance, use abstract base classes and structural protocols, write type hints, inject collaborators for flexibility, and refactor growing conditional logic into focused polymorphic behavior only when that added structure earns its place.

---

**Suggested capstone:** create a small Battle Arena package that uses the series’ classes, properties, dunder methods, dataclasses, package structure, and protocol-driven game rules.
