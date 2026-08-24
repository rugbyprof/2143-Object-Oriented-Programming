# 2143 Object-Oriented Programming

## Fall 2026

### General Course Information

- **Days:** Monday / Wednesday / Friday
- **Time:** 11:00 a.m. – 11:50 a.m.
- **Location:** Bolin 103
- **Semester:** Monday August 23<sup>rd</sup> – Friday December 4<sup>th</sup>
- **Labor Day:** Monday September 7<sup>th</sup>
- **Thanksgiving Holiday:** Wednesday November 25<sup>th</sup> – Sunday November 29<sup>th</sup>
- **Last Day for “W”:** Monday November 23<sup>rd</sup>
- **Last Day of Class:** Friday December 4<sup>th</sup>
- **Final Exam:** Monday December 7<sup>th</sup>, 10:30 a.m. – 12:30 p.m.

---

# Course Description

Object-oriented programming is often introduced as a collection of terms:

- classes;
- objects;
- encapsulation;
- inheritance;
- polymorphism; and
- abstraction.

Those ideas are important, but knowing their definitions is not the same as knowing how to design good software.

This course approaches object-oriented programming from a broader perspective:

> **How can we design our own types so they behave like natural parts of the programming language?**

In C++, classes allow programmers to create new abstractions that can behave much like built-in types.

A well-designed `Fraction`, `Vector`, `Matrix`, `Date`, `BigInteger`, `Graph`, or `PriorityQueue` should not merely store data. It should provide operations that make sense for the abstraction and allow programmers to use the type naturally.

For example, if two objects represent mathematical values, expressions such as

```cpp
c = a + b;

if (a < b) {
    ...
}
```

may be more expressive than interfaces such as

```cpp
c = a.add(b);

if (a.isLessThan(b)) {
    ...
}
```

The purpose of object-oriented programming is therefore not simply to "put everything in classes."

Instead, we will study how classes can be used to:

- represent meaningful abstractions;
- protect invariants;
- manage resources;
- define clear interfaces;
- model relationships;
- support reusable algorithms;
- hide implementation details; and
- make programs easier to reason about.

---

# Course Philosophy

There is no single programming paradigm that is appropriate for every problem.

Likewise, there is no single object-oriented technique that should be applied everywhere.

In particular:

> **Inheritance is a tool, not the objective of object-oriented programming.**

Beginning programmers often learn inheritance early and consequently begin looking for inheritance relationships everywhere.

Sometimes inheritance provides an elegant solution.

Sometimes composition is better.

Sometimes templates are better.

Sometimes a simple function and a `struct` are better.

And sometimes the best solution is not particularly object-oriented at all.

An important goal of this course is learning to recognize those differences.

Rather than asking:

> "How can I use inheritance here?"

we will learn to ask:

> **"What abstraction am I trying to create, and what interface should that abstraction provide?"**

Implementation decisions should follow from that question.

---

# The Central Theme of the Course

The central theme of this course is:

> ## Designing Types That Belong in the Language

C++ is particularly well suited to this idea because programmers can define types that participate in many of the same language mechanisms as built-in types.

A user-defined type can:

- be constructed;
- copied;
- moved;
- assigned;
- compared;
- printed;
- stored in containers;
- passed to algorithms;
- indexed;
- iterated;
- added or subtracted;
- converted;
- parameterized by another type; and
- used polymorphically when appropriate.

Our goal is not merely to create classes that compile.

Our goal is to create classes that are **easy to understand and difficult to misuse**.

---

# Expected Background

Students entering this course should already understand basic programming concepts including:

- variables and primitive types;
- conditions;
- loops;
- functions;
- parameters and return values;
- arrays;
- basic pointers and references;
- fundamental data structures;
- array-based versus linked structures; and
- the basic idea of a class containing data and methods.

This course will revisit some of these ideas, but they will increasingly be viewed from the perspective of **type and software design** rather than introductory programming syntax.

---

# Learning Objectives

By the end of the course, students should be able to:

1. Design classes that represent meaningful software abstractions.

2. Distinguish between an object's **public interface** and its internal implementation.

3. Use constructors to establish valid object state and maintain class invariants.

4. Explain object lifetime and the role of constructors, destructors, copying, and moving.

5. Apply RAII and modern C++ ownership techniques to manage resources safely.

6. Explain the Rule of Three, Rule of Five, and Rule of Zero and recognize when each is relevant.

7. Design overloaded operators whose behavior is consistent with the meaning of the represented abstraction.

8. Implement value-like user-defined types that can be copied, compared, assigned, printed, and used naturally in expressions.

9. Distinguish among association, aggregation, composition, and inheritance.

10. Prefer composition when an object **has** another capability or component and use inheritance when a genuine substitutable **is-a** relationship exists.

11. Explain static versus dynamic polymorphism.

12. Design interfaces using abstract base classes and virtual functions when runtime polymorphism is appropriate.

13. Use templates to write algorithms and data structures that operate across multiple types.

14. Understand how iterators connect user-defined containers with generic algorithms.

15. Use standard library containers and algorithms effectively.

16. recognize common ownership, lifetime, aliasing, and object-slicing problems.

17. Apply exceptions appropriately while maintaining valid object state.

18. Identify unnecessary coupling, poor abstractions, duplicated code, and other common design problems.

19. Refactor an existing design toward clearer responsibilities and interfaces.

20. Evaluate whether an object-oriented design is actually appropriate for a given problem.

21. Explain and defend important design decisions in their own programs.

---

# Major Course Themes

The semester will be organized around several recurring questions rather than a rigid sequence of isolated vocabulary terms.

---

## Theme 1 — What Is a Type?

We begin with one of the most important ideas in the course:

> A class is not merely a collection of variables and functions.

A class defines a **type**.

A type determines:

- what values can exist;
- what operations are valid;
- what states are permitted;
- how objects are created;
- how objects are copied or moved;
- how objects are destroyed; and
- how objects interact with the rest of the language.

Topics include:

- classes and objects;
- `struct` versus `class`;
- public and private interfaces;
- access control;
- member functions;
- `const` correctness;
- class invariants;
- abstraction;
- encapsulation;
- namespaces; and
- separating interface from implementation.

---

## Theme 2 — Object Lifetime and Ownership

Objects exist for some period of time, and understanding that lifetime is fundamental to C++ programming.

Topics include:

- object construction;
- default constructors;
- parameterized constructors;
- constructor delegation;
- member initializer lists;
- destructors;
- scope and lifetime;
- stack versus dynamic storage;
- pointers and references;
- ownership;
- resource management;
- RAII;
- smart pointers;
- copy constructors;
- copy assignment;
- move constructors;
- move assignment;
- shallow versus deep copying;
- Rule of Three;
- Rule of Five; and
- Rule of Zero.

The important question is not simply:

> "Where do I call `delete`?"

The better question is:

> **"Who owns this resource, and how is that ownership represented?"**

---

## Theme 3 — Making User-Defined Types Feel Natural

This theme represents one of the central ideas of the course.

Well-designed abstractions should provide operations that match what the represented objects actually mean.

Possible example types include:

- `Fraction`;
- `Complex`;
- `Vector`;
- `Matrix`;
- `Date`;
- `Time`;
- `Money`;
- `BigInteger`;
- `Point`;
- `Polynomial`;
- custom containers; and
- graph-related structures.

Topics include:

- function overloading;
- operator overloading;
- arithmetic operators;
- comparison operators;
- assignment operators;
- stream insertion and extraction;
- indexing with `operator[]`;
- function-call operators;
- conversion constructors;
- conversion operators;
- `explicit`;
- equality;
- ordering; and
- C++20 three-way comparison (`<=>`) where appropriate.

Operator overloading is not about creating clever syntax.

It is about allowing an abstraction to participate naturally in the language.

An overloaded operator should therefore behave in a way that is unsurprising to someone reading the code.

---

## Theme 4 — Relationships Between Objects

Large programs are constructed by connecting smaller abstractions.

We will examine several ways objects can relate to one another.

Topics include:

- association;
- aggregation;
- composition;
- dependency;
- ownership;
- object lifetime relationships;
- dependency injection;
- inheritance; and
- interface relationships.

A recurring design question will be:

> **Should this relationship be expressed through composition or inheritance?**

For example:

```text
Car HAS-A Engine
```

is fundamentally different from:

```text
Circle IS-A Shape
```

Even apparently reasonable inheritance relationships will be examined carefully to determine whether substitutability actually exists.

---

## Theme 5 — Inheritance and Runtime Polymorphism

Inheritance remains an important object-oriented technique, but it will be studied as one design mechanism among several.

Topics include:

- base and derived classes;
- protected members;
- constructor/destructor behavior in inheritance hierarchies;
- overriding;
- virtual functions;
- pure virtual functions;
- abstract classes;
- runtime polymorphism;
- virtual destructors;
- object slicing;
- references and pointers to base classes;
- `override`;
- `final`; and
- substitutability.

We will pay particular attention to distinguishing:

### Code reuse

from

### Type relationships

Inheritance should not be introduced simply because two classes happen to share some code.

---

## Theme 6 — Composition Before Inheritance

One of the recurring principles of the course will be:

> **Build complex behavior from smaller objects whenever that produces a simpler design.**

Students will practice designing classes whose capabilities emerge through collaboration with other objects.

Topics include:

- composition;
- delegation;
- dependency injection;
- interchangeable components;
- reducing coupling;
- cohesive classes;
- separating responsibilities; and
- refactoring inheritance-heavy designs.

Students should leave the course comfortable saying:

> "This does not need a base class."

That sentence alone may save several thousand lines of software during their careers.

---

## Theme 7 — Generic Programming

Not every form of polymorphism requires inheritance.

C++ templates allow algorithms and containers to operate on types that provide the required behavior.

Topics include:

- function templates;
- class templates;
- template parameters;
- generic algorithms;
- type requirements;
- compile-time polymorphism;
- templates versus virtual functions; and
- C++ concepts where appropriate.

We will compare:

### Runtime polymorphism

```cpp
Shape* s;
s->draw();
```

with:

### Compile-time polymorphism

```cpp
template <typename T>
void print(const T& value);
```

These solve different problems.

Neither is automatically superior.

---

## Theme 8 — Containers, Iterators, and the STL

The Standard Template Library is one of the best examples of types designed to work together through common interfaces.

Topics include:

- `vector`;
- `list`;
- `deque`;
- `stack`;
- `queue`;
- maps and sets;
- iterators;
- ranges;
- algorithms;
- predicates;
- lambdas;
- sorting;
- searching; and
- designing user-defined types that work correctly with standard containers and algorithms.

An important goal is understanding **why** an object can be placed into something such as:

```cpp
std::vector<MyType>
```

and what responsibilities `MyType` has when we do so.

---

## Theme 9 — Interfaces and Contracts

A good class communicates what callers may safely do with it.

Topics include:

- public APIs;
- preconditions;
- postconditions;
- invariants;
- `const` correctness;
- exceptions;
- exception safety;
- error handling;
- assertions;
- defensive programming; and
- documentation.

We will emphasize that encapsulation does not mean:

> "Make all your variables private."

It means protecting the assumptions necessary for an abstraction to remain valid.

---

## Theme 10 — Designing for Change

Software changes.

Good design attempts to localize that change.

Topics may include:

- coupling;
- cohesion;
- separation of concerns;
- Single Responsibility Principle;
- Open/Closed Principle;
- Dependency Inversion;
- selected SOLID principles;
- refactoring;
- code smells; and
- testing object-oriented code.

SOLID will be treated as a collection of **design heuristics**, not commandments brought down from Mount UML.

Students should be able to explain why a design is useful rather than merely stating the name of a principle.

---

## Theme 11 — Design Patterns Without Pattern Worship

Selected design patterns may be introduced when they solve a problem that naturally appears in class.

Possible examples include:

- Strategy;
- Factory;
- Observer;
- Adapter;
- Iterator;
- Command; and
- Decorator.

Patterns will not be taught primarily as vocabulary to memorize.

Instead, we will begin with a design problem and examine whether a known pattern provides a useful solution.

Students should never reach the point where the presence of twelve design patterns is considered evidence that twelve design patterns were necessary.

---

## Theme 12 — When Not to Use OOP

An advanced understanding of object-oriented programming includes recognizing when it is not particularly useful.

We will periodically compare object-oriented solutions with:

- free functions;
- simple structures;
- generic programming;
- procedural designs;
- functional techniques; and
- data-oriented approaches.

The question is never:

> **"How do we make this object-oriented?"**

The better question is:

> **"What design makes this problem easiest to understand, implement, test, and maintain?"**

---

# Core Technical Topics

The following topics form the technical core of the course.

### Classes and Types

- Classes and objects
- `struct` versus `class`
- Interfaces and implementation
- Access control
- Encapsulation
- Abstraction
- Class invariants
- `const` correctness
- Static members

### Construction and Lifetime

- Constructors
- Member initialization
- Destructors
- Object lifetime
- Copy semantics
- Move semantics
- Rule of Three
- Rule of Five
- Rule of Zero
- RAII
- Smart pointers
- Resource ownership

### Natural Interfaces

- Function overloading
- Operator overloading
- Assignment
- Arithmetic operators
- Comparison
- Stream operators
- Indexing
- Conversions
- `explicit`

### Object Relationships

- Association
- Aggregation
- Composition
- Delegation
- Dependency
- Inheritance

### Polymorphism

- Overriding
- Virtual functions
- Abstract base classes
- Runtime polymorphism
- Interfaces
- Object slicing
- Virtual destructors
- Substitutability

### Generic Programming

- Function templates
- Class templates
- Generic algorithms
- Static polymorphism
- Concepts
- Type requirements

### Standard Library Integration

- Containers
- Iterators
- Algorithms
- Lambdas
- Ranges where appropriate

### Software Design

- Cohesion
- Coupling
- Separation of responsibilities
- Composition versus inheritance
- Selected SOLID principles
- Refactoring
- Code smells
- Selected design patterns
- Unit testing

### Supporting Topics

As needed throughout projects:

- File I/O
- Exception handling
- UML
- debugging;
- project organization;
- header/source separation;
- build tools; and
- Git/GitHub workflow.

---

# Tentative Course Progression

The exact order may change according to class progress, student questions, and programming projects.

## Part I — Building Better Types

- Classes as user-defined types
- Interfaces and implementation
- Encapsulation
- Constructors
- `const`
- Class invariants
- Operator overloading

## Part II — Objects Have Lifetimes

- Destructors
- Copying
- Assignment
- Dynamic resources
- RAII
- Smart pointers
- Move semantics
- Rule of Three/Five/Zero

## Part III — Objects Work Together

- Composition
- Association
- Aggregation
- Dependencies
- Delegation
- Interface design

## Part IV — Polymorphism

- Inheritance
- Overriding
- Virtual functions
- Abstract classes
- Substitutability
- Composition versus inheritance

## Part V — Types Work With Algorithms

- Templates
- Generic programming
- Containers
- Iterators
- Algorithms
- Concepts

## Part VI — Designing Larger Programs

- Coupling and cohesion
- SOLID
- Refactoring
- Selected design patterns
- Testing
- Project architecture

## Part VII — Choosing the Right Design

The semester concludes by returning to the central question:

> **What abstraction makes this program easier to understand and use?**

Students should be able to compare several designs rather than assuming that the most elaborate object hierarchy is automatically the most sophisticated solution.

---

# Programming Projects

Programming assignments will emphasize the construction and evolution of useful abstractions.

Students may begin with relatively simple classes and progressively add capabilities such as:

- construction;
- copying;
- comparisons;
- arithmetic;
- input/output;
- iteration;
- templates;
- composition;
- polymorphism; and
- integration with the standard library.

Projects should demonstrate not merely that the program produces correct output, but that the program's **types and interfaces are well designed**.

An important question throughout the semester will be:

> **What does the code that USES your class look like?**

If using a class requires extensive knowledge of its internal implementation, the abstraction probably needs improvement.

---

# Project Evaluation

Programming projects may be evaluated according to several dimensions:

- correctness;
- class design;
- interface quality;
- appropriate abstraction;
- readability;
- use of language features;
- resource safety;
- documentation;
- testing;
- project organization; and
- the student's ability to explain the implementation.

A complicated solution will not automatically receive more credit than a simple solution.

In fact, when two solutions accomplish the same task reliably:

> **The simpler design is usually the more impressive one.**

---

# The Question Behind the Course

By the end of the semester, students should no longer look at every programming problem and immediately ask:

> "What should my base class be?"

Instead, they should ask:

- What concept am I trying to represent?
- What operations naturally belong to it?
- What states are valid?
- Who owns its resources?
- Should this object have value semantics?
- Should objects be copied?
- Should they be movable?
- What relationships exist among the objects?
- Is this relationship composition or inheritance?
- Do I need runtime polymorphism?
- Would templates solve the problem more simply?
- Can my type work naturally with the standard library?
- Can callers use this type without knowing how it is implemented?
- Am I introducing complexity that the problem does not require?

If the answers lead to inheritance, use inheritance.

If they lead to composition, use composition.

If they lead to templates, use templates.

And if the best solution is a three-function program with no classes at all:

**write the three-function program.**

The goal of object-oriented programming is not to maximize the number of objects.

The goal is to create useful abstractions.

There are several changes in there that I think would materially improve **what students think this course is about**.

### I would make operator overloading a first-class topic

This is where your existing philosophy differs from a lot of generic OOP courses, and I think you should lean into it.

Consider a `Fraction`:

```cpp
Fraction a{1, 2};
Fraction b{3, 4};

Fraction c = a + b;

if (c > 1) {
    cout << c << '\n';
}
```

That little example contains a staggering amount of OOP/C++:

- abstraction;
- constructors;
- invariants;
- private representation;
- `const`;
- operator overloading;
- conversions;
- stream operators;
- comparison;
- value semantics;
- copy/move behavior;
- interface design.

And the final program doesn't scream:

```text
ATTENTION! OBJECT-ORIENTED PROGRAMMING IS OCCURRING!
```

It just looks like C++.

**That is exactly the point.**

C++ even gives you newer tools that fit this philosophy. C++20's `<=>` operator can supply natural ordering semantics, and C++20 concepts let generic algorithms express things like *"I don't care what class you inherited from; I care whether your type supports the operations I require."* 

That is a powerful progression:

```text
class
  ↓
type
  ↓
interface
  ↓
value semantics
  ↓
operators
  ↓
STL compatibility
  ↓
generic programming
```

rather than:

```text
class
  ↓
inheritance
  ↓
more inheritance
  ↓
AbstractFactoryObserverSingletonManagerFactory
  ↓
sadness
```

### I'd significantly demote "the four pillars"

You still teach:

**Encapsulation → Abstraction → Inheritance → Polymorphism**

but don't organize the semester around them.

In fact, I'd tell students something like:

> These are useful words for discussing OOP. They are not a recipe for designing a program.

That's an important distinction.

I'd make **abstraction and encapsulation foundational**, while **inheritance and runtime polymorphism become specific mechanisms** encountered later.

### Composition versus inheritance should become a recurring argument

Not one lecture.

I'd keep returning to it.

Give them something like:

```text
Robot
 ├── Motor
 ├── Sensor
 ├── Battery
 └── Controller
```

and ask:

> Should `Robot` inherit from `Motor`?

They laugh.

Then:

```text
ElectricCar : Car
```

looks perfectly reasonable.

Then you start asking whether every `Car` operation makes sense, whether substitutability really holds, whether capabilities should be components instead, etc.

That's where actual design judgment begins.

### I'd teach Rule of Zero *after* making them suffer just enough

I wouldn't skip manual memory management.

They need to build something owning:

```cpp
T* data;
```

and implement a destructor/copy constructor/copy assignment so they understand the problem.

Then teach move semantics.

Then show them:

```cpp
std::vector<T> data;
```

and say:

> Congratulations. Now delete 80 lines of code.

That makes the **Rule of Zero** meaningful instead of magical. Modern C++ guidance explicitly encourages avoiding custom default operations when ownership can be delegated to proper resource-managing members. 

I'd probably frame that progression as:

```text
Understand ownership manually
           ↓
Understand why RAII exists
           ↓
Use RAII
           ↓
Prefer Rule of Zero
```

That's much better than pretending pointers don't exist.

### And templates belong in OOP more than your old list implies

This is one area where I'd modernize the course pretty aggressively.

Students often leave OOP thinking:

> polymorphism = virtual functions

But C++ has **two major polymorphic worlds**.

Runtime:

```cpp
Shape* s = new Circle;
s->draw();
```

Compile time:

```cpp
template <Drawable T>
void render(const T& thing) {
    thing.draw();
}
```

Those are fundamentally different design tools.

With concepts, the second can effectively say:

> I don't care who your parents are. Show me that you can `draw()`.

Which is wonderfully subversive immediately after spending three weeks teaching inheritance. 😄

### One thing I'd outright remove

Your old list has:

> **Multithreading in OOP**

I'd delete it from this course.

Not because concurrency isn't important—it obviously is—but because **it doesn't teach anything fundamental about OOP** and you've already got more than enough material.

Likewise, I'd move file I/O, exception handling, UML, and testing into **supporting techniques that appear when projects require them**, rather than presenting each as an independent OOP pillar.

That buys you room for topics that are much more authentically *modern C++ object design*:

**RAII, ownership, move semantics, Rule of Zero, value semantics, composition, generic programming, iterators, STL integration, concepts, and interface design.**

Those are far more valuable to a student leaving a C++ OOP course in 2026.

And I think you've now got a nice pairing between your two courses:

> **Advanced Database:**  
> *Don't ask which database is best. Ask what guarantees and workload the problem requires.*

> **Object-Oriented Programming:**  
> *Don't ask which OOP feature you can use. Ask what abstraction the problem requires.*

That's a pretty coherent philosophy across the curriculum.