<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: true
id: W09
name: W09
title: Designing with Objects
description: Relationships, Principles, Patterns
category: Assignments
date_due:
  month: '11'
  day: '30'
  year: 2026
  hour: 11
```

</details>

## Worksheet 09 — Designing with Objects

Review worksheet covering:

- The four relationships (dependency, association, aggregation, composition) plus inheritance: their meaning, lifetimes, C++ shapes, and UML arrows, then classifying eight member declarations (builds on **W08** ownership)
- Is it really "is-a"? The Liskov Substitution Principle through `Rectangle`/`Square` (`Stretch` prints `20 16`), plus judging six hierarchies and "prefer composition over inheritance"
- Coupling and cohesion: the Law of Demeter and "tell, don't ask," applied to the Game of War FTXUI renderer
- SOLID: SRP, OCP, LSP, and DIP, tied back to **P01** and **W06**; dependency injection with `Dice` / `FixedDice` to make `Combat` testable (the same idea as P01's stacked `Deck`)
- Strategy: a `Dealer` with swappable `HitStrategy` objects, and why it beats a subclass for each dealer style
- Factory: building characters from save-file data with a registry `map`, the `nullptr` trap, and Open/Closed
- Observer: a `ScoreBoard` with lambda listeners, adding an achievement without editing the subject, and the dangling-capture lifetime bug (**W08**)
- Facade: a `WarTable` that gives the War renderer one plain `TableView`. Students move the status logic out of the lambda and rewrite the renderer with a `SeatBox` helper.
- "Which pattern fits?" scenarios (Strategy, Factory, Observer, Facade, Adapter from **W07**, RAII from **W08**)
- Design review: find the problems in a working but badly designed `BlackjackGame`, then sketch a better class design
- A cheat sheet of design principles and patterns

Every snippet and model answer was compiled (Apple clang 21, `-std=c++20`). The facade and the rewritten renderer were also compiled and run against the FTXUI from the P01 build.

Blank worksheet: [W09.pdf](./W09.pdf) &middot; Key: [W09-Key.pdf](./W09-Key.pdf)
