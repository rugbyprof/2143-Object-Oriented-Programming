<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: W06
name: W06
title: Polymorphism
description: One Interface, Many Behaviors
category: Assignments
date_due:
  month: '10'
  day: '05'
  year: 2026
  hour: 11
```

</details>

## Worksheet 06 — Polymorphism

Review worksheet covering:

- The static-vs-dynamic binding problem — picks up the `Vehicle*`-points-at-a-`Car` cliffhanger from **Worksheet 05** Part 7, now with both a pointer and a reference, then the one-word `virtual` fix
- Two kinds of polymorphism: compile-time (overloading from **Worksheets 02 &amp; 04**, templates) vs. run-time (`virtual` + base pointers/references)
- Override signature rules and the `override` keyword — missing `const`, wrong parameter type, non-virtual base, misspelled name — plus the silent "hides instead of overrides" bug
- Pointers, references, and object slicing (by-value parameter, `vector<Character>`)
- One loop over a mixed `vector<unique_ptr<Character>>` (Warrior / Wizard / Rogue from the run-time polymorphism lecture), inherited-vs-overridden fallbacks, the if/else-on-a-type-string alternative, and a "write the `Bard`" exercise
- Virtual destructors — builds on the W05 destruction-order material
- Abstract classes and pure virtual functions (`Shape` / `Circle` / `Blob`), with "write `Rectangle`" and "write `totalArea()`" exercises
- Find-the-error traps: `virtual` only in the derived class, a missing `const` leaving a class abstract, a raw-pointer leak, and calling a derived-only method through a base pointer
- Under the hood: vtables and vptrs, a fill-in-the-vtable table, and a cheat sheet

Every code snippet was compiled (clang++, C++17) and the key's outputs and compile errors were checked against real runs.

Blank worksheet: [W06.html](./W06.html) &middot; Key: [W06-Key.html](./W06-Key.html)

This is a draft in `.profzone/Handouts/` — not yet published to the public `Assignments/` tree. Review, then publish manually per the usual workflow.
