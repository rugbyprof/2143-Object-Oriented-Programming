## Homework - Understanding Encapsulation

#### Due: 03-25-2025 (Tuesday)

Encapsulation is one of the key pillars of object-oriented programming (OOP), emphasizing the **separation of an object’s internal data** (state) from how that data is accessed or modified (behavior). This assignment focuses on **how** and **why** to protect data within classes, and how encapsulation helps maintain a clear contract between the class and the outside world.

---

## Objectives

1. **Identify** the importance of encapsulation in OOP.
2. **Differentiate** between public, private, and protected members.
3. **Demonstrate** how encapsulation ensures data hiding and promotes maintainable code.

---

## Part A: Conceptual Questions

1. **Definition**

   - In your own words, define **encapsulation**. Include an example of how it can prevent unintended changes to data.

2. **Visibility Modifiers**

   - Compare **public**, **private**, and **protected** access. For each, list **one benefit** and **one potential drawback** (in terms of code flexibility, safety, or maintainability).
   - Name a scenario in which you might **intentionally** use protected members instead of private members.

3. **Impact on Maintenance**

   - Explain why encapsulation can **reduce debugging complexity** when maintaining a large codebase.
   - Provide a brief example (no code needed, just a scenario) of how code could break if internal data is made public.

4. **Real-World Analogy**
   - Think of a real-life object or system. How would you describe its “public interface” vs. its “private implementation”? Why is it helpful to keep the private side hidden?

---

## Part B: Small-Class Design (Minimal Coding)

> **Note:** Keep coding minimal. Focus on how you would structure class members rather than implementing all functionality.

1. **Class Skeleton**

   - Outline a small class C++ that represents a **BankAccount**.
   - Include:
     - Two **private** data members (e.g., `balance`, `accountNumber`).
     - One or two **public** methods that allow interaction with the balance (e.g., `deposit` or `withdraw`).

2. **Encapsulation Justification**

   - For each private data member, explain in 1–2 sentences why it **should** be kept private.
   - For each public method, explain how it **enforces constraints** or **validations** before modifying any private data.

3. **Documentation**
   - Briefly show how you would **document** the class or methods so other developers understand they must not directly manipulate the `balance`.

## Part C: Reflection & Short-Answer

1. Pros and Cons
   - List two benefits of hiding internal data behind methods, and one potential limitation or overhead introduced by this design approach.
2. Encapsulation vs. Other Concepts
   - How does encapsulation differ from abstraction?
   - Why might we consider both “encapsulation” and “abstraction” to be forms of “information hiding”?
3. Testing Encapsulated Classes
   - If the data is private, how can we still unit test the class thoroughly? Propose a short strategy that ensures valid testing without exposing private data.

## Part D: Optional Research

This part is optional and can be completed for extra credit or deeper understanding.

1. Encapsulation in Various Languages
   - Compare how two programming languages (e.g., Java vs. C++) handle visibility modifiers. Do they differ in how they define public, private, or protected?
2. Encapsulation in Large-Scale Systems
   - Find a short online reference or article discussing how large companies ensure critical data is protected within their codebase. Summarize the key points in a paragraph.

### Submission Format

- Part A–C can be submitted as a text or PDF document.
- Minimal coding is sufficient; focus on class outlines and justifications for your design choices.
- Optional Part D can be included in your main submission as a separate section.

### Deliverables

- Create a folder called `H02` in your assignments folder and place all work there.
- Look at the following to determine your approach:
  - Clarity of Explanation (40%): How well you articulate the concept of encapsulation and your justification for using it.
  - Correct Usage of Visibility (30%): Appropriate use of private/public, plus correct reasons for each.
  - Completeness (20%): Answering all required questions and providing examples.
  - Conciseness and Readability (10%): Clear, succinct answers. Minimal (but illustrative) code.
