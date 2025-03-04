## Homework - Basic Design Principles in Software Development

#### Due: 03-25-2025 (Tuesday)

This homework focuses on fundamental design principles that guide the creation of clear, maintainable, and robust software. Specifically, we'll cover **DRY** (Don’t Repeat Yourself), **KISS** (Keep It Simple, Stupid), and a high-level introduction to the **SOLID** principles.

---

## Objectives

1. **Define** and **identify** DRY and KISS in code design.
2. **Explain** the high-level concepts behind the **SOLID** principles.
3. **Apply** these principles in simple scenarios or design sketches.

---

## Part A: Conceptual Questions

1. **DRY (Don’t Repeat Yourself)**

   - In your own words, define **DRY** and provide a short example of repeated code that violates DRY.
   - Briefly explain how you would refactor that code to adhere to DRY.

2. **KISS (Keep It Simple, Stupid)**

   - Describe **KISS** and why it is crucial for maintainable code.
   - Name one potential drawback of oversimplifying code—why might too little complexity sometimes be problematic?

3. **Introduction to SOLID** (High-Level)  
   The SOLID principles are:

   1. **Single Responsibility Principle (SRP)**
   2. **Open-Closed Principle (OCP)**
   3. **Liskov Substitution Principle (LSP)**
   4. **Interface Segregation Principle (ISP)**
   5. **Dependency Inversion Principle (DIP)**

   - Pick **two** of these (your choice) and provide a one-sentence explanation of each.
   - Why do the SOLID principles matter in large codebases?

---

## Part B: Minimal Examples or Scenarios

> **Note:** Keep coding minimal. You can present scenarios or UML-like sketches.

1. **DRY Violation & Fix**

   - **Scenario**: You have two functions in a class that perform very similar tasks (e.g., printing user details with slight variations).
   - **Task**: Show how you would rewrite or refactor them into a single function or method, removing duplicated logic.

2. **KISS Principle Example**

   - **Scenario**: A method that calculates the discount for a product uses overly complex conditional checks.
   - **Task**: Sketch or pseudo-code a simpler approach that follows KISS, ensuring the method is easy to read and modify.

3. **SOLID Application**
   - **Scenario**: Suppose you have a `Shape` interface with `draw()` and `computeArea()` methods. `Circle` and `Rectangle` implement `draw()` differently, but the same method to compute area.
   - **Task**: Show (in pseudo-code or UML) how **one** relevant SOLID principle (e.g., Single Responsibility or Interface Segregation) applies here.
   - **Optional**: If you want to illustrate a second principle, you can do so, but keep it minimal.

---

## Part C: Reflection & Short Discussion

1. **Trade-Offs**

   - Sometimes code repetition can look like a DRY violation but might be simpler to read.
   - Provide a short scenario where repeating code might be more readable than forcing a “clever” DRY solution.

2. **Combining Principles**

   - How can adhering to both DRY and KISS simultaneously guide your design decisions? Give a brief example.

3. **SOLID in Practice**
   - In a small project or code snippet, is it always necessary to strictly follow every SOLID principle?
   - Why might an early-stage or small codebase not adhere strictly to these guidelines?

## Deliverables

- Create a folder `H07` in your assignments folder and place all work there.
- **Format**:
  - Markdown, PDF
- **Length**:
  - Concise yet complete, focusing on conceptual clarity.
- **Assessment**:
  - Clarity & Correctness (40%)
  - Completeness (30%)
  - Realistic Examples (20%)
  - Brevity & Organization (10%)
