<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: T02
name: T02
title: Test 2 — Constructors, Inheritance, and Polymorphism
description: Exam 2 study guide, combining Quiz 04 and Quiz 06 along with worksheets
  W04, W05 and W06
category: Assignments
date_due:
  month: '10'
  day: '23'
  year: 2026
  hour: 11
```

</details>

## Test 2 — Study Guide

Test 2 covers the material from these two quizzes and three worksheets. They are your study guide: if you can work every question on them (and check yourself against the keys), you are ready.

| Type      | Folder         | Title                              |
| :-------- | :------------- | :--------------------------------- |
| Quiz      | [Q04](../Q04/) | Inheritance                        |
| Quiz      | [Q06](../Q06/) | Polymorphism                       |
| Worksheet | [W04](../W04/) | Constructors and Initializer Lists |
| Worksheet | [W05](../W05/) | Inheritance                        |
| Worksheet | [W06](../W06/) | Polymorphism                       |

> There is no Quiz 05. Quiz 04 is based on Worksheet 05, and Quiz 06 is based on Worksheet 06.

## Question Types

Expect the same style as Test 1: mostly multiple choice built around short code snippets (predict the output, does it compile, find the error), plus a short answer or two where you write a small class or function.

## Topics

### Constructors and Initializer Lists (W04)

- Default, overloaded, and copy constructors, and which one a given line calls
- Member initializer lists, and when they are required (`const` members, references, members with no default constructor, base classes)
- Initialization happens in **declaration** order, not initializer-list order
- Shallow vs. deep copy

### Inheritance (W05, Q04)

- What inheritance is ("is-a") and the syntax `class Derived : public Base`
- Access control in a hierarchy: what a derived class and `main()` can reach for `public`, `protected`, and `private` base members
- Constructor chaining: calling the base constructor from the derived initializer list
- Constructor and destructor **order** (base built first, destroyed last)
- Overriding vs. overloading, and calling the base version (`Base::print()`) from an override
- Hierarchical inheritance (several classes deriving from one base)

### Polymorphism (W06, Q06)

- Static (compile-time) vs. dynamic (run-time) binding, and what `virtual` changes
- Compile-time polymorphism (overloading, operators, templates) vs. run-time polymorphism (`virtual` + base pointers/references)
- The `override` keyword and the signature rules: same name, same parameter types, same `const`, and the base function must be `virtual`
- The silent bug: a derived function that *hides* instead of overriding
- Object slicing: passing by value and `vector<Base>` vs. pointers/references
- One loop over a mixed container (`vector<unique_ptr<Base>>`), where each object runs its own version or falls back to the inherited one
- Virtual destructors: why `delete` through a base pointer needs one
- Abstract classes and pure virtual functions (`= 0`), and what makes a derived class concrete
- vtables and vptrs, at a high level
- The pointer's type decides what you are **allowed to call**; the object's type decides **which version runs** (if it is `virtual`)

## Lecture Notes

The lecture folders explain each concept in more depth:

| Topic                     | Link                                                                                          |
| ------------------------- | --------------------------------------------------------------------------------------------- |
| Copy Constructor          | [03-CopyConstructor](../../Lectures/OOP_Fundamentals/03-CopyConstructor/)                     |
| Inheritance               | [04-Inheritance](../../Lectures/OOP_Fundamentals/04-Inheritance/)                             |
| Override & Const          | [08-Override&Const](../../Lectures/OOP_Fundamentals/08-Override&Const/)                       |
| Inheritance Access Levels | [12-Inheritance_Access_Levels](../../Lectures/OOP_Fundamentals/12-Inheritance_Access_Levels/) |
| Static Polymorphism       | [12-Static_Polymorphism](../../Lectures/OOP_Fundamentals/12-Static_Polymorphism/)             |
| Run-Time Polymorphism     | [13-Run_Time_Polymorphism](../../Lectures/OOP_Fundamentals/13-Run_Time_Polymorphism/)         |
