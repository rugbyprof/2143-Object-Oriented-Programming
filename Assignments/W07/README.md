<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: W07
name: W07
title: Templates
description: Write It Once, Use It for Any Type
category: Assignments
date_due:
  month: '11'
  day: '09'
  year: 2026
  hour: 11
```

</details>

## Worksheet 07 — Templates

Review worksheet built on the [Templates lecture](../../Lectures/Templates/) and its example files `template_01.cpp` through `template_13.cpp`. Each part names the example file it draws from.

- Function templates: why they exist, template parameters vs. arguments, deduction, explicit arguments, and the `'a'` vs `'Z'` and `"apple"` vs `"Banana"` comparison traps
- What a template requires: reading requirements off the code (`Average<T>`), integer-division surprises, and making `Player` fit `Larger` by overloading `operator>` (builds on **Worksheets 03 &amp; 04**)
- Class templates: writing `Box<T>` members outside the class, CTAD, `explicit`, and "methods are only generated when called"
- Non-type parameters and default template arguments (`Inventory<T, Capacity>`, `Counter<T = int>`), plus a compile-time vs. run-time size design question
- A generic `Stack<T>` (back to the **Worksheet 01** stack): tracing it, writing `Contains`, and composition vs. inheritance
- Templates as an interface without inheritance: `Leaderboard<T>` trace, where the `Monster` error appears, writing an adapter class, and a comparison with the abstract-base design from **Worksheet 06**
- Passing behavior in: `Filter` with functions, function objects, and lambdas; `SortedList<T, Compare>` (with a tie-ordering trap); writing a `Between` functor
- Specialization: full and partial `Formatter` specializations, why `Show("name", "Thorin")` skips `Formatter<string>`, and overloading instead of partially specializing function templates
- Templates and inheritance together: pick-the-tool scenarios, CRTP `Comparable<T>` / `Counted<T>` mixins with per-type `static` counters
- C++20 concepts: which types satisfy `Scorable` (including one that satisfies it but makes no sense), and writing a `Printable` concept
- Find-the-error: definitions in a `.cpp` (linker error), missing `template <typename T>` / `Box<T>::`, a run-time value as a template argument, and CTAD with no constructor argument
- A design question connecting templates to the **P01** card game, plus a cheat sheet and a static vs. dynamic polymorphism recap

Every snippet and model answer was compiled (Apple clang 21, `-std=c++20`), and the key's outputs and compiler messages were checked against real runs.

Blank worksheet: [W07.pdf](./W07.pdf)
