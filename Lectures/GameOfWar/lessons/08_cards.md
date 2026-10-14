# GameOfWar 08 — Starting the War App: The Card Class

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 08 - Card ADT
previous: examples/07_counter_view.cpp
new_file: src/main.cpp
concepts:
  - Abstract Data Types
  - Constructors
  - Encapsulation
  - Integer division and modulo
  - Separating data from presentation
```

We've built a counter, moved its logic into a class, and created an FTXUI view using composition.

Now we start the real project: **a game of War.**

From here on, we don't make a new file per lesson. There is **one program**, built from `src/main.cpp`. Each lesson edits it and adds classes as we need them. Your git commits are your checkpoints.

**We're not building a deck today. We're building one card.** A card is an integer from 0 through 51.

## Step 8.1 — Set up the War application

Create two folders:

```bash
mkdir include src
```

| Folder     | Holds                                         |
| ---------- | --------------------------------------------- |
| `include/` | Class declarations (`.hpp`)                   |
| `src/`     | `main.cpp` and class implementations (`.cpp`) |

At the bottom of `CMakeLists.txt`, add a second kind of target:

```cmake
# --------------------------------------------------
# Lessons 08-16: the War application
# --------------------------------------------------
add_executable(war
    src/main.cpp
)

target_include_directories(war PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(war PRIVATE
    ftxui::component
)
```

Unlike the `examples/` loop, this target lists its source files **explicitly**. As we add classes, we'll add their `.cpp` files to this list, just like `target_sources()` in Lesson 06.

`target_include_directories` means `#include "Card.hpp"` will look in `include/`.

Now create `src/main.cpp`:

```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        return vbox({
            text("GameOfWar 08") | bold | center,
            separator(),
            text("War is coming...") | center,
        }) | border;
    });

    screen.Loop(renderer);
}
```

Compile and run:

```bash
cmake -S . -B build
cmake --build build --target war
./build/war
```

Press **Ctrl+C** to exit.

**Checkpoint:** We have a working (if boring) War application. From now on, every build command is the same:

```bash
cmake --build build --target war
./build/war
```

---

## Step 8.2 — Introduce a Card class

For now, define `Card` directly in `main.cpp`, above `main()`. We'll move it into its own files in Lesson 09.

```cpp
class Card {
private:
    int id;

public:
    Card(int id = 0) : id(id) {
    }

    int getId() const {
        return id;
    }
};
```

That's our entire card class. No suit enum. No rank enum. No hierarchy. A card is identified by an integer.

Add this as the first line inside `main()`:

```cpp
Card card(17);
```

Compile. Nothing changes visually.

### Discussion

Why wrap the integer in a class instead of simply writing:

```cpp
int card = 17;
```

Because the class gives us a place to put **operations** (what's the suit? what's the name?) and to **enforce rules** (IDs must be 0–51).

---

## Step 8.3 — Calculate suit and rank

52 cards = 4 suits × 13 ranks. With IDs 0–51:

```text
id / 13  →  0, 1, 2, 3       (4 values: the suit)
id % 13  →  0 through 12     (13 values: the rank)
```

So **division gives the suit, and modulo gives the rank**:

```text
         rank:  0   1   2  ...  12
suit 0 (♣):     0   1   2  ...  12
suit 1 (♦):    13  14  15  ...  25
suit 2 (♥):    26  27  28  ...  38
suit 3 (♠):    39  40  41  ...  51
```

Add two methods to `Card`:

```cpp
int getSuit() const {
    return id / 13;
}

int getRank() const {
    return id % 13;
}
```

Compile.

### Experiment

For card 17:

```text
17 / 13 = 1   → suit 1
17 % 13 = 4   → rank index 4
```

**Work these out by hand:** cards 0, 12, 13, 25, 26, and 51. Which ones are Aces? Which are Kings?

---

## Step 8.4 — Give the card a name

Add these includes at the top of `main.cpp`:

```cpp
#include <string>
#include <vector>
```

Add three methods to `Card`:

```cpp
std::string rankName() const {
    static const std::vector<std::string> ranks = {
        "Ace", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "Jack", "Queen", "King"
    };

    return ranks[getRank()];
}

std::string suitName() const {
    static const std::vector<std::string> suits = {
        "Clubs", "Diamonds", "Hearts", "Spades"
    };

    return suits[getSuit()];
}

std::string toString() const {
    return rankName() + " of " + suitName();
}
```

The rank and suit numbers are just **indexes into lookup tables**. Card 17 has rank index 4 → `"5"` and suit 1 → `"Diamonds"`, so `toString()` returns `"5 of Diamonds"`.

**Question:** Why `static const`? What would happen without `static`?

Without `static`, the vector would be rebuilt every time the method is called. With `static`, it's built once and reused.

The card now knows how to describe itself. **But it still knows nothing about FTXUI.** That's important.

Compile.

---

## Step 8.5 — Display the card

Update the renderer:

```cpp
auto renderer = Renderer([&] {
    return vbox({
        text("GameOfWar 08") | bold | center,

        separator(),

        text("Card ID: " + std::to_string(card.getId())) | center,

        text(card.toString()) | center,

    }) | border;
});
```

Compile and run:

```text
┌───────────────────────────┐
│       GameOfWar 08        │
├───────────────────────────┤
│        Card ID: 17        │
│       5 of Diamonds       │
└───────────────────────────┘
```

Change `Card card(17);` to a few other IDs and check them against your answers from Step 8.3.

---

## Step 8.6 — Change cards with a button

Add a setter to `Card` that **refuses invalid IDs**:

```cpp
void setId(int newId) {
    if (newId >= 0 && newId < 52) {
        id = newId;
    }
}
```

The interface doesn't need to know the rule. The class enforces it.

Now add a button inside `main()`, right after creating the screen:

```cpp
auto next = Button("Next Card", [&] {
    card.setId((card.getId() + 1) % 52);
});
```

Give the renderer the button as its child (remember Lesson 03):

```cpp
auto renderer = Renderer(next, [&] {
```

And add the button to the end of the `vbox`:

```cpp
separator(),

next->Render() | center,
```

Compile and run. Clicking **Next Card** cycles through all 52 cards. After card 51 comes card 0.

### Discussion

| Responsibility               | Location        |
| ---------------------------- | --------------- |
| Store the card ID            | `Card`          |
| Calculate suit and rank      | `Card`          |
| Validate card IDs            | `Card`          |
| Handle button clicks         | FTXUI           |
| Display card information     | Renderer        |
| Decide which card comes next | Button callback |

That last row is interesting. Should the *button* calculate the next ID, or should `Card` have a `next()` method? There's no universal answer, but it's a good design question.

---

## Step 8.7 — Student challenge

Add two more buttons:

```text
[ Previous ] [ Next ]

      [ Random ]
```

Requirements:

1. Previous moves backward; Next moves forward.
2. Both wrap around at the boundaries.
3. Random selects an ID between 0 and 51.
4. The `Card` class must enforce valid IDs.
5. The renderer must not calculate ranks or suits.

For Previous, consider:

```cpp
(card.getId() - 1 + 52) % 52
```

**Why add 52 before applying modulo?** Because in C++, `-1 % 52` is `-1`, not `51`. The remainder takes the sign of the left operand.

For Random, look up `<random>` (`std::mt19937` and `std::uniform_int_distribution`). We'll use the same tools to shuffle a deck in Lesson 09.

---

## Putting it Together

Here is every file in the War app at the end of Lesson 08. Files marked **new** or **changed** were touched in this lesson; the rest are the same as last lesson.

### `src/main.cpp` (new)

<!-- file: src/main.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>
#include <vector>

using namespace ftxui;

class Card {
private:
    int id;

public:
    Card(int id = 0) : id(id) {
    }

    int getId() const {
        return id;
    }

    int getSuit() const {
        return id / 13;
    }

    int getRank() const {
        return id % 13;
    }

    std::string rankName() const {
        static const std::vector<std::string> ranks = {
            "Ace", "2", "3", "4", "5", "6", "7",
            "8", "9", "10", "Jack", "Queen", "King"
        };

        return ranks[getRank()];
    }

    std::string suitName() const {
        static const std::vector<std::string> suits = {
            "Clubs", "Diamonds", "Hearts", "Spades"
        };

        return suits[getSuit()];
    }

    std::string toString() const {
        return rankName() + " of " + suitName();
    }

    void setId(int newId) {
        if (newId >= 0 && newId < 52) {
            id = newId;
        }
    }
};

int main() {

    Card card(17);

    auto screen = ScreenInteractive::TerminalOutput();

    auto next = Button("Next Card", [&] {
        card.setId((card.getId() + 1) % 52);
    });

    auto renderer = Renderer(next, [&] {
        return vbox({
            text("GameOfWar 08") | bold | center,

            separator(),

            text("Card ID: " + std::to_string(card.getId())) | center,

            text(card.toString()) | center,

            separator(),

            next->Render() | center,

        }) | border;
    });

    screen.Loop(renderer);
}
```

---

## Commit your work

```bash
git add .
git commit -m "Lesson 08: Card class"
```

### Next: GameOfWar 09 — A Deck of Cards

We'll move `Card` into `include/Card.hpp` and `src/Card.cpp`, using exactly what we learned in Lesson 06. Then we'll add a `Deck` class that holds a `std::vector<int>` of card IDs and can **draw** and **shuffle**.
