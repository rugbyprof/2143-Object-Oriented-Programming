# Homework - Understanding Composition and Aggregation in OOP

#### Due: 03-25-2025 (Tuesday)

**Composition** and **aggregation** are two closely related concepts that describe "has-a" relationships between classes. This homework focuses on understanding how objects can be combined to form more complex systems, while still maintaining clear boundaries and responsibilities.

---

## Objectives

1. **Define** and **differentiate** composition and aggregation in the context of OOP.
2. **Explain** how these relationships differ from inheritance.
3. **Demonstrate** a basic design scenario where one class “owns” or “contains” objects of another class.

---

## Part A: Conceptual Questions

1. **Composition vs. Aggregation**

   - In your own words, define both **composition** and **aggregation**.
   - Provide a concise example (with or without code) illustrating each concept.
   - Which relationship implies a stronger form of ownership?

2. **When to Use**

   - Describe a scenario (in any domain, e.g. gaming, banking, or UI) where **composition** is more appropriate than **inheritance**.
   - Provide another scenario where **aggregation** is sufficient. Why is it only partial ownership or a looser coupling?

3. **Differences from Inheritance**

   - Explain how `composition/aggregation` differ from the **"is-a"** relationship implied by `inheritance`.
   - Why might an OOP design favor composition over inheritance in certain cases?

4. **Real-World Analogy**
   - Think of a real-life system that uses both composition and aggregation. (e.g., A car with an engine (composition) and a driver (aggregation)?).
   - Why do these distinctions matter in code?

---

## Part B: Minimal Class Design or UML

> **Choose one** of the following approaches and keep it short.

### Option 1: Minimal Class Example

1. **Create Two Classes**

   - **Person** and **Address**, for instance.
   - Decide if **Address** is truly contained by **Person** (composition) or if **Person** only holds a reference that could exist independently (aggregation).

2. **Structure & Methods**

   - Show minimal attributes (e.g., `name`, `street`, `city`).
   - Provide a constructor or an assignment method.
   - Emphasize how the **lifecycle** of one object depends (or does not depend) on the other.

3. **Short Snippet**

```cpp
class Person {
    private Address address;  // Decide if it's a strong or weak "has-a"
    ...
}

class Address {
    ...
}
```

### Option 2: UML Diagram

1. Diagram
   - Draw two classes representing composition (a solid diamond arrow) or aggregation (an open diamond arrow).
   - Label attributes and show how the classes relate (e.g., “1..1” or “1..\*”).
2. Brief Explanation
   - In 2–3 sentences, explain why the chosen relationship is composition (strong ownership) or aggregation (looser coupling).

## Part C: Reflection & Short Discussion

1. Ownership & Lifecycle
   - In a composition relationship, what happens to the “child” object if the “parent” is destroyed or deallocated?
   - In an aggregation relationship, how might the child object continue to exist independently?
2. Advantages & Pitfalls
   - Give one advantage of using composition for controlling object lifecycles.
   - Provide one potential pitfall if you wrongly use composition where looser coupling (aggregation) is needed.
3. Contrast with Inheritance
   - Summarize how “has-a” relationships differ from “is-a” relationships in practical code design.
   - Why might we avoid inheritance in situations that can be solved by composition or aggregation?

## Deliverables

- Create a folder `H06` in your assignments folder and place all work there.
- **Format**:
  - Markdown, PDF
- **Length**:
  - Concise yet complete, focusing on conceptual clarity.
- **Assessment**:
  - Clarity & Correctness (40%)
  - Completeness (30%)
  - Realistic Examples (20%)
  - Brevity & Organization (10%)

---
