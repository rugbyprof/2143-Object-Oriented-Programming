---
name: 2143 OOP Course Context
description: Current state of assignments and resources for 2143 Object-Oriented Programming
type: project
---

Course is 2143 Object-Oriented Programming, taught in C++. Assignments live in Assignments/, resources in Resources/.

Current assignment arc:
- 07-P02: Command-line args parser (Args class, static factory method Args::parse(), imgtool theme)
- 10-P03: Image filter pipeline (Strategy pattern, Filter base class, Pipeline class, PPM image format)

Key design lessons being taught:
- Static factory methods vs. constructors doing all the work
- Strategy pattern / polymorphism via Filter hierarchy
- Modern C++ storage: map, variant, optional, any, nlohmann JSON

Resources created this session:
- Resources/Static_Keyword_Guide.md — static keyword in all four contexts
- Resources/Dynamic_Data_Storage_Guide.md — map → variant → any → JSON progression, using aliases, feature version table
- Assignments/10-P03/Filter.h, Grayscale.h, Grayscale.cpp — stubs for P03

**Why:** Terry wants students to learn modern C++17/20 idioms, not 1998-era patterns. The imgtool theme runs across both assignments so students see the pieces connect.
**How to apply:** When suggesting code or design patterns, default to C++17 minimum. Tie examples back to the imgtool/Args/Filter context where possible.
