# TinyChunks 09 — Building a Deck of Cards

```yaml
course: 2143 - Object-Oriented Programming
project: tinychunks
lesson: 09 - Deck of Cards
previous: Lesson 08 (src/main.cpp)
new_files:
  - include/Card.hpp
  - src/Card.cpp
  - include/Deck.hpp
  - src/Deck.cpp
concepts:
  - Moving a class into its own files
  - Refactoring
  - std::vector
  - Returning a sentinel value
  - std::shuffle and <random>
```

We have a working `Card` class inside `main.cpp`. Before building a deck, we'll give `Card` its own files, exactly like we did with `Counter` in Lesson 06.

Today we will:

1. Move `Card` into `include/Card.hpp` and `src/Card.cpp`.
2. Create a `Deck` class containing 52 card IDs.
3. Add buttons that draw and shuffle.

**We'll compile after each change.** No giant code dump followed by thirty compiler errors.

## Step 9.1 — Move Card into its own files

Create `include/Card.hpp`. It holds only the **declarations**:

```cpp
#pragma once

#include <string>

class Card {
private:
    int id;

public:
    Card(int id = 0);

    int getId() const;
    int getSuit() const;
    int getRank() const;

    std::string rankName() const;
    std::string suitName() const;
    std::string toString() const;

    void setId(int newId);
};
```

Notice the default argument `= 0` appears in the **header only**, not again in the `.cpp` file.

Now create `src/Card.cpp` with the **definitions**:

```cpp
#include "Card.hpp"

#include <vector>

Card::Card(int id) : id(0) {
    setId(id);
}

int Card::getId() const {
    return id;
}

int Card::getSuit() const {
    return id / 13;
}

int Card::getRank() const {
    return id % 13;
}

std::string Card::rankName() const {
    static const std::vector<std::string> ranks = {
        "Ace", "2", "3", "4", "5", "6", "7",
        "8", "9", "10", "Jack", "Queen", "King"
    };

    return ranks[getRank()];
}

std::string Card::suitName() const {
    static const std::vector<std::string> suits = {
        "Clubs", "Diamonds", "Hearts", "Spades"
    };

    return suits[getSuit()];
}

std::string Card::toString() const {
    return rankName() + " of " + suitName();
}

void Card::setId(int newId) {
    if (newId >= 0 && newId < 52) {
        id = newId;
    }
}
```

We made one small improvement while moving the code. Look at the constructor:

```cpp
Card::Card(int id) : id(0) {
    setId(id);
}
```

It starts at a valid ID (0), then uses `setId()` to apply the validation rule. So `Card(999)` becomes card 0 instead of an invalid card. The rule now lives in **one place**.

### Update `main.cpp`

1. **Delete** the `class Card { ... };` from `main.cpp`.
2. Add near the other includes:

```cpp
#include "Card.hpp"
```

### Update CMake

Add the new file to the `war` target:

```cmake
add_executable(war
    src/main.cpp
    src/Card.cpp
)
```

Compile and run:

```bash
cmake -S . -B build
cmake --build build --target war
./build/war
```

**Checkpoint:** The program behaves *exactly* as it did in Lesson 08.

That's the point. We changed the structure without changing the behavior. That's called **refactoring**.

**Question:** What error would you get if you forgot to add `src/Card.cpp` to CMake? (Hint: Lesson 06.)

---

## Step 9.2 — Create the Deck class

Create `include/Deck.hpp`:

```cpp
#pragma once

#include <vector>

class Deck {
private:
    std::vector<int> cards;

public:
    Deck();

    int size() const;
};
```

Notice:

```cpp
std::vector<int> cards;
```

We're storing card **IDs**, not 52 `Card` objects. The integers already identify every card. When we need a card's name, we can build a `Card` from the ID on the spot.

**Question:** Why is `cards` private?

Because nothing outside `Deck` should be able to add, remove, or reorder cards except through the deck's own methods.

Create `src/Deck.cpp`:

```cpp
#include "Deck.hpp"

Deck::Deck() {
    for (int i = 0; i < 52; i++) {
        cards.push_back(i);
    }
}

int Deck::size() const {
    return static_cast<int>(cards.size());
}
```

**Why the `static_cast<int>`?** `cards.size()` returns an unsigned type (`size_t`). We return `int` so callers can safely do math like `size() - 1` without surprises.

Add `src/Deck.cpp` to the `war` target in `CMakeLists.txt`:

```cmake
add_executable(war
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
)
```

Compile. **Checkpoint:** `Deck` compiles, but we haven't used it yet.

---

## Step 9.3 — Show the deck

In `main.cpp`, add:

```cpp
#include "Deck.hpp"
```

Now replace the **whole body** of `main()` with something very simple. (Your Lesson 08 version is safe in git.)

```cpp
int main() {

    Deck deck;

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        return vbox({
            text("TinyChunks 09") | bold | center,

            separator(),

            text("Cards remaining: " + std::to_string(deck.size())) | center,

        }) | border;
    });

    screen.Loop(renderer);
}
```

Compile and run:

```text
┌─────────────────────────┐
│      TinyChunks 09      │
├─────────────────────────┤
│   Cards remaining: 52   │
└─────────────────────────┘
```

---

## Step 9.4 — Add a `draw()` method

In `include/Deck.hpp`, add to the public section:

```cpp
int draw();
```

In `src/Deck.cpp`:

```cpp
int Deck::draw() {
    if (cards.empty()) {
        return -1;
    }

    int card = cards.back();
    cards.pop_back();

    return card;
}
```

**Why return `-1`?** Valid card IDs are 0–51, so `-1` can never be mistaken for a real card. A special value like this is called a **sentinel**. (Later, you could look at `std::optional<int>` as a cleaner alternative.)

**Why draw from the back?** `back()` and `pop_back()` are constant time. Removing from the *front* with `cards.erase(cards.begin())` shifts every remaining element down one slot. For 52 cards nobody will notice, but it's a good habit to think about.

Compile.

---

## Step 9.5 — Add a Draw button

In `main()`, we need somewhere to remember the most recently drawn card:

```cpp
Deck deck;

int lastCard = -1;
```

Create a button after the screen:

```cpp
auto drawButton = Button("Draw Card", [&] {
    lastCard = deck.draw();
});
```

Now update the renderer:

```cpp
auto renderer = Renderer(drawButton, [&] {

    std::string cardText = "No card drawn";

    if (lastCard >= 0) {
        Card card(lastCard);
        cardText = card.toString();
    }

    return vbox({
        text("TinyChunks 09") | bold | center,

        separator(),

        text("Cards remaining: " + std::to_string(deck.size())) | center,

        separator(),

        text(cardText) | center,

        separator(),

        drawButton->Render() | center,

    }) | border;
});
```

Notice that the renderer lambda can contain ordinary statements before its `return`. It's just a function.

Compile and run. Click **Draw Card**.

Because the deck starts in order (0–51) and we draw from the back, the first card is the **King of Spades** (ID 51).

Keep drawing until the deck is empty, then click once more.

**Question:** What happens? Why?

`draw()` returns `-1`, we store it in `lastCard`, and the display goes back to "No card drawn". That's not ideal.

---

## Step 9.6 — Improve the empty-deck behavior

Change the callback:

```cpp
auto drawButton = Button("Draw Card", [&] {

    int card = deck.draw();

    if (card != -1) {
        lastCard = card;
    }
});
```

Now the last real card stays visible after the deck runs out.

**Checkpoint:** We improved the behavior *without changing* `Deck`.

---

## Step 9.7 — Add Shuffle

In `include/Deck.hpp`, add:

```cpp
void shuffle();
```

At the top of `src/Deck.cpp`, add:

```cpp
#include <algorithm>
#include <random>
```

Then implement:

```cpp
void Deck::shuffle() {
    static std::mt19937 rng(std::random_device{}());

    std::shuffle(cards.begin(), cards.end(), rng);
}
```

`std::random_device` provides a random seed, `std::mt19937` is a fast random number generator, and `std::shuffle` does the shuffling. **We don't need to write our own shuffle algorithm.** (`static` means the generator is created once, not on every shuffle.)

Now add a Shuffle button in `main()`:

```cpp
auto shuffleButton = Button("Shuffle", [&] {
    deck.shuffle();
});
```

We have two interactive components, so we need a container (Lesson 04):

```cpp
auto buttons = Container::Horizontal({
    drawButton,
    shuffleButton,
});
```

Change the renderer to use the container:

```cpp
auto renderer = Renderer(buttons, [&] {
```

And replace:

```cpp
drawButton->Render() | center,
```

with:

```cpp
buttons->Render() | center,
```

Compile and run. Shuffle, then draw.

Notice that shuffling doesn't bring back drawn cards. It only reorders the cards still in the deck.

---

## Checkpoint: complete `src/main.cpp`

<details>
<summary>Click to compare your file</summary>

<!-- checkpoint: main.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

#include "Card.hpp"
#include "Deck.hpp"

using namespace ftxui;

int main() {

    Deck deck;

    int lastCard = -1;

    auto screen = ScreenInteractive::TerminalOutput();

    auto drawButton = Button("Draw Card", [&] {

        int card = deck.draw();

        if (card != -1) {
            lastCard = card;
        }
    });

    auto shuffleButton = Button("Shuffle", [&] {
        deck.shuffle();
    });

    auto buttons = Container::Horizontal({
        drawButton,
        shuffleButton,
    });

    auto renderer = Renderer(buttons, [&] {

        std::string cardText = "No card drawn";

        if (lastCard >= 0) {
            Card card(lastCard);
            cardText = card.toString();
        }

        return vbox({
            text("TinyChunks 09") | bold | center,

            separator(),

            text("Cards remaining: " + std::to_string(deck.size())) | center,

            separator(),

            text(cardText) | center,

            separator(),

            buttons->Render() | center,

        }) | border;
    });

    screen.Loop(renderer);
}
```

</details>

---

## Step 9.8 — Student challenge

Add a method to `Deck`:

```cpp
void reset();
```

Requirements:

1. Restore all 52 cards to the deck (in order).
2. Add a **Reset** button to the interface.
3. Resetting also sets the displayed card back to "No card drawn".
4. Add a **Reset & Shuffle** button that calls both methods.
5. Keep all deck-management logic inside `Deck`.

**Bonus:** Add `bool empty() const;` and use it to display `Deck is empty!` when no cards remain.

---

## Project structure after Lesson 09

```text
tinychunks/
├── CMakeLists.txt
├── examples/          (Lessons 01–07)
├── include/
│   ├── Card.hpp
│   └── Deck.hpp
└── src/
    ├── main.cpp
    ├── Card.cpp
    └── Deck.cpp
```

We now have two reusable classes:

- **`Card`** interprets an integer ID as a playing card.
- **`Deck`** manages an ordered collection of card IDs and supports drawing and shuffling.

Neither knows anything about FTXUI. The application uses their public interfaces.

## Commit your work

```bash
git add .
git commit -m "Lesson 09: Card files and Deck class"
```

### Next: TinyChunks 10 — Introducing a Hand

Right now, a drawn card just vanishes. We'll create a `Hand` class to hold the cards we draw:

```text
   Deck  ──draw()──►  card ID  ──add()──►  Hand
```

Then we'll display every card in the hand, building the FTXUI layout dynamically from the hand's contents.
