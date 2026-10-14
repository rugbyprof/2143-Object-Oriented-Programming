# TinyChunks 10 — Introducing the Hand Class

```yaml
course: 2143 - Object-Oriented Programming
project: tinychunks
lesson: 10 - Hand ADT
previous: Lesson 09 (src/main.cpp)
new_files:
  - include/Hand.hpp
  - src/Hand.cpp
concepts:
  - Encapsulation and invariants
  - std::vector
  - Objects collaborating through the application
  - Building FTXUI layouts dynamically
```

Our deck can shuffle and draw cards, but there's a problem:

**When we draw a card, where does it go?**

Right now, the application only remembers the most recently drawn card. Let's create a `Hand` class that keeps every card we draw.

## Step 10.1 — Create the Hand class

Create `include/Hand.hpp`. Start with the smallest useful class:

```cpp
#pragma once

#include <vector>

class Hand {
private:
    std::vector<int> cards;

public:
    int size() const;
};
```

Like `Deck`, we store **card IDs**, not `Card` objects.

Create `src/Hand.cpp`:

```cpp
#include "Hand.hpp"

int Hand::size() const {
    return static_cast<int>(cards.size());
}
```

Add `src/Hand.cpp` to the `war` target in `CMakeLists.txt`:

```cmake
add_executable(war
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Hand.cpp
)
```

Compile:

```bash
cmake -S . -B build
cmake --build build --target war
```

### Discussion

**Why doesn't `Hand` need a constructor?**

Because `std::vector` already starts out empty. The compiler-generated default constructor for `Hand` does everything we need. We *could* write `Hand() {}`, but it accomplishes nothing.

**Don't write code merely because C++ allows it.**

---

## Step 10.2 — Add cards to the hand

In `Hand.hpp`, add to the public section:

```cpp
void add(int cardId);
```

In `Hand.cpp`:

```cpp
void Hand::add(int cardId) {
    if (cardId >= 0 && cardId < 52) {
        cards.push_back(cardId);
    }
}
```

Compile.

### Discussion

**Why does `add()` validate the card ID?**

Because a class should protect its own **invariants**, the rules that must always be true about its data. For `Hand`, the rule is "every entry is a valid card ID."

`Deck::draw()` can return `-1`. Someone could also call `hand.add(999)`. `Hand` shouldn't blindly accept either.

Notice that `Hand` doesn't know anything about `Deck`. It just accepts valid card IDs.

---

## Step 10.3 — Create a Hand in the application

In `main.cpp`, add:

```cpp
#include "Hand.hpp"
```

Inside `main()`, right after the deck:

```cpp
Deck deck;
Hand hand;
```

In the renderer, add a line right below "Cards remaining":

```cpp
text("Cards in hand: " + std::to_string(hand.size())) | center,
```

Compile and run:

```text
┌────────────────────────────┐
│       TinyChunks 10        │
├────────────────────────────┤
│    Cards remaining: 52     │
│     Cards in hand: 0       │
├────────────────────────────┤
│       No card drawn        │
├────────────────────────────┤
│   [ Draw Card ] [ Shuffle ]│
└────────────────────────────┘
```

(Update the title text to `"TinyChunks 10"` while you're there.)

**Checkpoint:** Two objects exist side by side, but no cards move between them yet.

---

## Step 10.4 — Draw a card into the hand

Find the Draw button callback and add **one line**:

```cpp
auto drawButton = Button("Draw Card", [&] {
    int card = deck.draw();

    if (card != -1) {
        hand.add(card);
        lastCard = card;
    }
});
```

Compile and run. Click Draw Card a few times:

```text
Cards remaining: 49
Cards in hand: 3
```

### What just happened?

```text
       Deck
        │
        │ draw()
        ▼
    card ID 51
        │
        │ add(51)
        ▼
       Hand
```

`Deck` doesn't know about `Hand`. `Hand` doesn't know about `Deck`. **The application coordinates the transfer.**

We could have written `deck.dealTo(hand)`, but then `Deck` would depend on `Hand`. Keeping them independent means each one can be used, tested, and changed on its own.

---

## Step 10.5 — Look at individual cards

The hand knows how many cards it has, but we can't see them.

In `Hand.hpp`:

```cpp
int getCard(int index) const;
```

In `Hand.cpp`:

```cpp
int Hand::getCard(int index) const {
    if (index < 0 || index >= size()) {
        return -1;
    }

    return cards[index];
}
```

Now `hand.getCard(0)` returns the ID of the first card in the hand.

Compile.

### Discussion: why not just make the vector public?

```cpp
class Hand {
public:
    std::vector<int> cards;
};
```

Then any code could write `hand.cards.push_back(999);` and break the invariant. Keeping the vector private means **`Hand` decides which operations are allowed.**

---

## Step 10.6 — Display every card in the hand

Up to now, every layout had a fixed number of elements:

```cpp
vbox({
    text("Card 1"),
    text("Card 2"),
    text("Card 3"),
});
```

But a hand can hold anywhere from 0 to 52 cards. We need to **build the layout in a loop**.

Inside the renderer lambda, before `return vbox(...)`, add:

```cpp
Elements handElements;

for (int i = 0; i < hand.size(); i++) {
    Card card(hand.getCard(i));

    handElements.push_back(
        text(card.toString())
    );
}
```

`Elements` is FTXUI's name for `std::vector<Element>`. We're building a vector of visual elements from the hand's contents.

Now add these to the renderer's `vbox`, just above the final separator and buttons:

```cpp
separator(),

text("Your Hand") | bold | center,

vbox(std::move(handElements)) | center,
```

`std::move` hands the vector to `vbox` without copying it. We don't need `handElements` afterward.

Compile and run. Draw three cards (without shuffling):

```text
│         Your Hand          │
│       King of Spades       │
│      Queen of Spades       │
│       Jack of Spades       │
```

The number of displayed lines now depends on the application's state. **We didn't create 52 text widgets ahead of time.**

---

## Step 10.7 — Clear the hand

In `Hand.hpp`:

```cpp
void clear();
```

In `Hand.cpp`:

```cpp
void Hand::clear() {
    cards.clear();
}
```

In `main()`, add a button:

```cpp
auto clearButton = Button("Clear Hand", [&] {
    hand.clear();
    lastCard = -1;
});
```

**Add it to the container**, not just the renderer. Otherwise it will be drawn but unreachable:

```cpp
auto buttons = Container::Horizontal({
    drawButton,
    shuffleButton,
    clearButton,
});
```

Compile and run.

### Design question

When we clear the hand, **where do those cards go?** Nowhere. They vanish from the program. That's fine for this exercise, but a real card game would need a discard pile. Keep that in mind; it's a natural reason to add a class later.

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
#include "Hand.hpp"

using namespace ftxui;

int main() {

    Deck deck;
    Hand hand;

    int lastCard = -1;

    auto screen = ScreenInteractive::TerminalOutput();

    auto drawButton = Button("Draw Card", [&] {
        int card = deck.draw();

        if (card != -1) {
            hand.add(card);
            lastCard = card;
        }
    });

    auto shuffleButton = Button("Shuffle", [&] {
        deck.shuffle();
    });

    auto clearButton = Button("Clear Hand", [&] {
        hand.clear();
        lastCard = -1;
    });

    auto buttons = Container::Horizontal({
        drawButton,
        shuffleButton,
        clearButton,
    });

    auto renderer = Renderer(buttons, [&] {

        std::string cardText = "No card drawn";

        if (lastCard >= 0) {
            Card card(lastCard);
            cardText = card.toString();
        }

        Elements handElements;

        for (int i = 0; i < hand.size(); i++) {
            Card card(hand.getCard(i));

            handElements.push_back(
                text(card.toString())
            );
        }

        return vbox({
            text("TinyChunks 10") | bold | center,

            separator(),

            text("Cards remaining: " + std::to_string(deck.size())) | center,
            text("Cards in hand: " + std::to_string(hand.size())) | center,

            separator(),

            text(cardText) | center,

            separator(),

            text("Your Hand") | bold | center,

            vbox(std::move(handElements)) | center,

            separator(),

            buttons->Render() | center,

        }) | border;
    });

    screen.Loop(renderer);
}
```

</details>

---

## Step 10.8 — Student challenge

1. Add a **Draw 5** button that draws five cards into the hand at once. What should happen if fewer than five cards remain?
2. Add `bool contains(int cardId) const;` to `Hand`. Use it to display `"You have the Ace of Spades!"` when card 39 is in the hand.

Rules: no code outside `Hand` may touch its vector, and the renderer must not do any card math.

---

## Project structure after Lesson 10

```text
tinychunks/
├── CMakeLists.txt
├── examples/          (Lessons 01–07)
├── include/
│   ├── Card.hpp
│   ├── Deck.hpp
│   └── Hand.hpp
└── src/
    ├── main.cpp
    ├── Card.cpp
    ├── Deck.cpp
    └── Hand.cpp
```

| Class  | Responsibility                               |
| ------ | -------------------------------------------- |
| `Card` | Interpret an integer as a playing card       |
| `Deck` | Maintain the remaining cards and their order |
| `Hand` | Store cards that have been drawn             |

No inheritance anywhere. Just **encapsulation, vectors, and small public interfaces**, coordinated by the application.

## Commit your work

```bash
git add .
git commit -m "Lesson 10: Hand class"
```

### Next: TinyChunks 11 — Rendering Actual Playing Cards

Instead of a list of names, we'll write a reusable function that draws real-looking cards:

```text
┌───────┐ ┌───────┐ ┌───────┐
│K      │ │Q      │ │J      │
│       │ │       │ │       │
│   ♠   │ │   ♠   │ │   ♠   │
│       │ │       │ │       │
│      K│ │      Q│ │      J│
└───────┘ └───────┘ └───────┘
```
