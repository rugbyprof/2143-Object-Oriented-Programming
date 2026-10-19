<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: W05
name: W05
title: Inheritance
description: Building New Classes from Old Ones
category: Assignments
date_due:
  month: '09'
  day: '28'
  year: 2026
  hour: 11
```

</details>

## Worksheet 05 — Inheritance

Review worksheet covering:

- Base/derived classes, the "is-a" relationship, `class Derived : public Base` syntax
- `protected` access — reprises the `private`/`public` access-control material from **Worksheet 01**, extended with the third level
- Constructor chaining via the initializer list — directly builds on the initializer-list work in **Worksheet 04**; base-before-derived construction order (and the reverse for destructors)
- Overriding vs. overloading — a deliberate contrast with the overloading covered in **Worksheets 02 &amp; 04**
- Hierarchical inheritance (one base, several derived classes) and a "write the class" exercise
- Find-the-error traps: missing `public` on the inheritance list (defaults to private, mirroring the class/struct default-access lesson from W01), a derived constructor that can't chain to a base with no default constructor, and `protected` not being the same as `public`
- A short, ungraded preview of `virtual` functions/polymorphism as the logical next topic

Blank worksheet: [W05.pdf](./W05.pdf) &middot; Key: [W05-Key.pdf](./W05-Key.pdf)
