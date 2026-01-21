```yaml
title: OOP Wiki Assignment (Spiced Up + Better Requirements)
course: OOP
assignment_type: documentation_project
platform: GitHub Wiki
deliverable: polished_wiki_with_definitions_examples_and_visuals
due_dates:
  checkpoint: 2025-03-17
  final: 2025-05-09
grading_emphasis:
  - completeness
  - clarity_and_accuracy
  - organization_and_navigation
  - examples_and_code_quality
  - visuals_and_diagrams
  - professional_presentation
```

## OOP Wiki Assignment: Build Your Personal OOP Knowledge Base

> **Note:** This assignment has **two due dates**. The first is a **progress checkpoint**, not the final product.  
> **Checkpoint (Midterm):** **2025-03-17**  
> **Final (Last Week):** **2025-05-09**

### Why this exists

In industry, you’ll spend a shocking amount of time reading documentation that ranges from “pretty good” to “written by a raccoon on espresso.” This assignment teaches you how to produce documentation that is **useful, navigable, and readable**—the kind you’ll wish existed when you’re debugging at 2:00am.

You will create a **GitHub Wiki** for your OOP repository that documents OOP concepts we cover in class **with definitions, examples, and visuals**. You’ll start with the concepts we cover, but you also have access to a larger master list to keep expanding your knowledge over time.

This wiki should be something you can point to later and say:  
“Yeah… I actually understand OOP. Here’s the proof.”

---

## Required Tutorials (Do These Early)

You are expected to learn how GitHub-flavored Markdown and GitHub Wikis work:

- [Getting Started With Markdown](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
- [Mastering Markdown](https://guides.github.com/features/mastering-markdown/)
- [Documenting Projects With Wikis](https://docs.github.com/en/communities/documenting-your-project-with-wikis/about-wikis)

---

## Deliverables

### 1) Wiki Setup Requirements (Non-negotiable)

Your wiki must include:

✅ **Home Page**

- Brief description of what the wiki is and how to use it.
- A “Start Here” section for navigation.

✅ **Sidebar Navigation (`_Sidebar.md`)**

- Must contain a structured index (not a wall of links).
- Must group topics into logical categories (Core Concepts, Relationships, Patterns, etc.).

✅ **Footer (`_Footer.md`)**

- Your name, course, semester, and repo link
- A short citation note: “Examples are original unless otherwise credited.”

✅ **Glossary / Index Page**

- A single page listing all terms **alphabetically**
- Each term must link to its page/section

✅ **Changelog Page**

- A running list of updates (simple bullet list is fine)
- Helps prove progress between checkpoint and final

---

### 2) Page Template Requirements (Consistency = professionalism)

Every concept page must follow a consistent structure like this:

#### Required Sections Per Concept

1. **Definition**
   - Clear and correct (2–5 sentences)
2. **Why it matters**
   - What problem it solves / why OOP uses it
3. **Code Example**
   - At least one short example (C++ or Python, whichever we’re using in class)
   - Must be readable and commented _lightly_ (no novel-length comments)
4. **Common Mistakes**
   - At least 2 common misconceptions or beginner errors
5. **Related Concepts**
   - At least 3 internal wiki links (ex: Encapsulation ↔ Access Modifiers ↔ Information Hiding)
6. **Further Reading**
   - 1–3 external links (official docs, reputable tutorials)

> If a page is missing these sections, it’s incomplete. This is documentation, not vibes.

---

### 3) Visual Requirements (Make it teach, not just talk)

Your wiki must include **at least 10 visuals total**, distributed across the wiki.

Pick from:

- **UML class diagrams** (yes, even if you hate them)
- **sequence diagrams** showing message passing / method calls
- **inheritance trees**
- **memory diagrams** (stack vs heap, pointers/references)
- **screenshots** of your code running with labeled output
- **tables** comparing concepts (composition vs inheritance, overloading vs overriding, etc.)

#### Visual ideas that work well in OOP:

- **Encapsulation:** diagram showing private fields + public methods
- **Inheritance:** base/derived diagram showing what’s inherited
- **Polymorphism:** one interface → multiple implementations diagram
- **V-table / dispatch:** simple “function pointer table” diagram for C++
- **Composition vs Inheritance:** “has-a vs is-a” visual
- **Exception handling:** control flow diagram with try/catch

---

## Screenshot Instructions (Required for at least 5 pages)

Screenshots should be **useful evidence**, not random screen grabs.

### Minimum Screenshot Standards

- Must show **your name OR repo OR terminal prompt** in the image (proof it’s yours)
- Crop out irrelevant clutter (don’t screenshot your entire desktop like it’s 2009)
- Must include either:
  - code + output, OR
  - diagram + explanation, OR
  - test results

### Great screenshot options:

- Terminal output showing a program behavior (constructor/destructor order!)
- A polymorphism example where the base pointer calls derived methods
- A unit test run (even a tiny one)
- A debug trace or printout showing execution order

### How to add images to GitHub Wiki

- Create an `images/` folder in the Wiki repository
- Upload images there
- Reference them like:

```md
![Short description](images/polymorphism_dispatch.png)
```

---

## Midterm Checkpoint Requirements (2025-03-17)

By the checkpoint, your wiki must have:

- ✅ Home page + sidebar + footer
- ✅ At least **8 completed terms/pages**
- ✅ At least **3 visuals**
- ✅ At least **3 screenshots** (properly labeled)
- ✅ A changelog showing progress

This is graded like: _“Are you building the thing?”_ not _“Is it perfect?”_

---

## Final Submission Requirements (2025-05-09)

By the final due date, your wiki must have:

- ✅ At least **25 completed terms/pages**
- ✅ At least **10 visuals** total
- ✅ At least **5 screenshot-based pages**
- ✅ Internal linking that forms a web (not isolated pages)
- ✅ A clean, readable sidebar (organized categories)
- ✅ A glossary/index page with all terms linked
- ✅ A changelog showing meaningful progress over time

---

## Style Guide (Make it not ugly)

A wiki should feel like a _reference manual_, not a diary.

### Formatting Requirements

- Use **headers consistently** (`##`, `###`)
- Use **short paragraphs**
- Use **lists** for steps and mistakes
- Use **code fences** with language labels:

```cpp
// C++ example
```

```python
# Python example
```

### “Looks good” checklist

- Every page starts with a one-sentence summary
- No giant unbroken text walls
- Related links at the bottom
- Pages share a common template

---

## Extra Credit (Optional, but cool)

Pick one:

- Add a “**Mini Labs**” section: tiny runnable examples for 5 concepts
- Add a “**Design Patterns Gallery**” page with a diagram + example for 3 patterns
- Convert one messy concept into a killer visual explanation (v-table, slicing, LSP)

---

## Object-Oriented Programming Terms Organized by Category

### Core OOP Concepts

- [ ] Classes and Objects
- [ ] Instance Variables
- [ ] Member Variables
- [ ] Class Variables
- [ ] Methods
- [ ] Static Methods and Variables
- [ ] Constructors and Destructors
- [ ] Encapsulation
- [ ] Inheritance
- [ ] Polymorphism
- [ ] Method Overloading
- [ ] Operator Overloading
- [ ] Overloading
- [ ] Multiple Inheritance
- [ ] Abstract Classes and Methods
- [ ] Interfaces
- [ ] Virtual Functions (V-Table and Dynamic Dispatch)

### Object Relationships and Design Principles

- [ ] Object Relationships (Association, Aggregation, Composition)
- [ ] Composition vs Aggregation
- [ ] Delegation
- [ ] Cohesion and Coupling
- [ ] Encapsulation vs Information Hiding
- [ ] Separation of Concerns (SoC)
- [ ] Dependency Injection
- [ ] Message Passing
- [ ] Mixin Classes
- [ ] Type Hinting and Type Safety in OOP

### Access Control and Scope

- [ ] Access Modifiers (Public, Private, Protected)
- [ ] Public / Private / Protected
- [ ] Final Classes and Methods
- [ ] Friends (C++ Specific)
- [ ] Namespace and Scope in OOP

### OOP Design Principles and Patterns

- [ ] Object-Oriented Design Principles
- [ ] SOLID Principles
- [ ] Single Responsibility Principle
- [ ] Open-Closed Principle
- [ ] Liskov Substitution Principle
- [ ] Interface Segregation Principle
- [ ] Dependency Inversion Principle
- [ ] Design Patterns (Creational, Structural, Behavioral)
- [ ] Creational Patterns (e.g., Singleton, Factory Method, Prototype)
- [ ] Structural Patterns (e.g., Adapter, Composite)
- [ ] Behavioral Patterns (e.g., Strategy, State, Observer, Command, Chain of Responsibility)
- [ ] Service-Oriented Architecture (SOA)
- [ ] Metaprogramming and Reflection
- [ ] Aspect-Oriented Programming (AOP)

### Exception Handling and Memory Management

- [ ] Exception Handling
- [ ] Memory Management (Garbage Collection, Pointers)
- [ ] Automatic and Manual Memory Allocation
- [ ] Smart Pointers (C++ Specific)

### File Handling, Collections, and Iterators

- [ ] File I/O in OOP
- [ ] Collections and Iterators
- [ ] Generics and Templates

### Testing, Debugging, and Multithreading

- [ ] Testing in OOP (Unit Testing, Test-Driven Development)
- [ ] Multithreading in OOP (Concurrency, Parallelism, Thread Safety)

### UML and Software Modeling

- [ ] UML Diagrams and Modeling
- [ ] Use Case Diagrams
- [ ] Class Diagrams
- [ ] Sequence Diagrams
- [ ] State Diagrams

### Other OOP Concepts

- [ ] Duck Typing
- [ ] Prototype Pattern
- [ ] Singleton vs Static Class
- [ ] Factory Method Pattern

---

## Grading Rubric

- **Organization & Navigation (20%)**  
  Sidebar, structure, index, cross-links
- **Content Quality (30%)**  
  Definitions accurate, explanations clear
- **Examples (20%)**  
  Real code, readable, correct
- **Visuals & Screenshots (20%)**  
  Useful, relevant, not junk
- **Professionalism (10%)**  
  Consistency, formatting, citations

---

## Submission

We will discuss submitting assignments later.
