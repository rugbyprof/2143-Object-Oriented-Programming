# Homework - Understanding Abstraction in OOP

#### Due: 03-25-2025 (Tuesday)

**Abstraction** is the concept of simplifying complex systems by modeling classes appropriate to the problem, focusing on relevant attributes and behaviors while hiding internal details. This assignment helps students discern how to apply abstraction in class design and why it’s critical for managing complexity.

---

## Objectives

1. **Define** abstraction in your own words.
2. **Identify** when to use abstraction in the design of classes.
3. **Discuss** how abstraction differs from encapsulation, inheritance, and polymorphism.

---

## Part A: Conceptual Questions

1. **Definition**

   - In your own words, what is **abstraction** in OOP?
   - Provide a short real-world analogy illustrating how abstraction hides unnecessary details.

2. **Abstraction vs. Encapsulation**

   - Briefly compare **abstraction** and **encapsulation**.
   - Why might someone confuse the two concepts?

3. **Designing with Abstraction**

   - Imagine you are modeling a **smart thermostat** in a home automation system.
   - List **three** attributes and **two** methods you consider **essential** to the thermostat (from the user’s or system’s perspective).
   - Explain why you would **omit certain internal details** (e.g., circuit design, firmware routines).

4. **Benefits of Abstraction**
   - Name **two** benefits of abstraction in large-scale software projects.
   - In a short sentence, how can abstraction reduce code complexity?

---

## Part B: Minimal Class Example (Pseudo-code)

> Keep any code short implement using C++.

### Scenario:

Model a **Banking System** where you only want certain core operations exposed (like `deposit` and `withdraw`), hiding internal complexities (like encryption, logging, or ledger balancing).

- The BankAccount could be an abstract class, specifying only the interface methods (no concrete details).
- The user interacts with derived classes (like SavingsAccount), which implement the abstract methods but hide the internal mechanics.

## Part C: Reflection & Comparison

1. Distilling the Essentials
   - In your SavingsAccount class, which data or methods would you hide from direct user calls to maintain a clear public interface?
   - Provide a brief explanation.
2. Contrast with Polymorphism
   - If BankAccount is abstract, how does a method call on SavingsAccount highlight polymorphism while also showcasing abstraction?
3. Real-World Example
   - Briefly name another real-world domain (e.g., gaming or healthcare) where abstraction is crucial for a simpler API design.

### (Optional) Additional Exploration

1. Interfaces vs. Abstract Classes
   - Summarize, in two sentences, how an interface differs from an abstract class for expressing abstraction in OOP.
   - Provide a scenario where an interface might be more suitable than an abstract class.
1. Testing Abstractions
   - Propose a quick strategy on how to unit test abstract methods or classes if they have no direct implementation.

## Deliverables

- Create a folder `H05` in your assignments folder and place all work there.
- **Format**: Markdown, PDF, or text.
- **Length**: Concise answers; emphasize clarity.
- **Assessment**:
  1. Clarity & Understanding (40%)
  2. Practical Application (30%)
  3. Complete Responses (20%)
  4. Organization (10%)
