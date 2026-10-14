# GameOfWar — Building War with FTXUI

Sixteen short lessons that go from a single terminal box to a playable game of War. Along the way they teach lambdas, classes, separate compilation, encapsulation, composition, and const-correctness. Every lesson follows the same rhythm: **make one small change, compile, run, discuss.**

## Lessons

| #  | Lesson                                         | Main concept                              | Files touched                      |
| -- | ---------------------------------------------- | ----------------------------------------- | ---------------------------------- |
| 01 | [Project setup & first box](01_box.md)         | Elements, layouts, decorators             | `examples/01_box.cpp`              |
| 02 | [Interactive rendering](02_renderer.md)        | Renderers, lambdas, captures              | `examples/02_renderer.cpp`         |
| 03 | [Buttons & callbacks](03_buttons.md)           | Event-driven programming                  | `examples/03_buttons.cpp`          |
| 04 | [Containers](04_containers.md)                 | Component tree vs element tree, focus     | `examples/04_containers.cpp`       |
| 05 | [Counter class](05_counter.md)                 | Encapsulation                             | `examples/05_counter.cpp`          |
| 06 | [Header & implementation files](06_counter.md) | Compiling vs linking                      | `examples/Counter.hpp/.cpp`        |
| 07 | [CounterView](07_counter_view.md)              | Composition, `[this]`, lifetimes          | `examples/07_counter_view.cpp`     |
| 08 | [Card](08_cards.md)                            | Starting the War app; ADTs                | `src/main.cpp`                     |
| 09 | [Deck](09_deck.md)                             | Refactoring into files; `std::vector`     | `Card`, `Deck`                     |
| 10 | [Hand](10_hand.md)                             | Invariants; dynamic layouts               | `Hand`                             |
| 11 | [Rendering cards](11_card_renderer.md)         | Reusable functions; separation of concerns | `main.cpp`                        |
| 12 | [Selecting cards](12_card_select.md)           | Keyboard events with `CatchEvent`         | `main.cpp`                         |
| 13 | [HandView](13_hand_view.md)                    | Refactoring toward a class                | `HandView`                         |
| 14 | [Player](14_player.md)                         | Ownership vs references; const            | `Player`, `HandView`               |
| 15 | [Rules of War](15_war.md)                      | Where rules belong; invariants            | `WarGame`, `Hand`, `Player`        |
| 16 | [Finishing War](16_war_game.md)                | Game state, edge cases, testing           | `WarGame`, `main.cpp`              |

## How the project is organized

- **Lessons 01–07** are standalone warm-ups in `examples/`. Every numbered file there is its own program, so earlier lessons stay runnable.
- **Lessons 08–16** build **one** application, `war`, from `src/main.cpp` plus one `.hpp`/`.cpp` pair per class. Students commit to git at the end of every lesson, so the git log holds each checkpoint.
- Every lesson ends with **Putting it Together**: the complete program as of that lesson, with each file marked new, changed, or unchanged, so a student who falls behind can catch up.

## Final structure

```text
GameOfWar/
├── CMakeLists.txt
├── .gitignore
├── examples/        01_box.cpp … 07_counter_view.cpp, Counter.hpp, Counter.cpp
├── include/         Card.hpp  Deck.hpp  Hand.hpp  HandView.hpp  Player.hpp  WarGame.hpp
└── src/             main.cpp  Card.cpp  Deck.cpp  Hand.cpp  HandView.cpp  Player.cpp  WarGame.cpp
```

```text
main.cpp (FTXUI)
    │
    ├── WarGame ─────────── rules, rounds, game state
    │     ├── Deck
    │     ├── Player ── Hand
    │     └── Player ── Hand
    │
    └── renderCard() / HandView ── drawing only (reads, never modifies)

Card ── interprets IDs 0–51 (suit = id / 13, rank = id % 13)
```

## Building

```bash
cmake -S . -B build                      # first time: downloads FTXUI
cmake --build build --target 03_buttons  # any example: 01_box … 07_counter_view
./build/03_buttons

cmake --build build --target war         # the War application (lessons 08–16)
./build/war
```

## Instructor notes

- The code in `examples/`, `include/`, and `src/` is the **finished state** after Lesson 16. It builds with no warnings on FTXUI v6.1.9.
- The code in every lesson's **Putting it Together** section was extracted and compiled on its own (all 16 build with no warnings).
- `WarGame` was simulated over 20,000 games: every game ended, and the 52-card total held after every round. Lesson 16 Step 16.5 explains the "games that never end" bug that this simulation found in the Lesson 15 version.
- Lesson 16 Challenge 3 (a `war_test` executable) is a good assignment: it reuses the model without the UI, which is the payoff of keeping `WarGame` FTXUI-free.
- **Facade discussion:** Lesson 15 ends with "Is `WarGame` a Facade?". It argues `WarGame` is better described as a game model/controller. A UI-side facade (e.g. a `GameView` that wraps the whole FTXUI screen so `main()` becomes three lines) would be a natural follow-up lesson.
