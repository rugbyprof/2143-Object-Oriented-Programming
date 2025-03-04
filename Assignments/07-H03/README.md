# Homework - Inheritance in OOP

#### Due: 03-25-2025 (Tuesday)

Inheritance is another fundamental concept of object-oriented programming (OOP). It allows you to create new classes (derived classes) based on existing ones (base classes), enabling **reusability**, **extensibility**, and a clearer **hierarchy** of types. This assignment focuses on **why** and **how** to use inheritance in practical scenarios.

---

## Objectives

1. **Identify** different types of inheritance (single, multiple, hierarchical).
2. **Explain** how derived classes extend or override base class functionality.
3. **Discuss** advantages and pitfalls of inheritance in real-world software.

---

## Part A: Conceptual Questions

1. **Inheritance Definition**

   - In your own words, define **inheritance**.
   - How does it differ from **composition** or **aggregation** in creating complex objects?

2. **Types of Inheritance**

   - List **two** forms of inheritance (e.g., single vs. multiple).
   - Provide a brief example of when each type might be appropriate.

3. **Overriding Methods**

   - Explain how **method overriding** in a derived class helps tailor or extend the base class’s functionality.
   - Why might you **override** a method instead of simply adding a new method in the derived class?

4. **Real-World Analogy**
   - Describe a real-life scenario (outside of programming) where an item or concept “inherits” characteristics from another.
   - Discuss how that real-life example aligns with the OOP concept of inheritance.

---

## Part B: Minimal Coding or UML (Choose One)

> **Note:** The coding requirement is minimal. You can choose a class diagram (UML) approach if preferred.

### **Option 1: Minimal Coding**

1. **Base Class**

   - Create a simple base class called `Vehicle` with:
     - A `brand` attribute (or `manufacturer`).
     - A method `drive()` that prints something generic like "Vehicle is driving."

2. **Derived Class**

   - Define a derived class `Car` that inherits from `Vehicle`.
   - Add a new attribute (e.g., `doors`) and override the `drive()` method to show it’s a car specifically driving.

3. **Short Driver Code**
   - Demonstrate creating a `Vehicle` object and a `Car` object.
   - Call `drive()` on both to illustrate the difference.

> This can be pseudo-code if desired—focus on the inheritance structure rather than language syntax.

### **Option 2: UML Diagram**

1. **UML Class Diagram**

   - Draw a class diagram showing `Vehicle` (base class) and `Car` (derived class).
   - Indicate which attributes and methods belong to each, and how `Car` extends or overrides aspects of `Vehicle`.

2. **Brief Explanation**
   - In a short paragraph, explain how the derived class (`Car`) inherits from the base class (`Vehicle`) and what unique functionality or data it adds.

---

## Part C: Short Reflection & Discussion

1. **When to Use Inheritance**

   - Provide one scenario in which inheritance is clearly beneficial, and one scenario in which inheritance might be overkill or lead to a fragile design.

2. **Method Overriding vs. Overloading**

   - Differentiate **method overriding** (runtime polymorphism) and **method overloading** (compile-time).
   - Why does inheritance rely heavily on overriding for real flexibility?

3. **Inheritance vs. Interfaces/Abstract Classes**

   - In some languages, we define **abstract classes** or **interfaces**.
   - How does the concept of **inheritance** differ from **implementing an interface** (or an abstract base class)?

4. **Pitfalls of Multiple Inheritance**
   - Name one potential problem with **multiple inheritance** (e.g., diamond problem).
   - Suggest a strategy or approach (like virtual inheritance in C++ or an interface-based design) to mitigate this issue.

---

## Part D: (Optional) Research

1. **Inheritance in Different Languages**

   - Compare how two languages (e.g., Java and C++) handle inheritance.
   - Mention any restrictions (e.g., Java lacks multiple class inheritance, C++ supports it with complexities).

2. **Open-Closed Principle**
   - Summarize how the **Open-Closed Principle** (from SOLID) relates to inheritance.
   - Provide a brief example of how a derived class extends functionality without modifying the base class code.

---

## Deliverables

- Create a folder `H03` in your assignments folder and place all work there.
- **Part A–C** are required.
- **Part D** is **optional** (for deeper understanding or extra credit).
- You can provide the minimal code snippet or a short UML diagram for Part B.
- **Format**
  - Acceptable as **text**, **PDF**, or a **markdown** file.
  - Keep code minimal and focus on inheritance structure and reasoning.
- **Grading**
  - **Clarity (40%)**: Demonstrates a clear understanding of inheritance concepts and how they differ from other OOP mechanisms.
  - **Completeness (30%)**: Answers all required questions or tasks in Part A–C.
  - **Relevance (20%)**: Examples and explanations tie back to real OOP usage, not just theoretical knowledge.
  - **Brevity & Organization (10%)**: Concise explanations, well-structured submission, minimal but illustrative code.

---
