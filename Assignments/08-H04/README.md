# Homework - Understanding Polymorphism in OOP

#### Due: 03-25-2025 (Tuesday)

**Polymorphism** is a key principle in OOP that allows objects of different classes to be treated as objects of a common base class. It comes in different forms—most notably **compile-time polymorphism** (method overloading) and **runtime polymorphism** (method overriding). This assignment focuses on understanding **when** and **why** polymorphism is used, along with a minimal demonstration.

---

## Objectives

1. **Differentiate** between compile-time (overloading) and runtime (overriding) polymorphism.
2. **Explain** how virtual functions or abstract methods enable derived classes to provide specific implementations.
3. **Recognize** real-world scenarios where polymorphism provides flexibility and maintainability.

---

## Part A: Conceptual Questions

1. **Definition**

   - In your own words, define polymorphism.
   - Why is polymorphism often considered one of the pillars of OOP?

2. **Compile-Time vs. Runtime**

   - Provide a **one-sentence** explanation of compile-time polymorphism (method overloading).
   - Provide a **one-sentence** explanation of runtime polymorphism (method overriding).
   - Which type requires an inheritance relationship, and why?

3. **Method Overloading**

   - Why might a class have multiple methods with the **same name** but **different parameter lists**?
   - Give a brief example (no full code needed) of how method overloading can simplify user interactions with a class.

4. **Method Overriding**
   - Describe how a derived class **overrides** a base class’s method to provide specialized behavior.
   - In some languages (e.g., C++), the `virtual` keyword or annotations are used. Why might this be needed?

---

## Part B: Minimal Demonstration (Pseudo-code or UML)

> **Note:** Keep code minimal—focus on structure.

### Option 1: Minimal Code (No More Than 20 Lines)

1. **Base Class & Derived Classes**

   - Create a base class `Shape` with an abstract or virtual method: `draw()`.
   - Create two derived classes, `Circle` and `Rectangle`, each overriding `draw()` to print or return a shape-specific action.

2. **Demonstration**
   - Show a short snippet where you create a list/array of `Shape*` or references, store both a `Circle` and a `Rectangle`, and then call `draw()` on each.
   - Emphasize how the correct `draw()` method is chosen **at runtime**.

### Option 2: Short UML Diagram

1. **Class Diagram**
   - Show `Shape` as an abstract class (or interface) with a `draw()` method.
   - Show `Circle` and `Rectangle` as derived classes, each overriding `draw()`.
2. **Brief Explanation**
   - In 2–3 sentences, explain how a generic `Shape` reference can hold either `Circle` or `Rectangle` objects, calling the correct method at runtime.

---

## Part C: Overloading vs. Overriding Distinctions

1. **Overloaded Methods**

   - Imagine a class `Calculator` that has multiple `calculate()` methods, each accepting different parameter types (e.g., `(int, int)`, `(double, double)`).
   - How is **compile-time** resolution used here?

2. **Overridden Methods**
   - In your `Shape` example (or another scenario), the `draw()` method is overridden in derived classes.
   - **When** does the decision for which method to call occur (compile time or runtime)?
   - Why does this matter for flexible code design?

---

## Part D: Reflection & Real-World Applications

1. **Practical Example**

   - Briefly outline a scenario (in a game, a UI framework, or a simulation) where polymorphism is essential.
   - Why does it reduce code duplication or improve design?

2. **Potential Pitfalls**

   - List one possible confusion or pitfall when using **method overloading**.
   - List one potential pitfall when relying heavily on **runtime polymorphism** (e.g., performance, debugging complexity).

3. **Checking Understanding**
   - If a new `Triangle` class is added to your `Shape` hierarchy, how does polymorphism help you **not** modify the existing code that uses `Shape` references?

---

## Deliverables

- Create a folder `H04` in your assignments folder and place all work there.
- **Grading:**
  - **Clarity & Accuracy (40%)**: Demonstrates understanding of polymorphism principles, including method overloading vs. overriding.
  - **Completeness (30%)**: Answers all sections (A, B, C, D as required).
  - **Relevance (20%)**: Provides real-world or code examples that illustrate key points.
  - **Conciseness & Organization (10%)**: Clear structure, minimal but illustrative code or UML.
