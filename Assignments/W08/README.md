<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: W08
name: W08
title: Object Lifetime and Ownership
description: Who Cleans Up?
category: Assignments
date_due:
  month: '11'
  day: '16'
  year: 2026
  hour: 11
```

</details>

## Worksheet 08 — Object Lifetime and Ownership

Review worksheet covering:

- When objects die: automatic, by-value parameter, and heap lifetimes, traced with a printing `Tracer` class, including a `new` that is never deleted (builds on **W05** construction order)
- The Big Three: finishes the copy-semantics preview from **Worksheets 03 &amp; 04**. Which special member each line calls, and exactly what goes wrong (double free, leak) when only a destructor is written
- Writing copy assignment: three buggy versions (shallow copy, self-assignment, `void` return) and a correct one to write
- Move semantics: lvalues vs. rvalues, `std::move` is only a cast, writing a move constructor, `noexcept`, copy elision, and `push_back` vs. `emplace_back`
- The Rule of Five and the Rule of Zero: how a user-declared destructor silently turns moves into copies, rewriting the **W01** `IntStack` with `vector`, and `= delete` for non-copyable types
- RAII: destructors run during exceptions (stack unwinding), fixing a leak with one line, and writing a `LogScope` class
- Smart pointers: `unique_ptr`, `shared_ptr` use counts, `weak_ptr`, and a `Team`/`Player` `shared_ptr` cycle that leaks
- Ownership as a design decision: what a signature promises (`const T&`, `unique_ptr<T>`, `shared_ptr<T>`, `T*`), choosing member types, and value cards vs. `unique_ptr` characters (**W06** slicing, **P01**)
- Find-the-error: returning a reference to a local, a reference into a `vector` that reallocates, two `unique_ptr`s owning one raw pointer, and use after move
- A cheat sheet and a "which member type?" decision tree

Every snippet and model answer was compiled (Apple clang 21, `-std=c++20`). Outputs in the key come from real runs, and the crash claims were confirmed with AddressSanitizer (double free, heap-use-after-free). Two outputs depend on the implementation and are labeled that way in the key: the contents of a moved-from `string`, and the order in which `vector` destroys its elements (not asked).

Blank worksheet: [W08.pdf](./W08.pdf) &middot; Key: [W08-Key.pdf](./W08-Key.pdf)
