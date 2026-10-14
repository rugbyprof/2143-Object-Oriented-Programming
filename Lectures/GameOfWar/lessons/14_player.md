# GameOfWar 14 — Introducing the `Player` Class

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 14 - Player
previous: Lesson 13
new_files:
  - include/Player.hpp
  - src/Player.cpp
changed_files:
  - include/HandView.hpp
  - src/HandView.cpp
  - src/main.cpp
concepts:
  - Has-a vs is-a
  - Composition (value members)
  - Ownership vs references
  - Delegation
  - Const-correctness
```

We're moving from cards and hands toward an actual game of War. Today's big question:

**Does an object *own* another object, or merely *refer to* it?**

---

## Step 14.1 — What is a Player?

For War, a player needs two things:

1. A name.
2. A collection of cards.

We already have a class for a collection of cards. So should `Player` inherit from `Hand`?

```cpp
class Player : public Hand {   // ✗ No
    // ...
};
```

**No.** Say it out loud:

- "A player **is a** hand." ✗ Wrong.
- "A player **has a** hand." ✓ Right.

*Has-a* means **composition**. The hand is a member:

```cpp
class Player {
private:
    std::string name;
    Hand hand;
};
```

When a `Player` is created, its `Hand` is created automatically. When the `Player` is destroyed, its `Hand` goes with it. No pointers, no `new`, no `delete`.

### Create `include/Player.hpp`

```cpp
#pragma once

#include <string>

#include "Hand.hpp"

class Player {
private:
    std::string name;
    Hand hand;

public:
    Player(const std::string& name);

    std::string getName() const;
    int cardCount() const;
};
```

We only add what we need right now, not every method a player might someday want.

---

## Step 14.2 — Implement Player

Create `src/Player.cpp`:

```cpp
#include "Player.hpp"

Player::Player(const std::string& name)
    : name(name) {
}

std::string Player::getName() const {
    return name;
}

int Player::cardCount() const {
    return hand.size();
}
```

**What about initializing `hand`?** We don't have to. `Hand` has a default constructor, so C++ builds it automatically. Writing `: name(name), hand()` would also work, but adds nothing.

**Notice `cardCount()`.** The player doesn't know how the hand stores its cards. It just asks the hand. Passing a request along to a member object is called **delegation**.

Add `src/Player.cpp` to `CMakeLists.txt`:

```cmake
add_executable(war
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Hand.cpp
    src/HandView.cpp
    src/Player.cpp
)
```

Compile:

```bash
cmake -S . -B build
cmake --build build --target war
```

---

## Step 14.3 — Two players on screen

In `main.cpp`, add:

```cpp
#include "Player.hpp"
```

Replace the **whole body** of `main()` with a small test. (Your Lesson 13 version is safe in git.)

```cpp
int main() {

    Player alice("Alice");
    Player bob("Bob");

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        return vbox({
            text(alice.getName() + ": " + std::to_string(alice.cardCount())),
            text(bob.getName() + ": " + std::to_string(bob.cardCount())),
        }) | border;
    });

    screen.Loop(renderer);
}
```

Compile and run (Ctrl+C to exit):

```text
┌──────────┐
│Alice: 0  │
│Bob: 0    │
└──────────┘
```

**Question:** How many `Hand` objects exist right now?

**Two.** Each player owns its own:

```text
┌──────────────────┐   ┌──────────────────┐
│      Alice       │   │       Bob        │
│  ┌────────────┐  │   │  ┌────────────┐  │
│  │ Hand (0)   │  │   │  │ Hand (0)   │  │
│  └────────────┘  │   │  └────────────┘  │
└──────────────────┘   └──────────────────┘
```

---

## Step 14.4 — Let players receive cards

`Hand` already has `add()`. `Player` keeps its hand private, so it needs its own method that delegates.

In `Player.hpp`:

```cpp
void receiveCard(int cardId);
```

In `Player.cpp`:

```cpp
void Player::receiveCard(int cardId) {
    hand.add(cardId);
}
```

Test it in `main()`, right after creating the players:

```cpp
alice.receiveCard(51);
alice.receiveCard(50);

bob.receiveCard(12);
```

Compile and run:

```text
┌──────────┐
│Alice: 2  │
│Bob: 1    │
└──────────┘
```

---

## Step 14.5 — Ownership versus references

We chose:

```cpp
class Player {
    Hand hand;      // Player OWNS its hand
};
```

We *could* have written:

```cpp
class Player {
    Hand& hand;     // Player REFERS TO a hand owned by someone else
};
```

Then every hand would have to be created outside first:

```cpp
Hand aliceHand;
Player alice("Alice", aliceHand);
```

Both are valid C++. They mean different things:

| Member                  | Meaning                                  | Who keeps it alive? |
| ----------------------- | ---------------------------------------- | ------------------- |
| `Hand hand;`            | Player owns its hand                     | Player              |
| `Hand& hand;`           | Player refers to someone else's hand     | Someone else        |
| `Hand* hand;`           | Player points to a hand (or nothing)     | Depends             |
| `std::unique_ptr<Hand>` | Player owns a dynamically allocated hand | Player              |

Compare with `HandView` from Lesson 13: a **view** should *refer to* the hand it displays, which is why it holds `Hand&`. A **player** should *own* its hand.

**Prefer plain value members when they describe the relationship.** There's no reason for dynamic allocation here.

---

## Step 14.6 — Connect `HandView` to a player's hand

We want to draw each player's cards with `HandView`. But `HandView` needs a `Hand&`, and `Player` keeps its hand private.

Give `Player` **read-only** access. In `Player.hpp`:

```cpp
const Hand& getHand() const;
```

In `Player.cpp`:

```cpp
const Hand& Player::getHand() const {
    return hand;
}
```

Callers can *look at* the hand through this reference, but can't change it.

Now try:

```cpp
HandView aliceView(alice.getHand());
```

**It won't compile.** `HandView`'s constructor wants a `Hand&` (modifiable), and we're handing it a `const Hand&` (read-only). C++ won't silently drop the `const`.

### Fix `HandView`

Does `HandView` ever change the hand? Look at its methods. It reads `size()` and `getCard()`, and nothing else. Its *selection* is its own member, not part of the hand.

So `HandView` should promise not to modify the hand. Make three small changes:

In `include/HandView.hpp`:

```cpp
const Hand& hand;
```

```cpp
HandView(const Hand& h);
```

In `src/HandView.cpp`:

```cpp
HandView::HandView(const Hand& h) : hand(h) {
}
```

Compile.

This is **const-correctness**: if a class only needs to read something, say so in the type. The compiler then enforces the promise, and the class works with both const and non-const hands.

---

## Step 14.7 — Display both players' cards

Update `main()`:

```cpp
Player alice("Alice");
Player bob("Bob");

alice.receiveCard(51);
alice.receiveCard(50);

bob.receiveCard(12);

HandView aliceView(alice.getHand());
HandView bobView(bob.getHand());
```

Replace the renderer:

```cpp
auto renderer = Renderer([&] {
    return vbox({
        text("GameOfWar 14 - Players") | bold | center,

        separator(),

        text(alice.getName()) | bold,
        text("Cards: " + std::to_string(alice.cardCount())),
        aliceView.render(),

        separator(),

        text(bob.getName()) | bold,
        text("Cards: " + std::to_string(bob.cardCount())),
        bobView.render(),

    }) | border;
});
```

Compile and run:

```text
┌──────────────────────────────┐
│   GameOfWar 14 - Players     │
├──────────────────────────────┤
│Alice                         │
│Cards: 2                      │
│┌───────┐ ┌───────┐           │
││K      │ │Q      │           │
││       │ │       │           │
││   ♠   │ │   ♠   │           │
││       │ │       │           │
││      K│ │      Q│           │
│└───────┘ └───────┘           │
├──────────────────────────────┤
│Bob                           │
│Cards: 1                      │
│┌───────┐                     │
││K      │                     │
││       │                     │
││   ♣   │                     │
││       │                     │
││      K│                     │
│└───────┘                     │
└──────────────────────────────┘
```

(The first card of each hand is also highlighted blue. That's `HandView`'s selection, which we aren't using here.)

---

## Step 14.8 — Deal from a real deck

Add `#include "Deck.hpp"` if it isn't already there.

Replace the hard-coded test cards with a shuffled deck and a dealing loop:

```cpp
Deck deck;
deck.shuffle();

Player alice("Alice");
Player bob("Bob");

for (int i = 0; i < 5; i++) {
    alice.receiveCard(deck.draw());
    bob.receiveCard(deck.draw());
}

HandView aliceView(alice.getHand());
HandView bobView(bob.getHand());
```

Add one line to the renderer, below the separator under the title:

```cpp
text("Deck: " + std::to_string(deck.size()) + " cards remaining"),

separator(),
```

Compile and run. Each player gets five random cards, and the deck shows 42 remaining.

This is the first time `Deck`, `Player`, and `Hand` all work together. Notice that **`Deck` knows nothing about players, and players know nothing about decks.** `main()` coordinates:

```cpp
alice.receiveCard(deck.draw());
```

We *could* write `deck.deal(alice)`, but then `Deck` would depend on `Player`. Keeping them independent is simpler.

---

## Step 14.9 — A missing operation

War requires players to **play** cards, not just receive them. `Hand` can `add()`, `getCard()`, `size()`, and `clear()`, but it can't **remove and return** one card.

Where should that live?

- The *player* plays a card: `int Player::playCard();`
- But the player shouldn't touch the hand's vector directly.
- So `Hand` gets a new operation, and `Player` delegates:

```cpp
int Player::playCard() {
    return hand.removeCard();
}
```

We'll write it in Lesson 15. For now, notice that we **identified** a missing operation from a real need instead of adding it "just in case."

---

## Student challenge — Player statistics

Add to `Player`:

```cpp
int roundsWon = 0;

void winRound();
int getRoundsWon() const;
```

Display each player's rounds won. (You'll be able to use this in Lesson 15.)

**Don't** add a `roundsLost` variable. Rounds can end in ties, so losses aren't simply "rounds played minus rounds won". **Add state only when you actually need it.**

---

## Project structure after Lesson 14

```text
GameOfWar/
├── CMakeLists.txt
├── examples/          (Lessons 01–07)
├── include/
│   ├── Card.hpp
│   ├── Deck.hpp
│   ├── Hand.hpp
│   ├── HandView.hpp
│   └── Player.hpp
└── src/
    ├── main.cpp
    ├── Card.cpp
    ├── Deck.cpp
    ├── Hand.cpp
    ├── HandView.cpp
    └── Player.cpp
```

| Concept                | Example                                        |
| ---------------------- | ---------------------------------------------- |
| Composition            | `Player` contains a `Hand`                     |
| Encapsulation          | `Player` keeps its hand private                |
| Delegation             | `Player::cardCount()` calls `Hand::size()`     |
| Const-correctness      | `getHand()` returns `const Hand&`              |
| Reference vs ownership | `HandView` refers; `Player` owns               |

Still no inheritance. Our relationships are all *has-a* or *uses-a*, not *is-a*.

## Putting it Together

Here is every file in the War app at the end of Lesson 14. Files marked **new** or **changed** were touched in this lesson; the rest are the same as last lesson.

### `src/main.cpp` (changed)

<!-- file: src/main.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

#include "Deck.hpp"
#include "HandView.hpp"
#include "Player.hpp"

using namespace ftxui;

int main() {

    Deck deck;
    deck.shuffle();

    Player alice("Alice");
    Player bob("Bob");

    for (int i = 0; i < 5; i++) {
        alice.receiveCard(deck.draw());
        bob.receiveCard(deck.draw());
    }

    HandView aliceView(alice.getHand());
    HandView bobView(bob.getHand());

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        return vbox({
            text("GameOfWar 14 - Players") | bold | center,

            separator(),

            text("Deck: " + std::to_string(deck.size()) + " cards remaining"),

            separator(),

            text(alice.getName()) | bold,
            text("Cards: " + std::to_string(alice.cardCount())),
            aliceView.render(),

            separator(),

            text(bob.getName()) | bold,
            text("Cards: " + std::to_string(bob.cardCount())),
            bobView.render(),

        }) | border;
    });

    screen.Loop(renderer);
}
```

<details>
<summary><code>include/Card.hpp</code> (unchanged)</summary>

<!-- file: include/Card.hpp -->
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

</details>

<details>
<summary><code>src/Card.cpp</code> (unchanged)</summary>

<!-- file: src/Card.cpp -->
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

</details>

<details>
<summary><code>include/Deck.hpp</code> (unchanged)</summary>

<!-- file: include/Deck.hpp -->
```cpp
#pragma once

#include <vector>

class Deck {
private:
    std::vector<int> cards;

public:
    Deck();

    int size() const;
    int draw();
    void shuffle();
};
```

</details>

<details>
<summary><code>src/Deck.cpp</code> (unchanged)</summary>

<!-- file: src/Deck.cpp -->
```cpp
#include "Deck.hpp"

#include <algorithm>
#include <random>

Deck::Deck() {
    for (int i = 0; i < 52; i++) {
        cards.push_back(i);
    }
}

int Deck::size() const {
    return static_cast<int>(cards.size());
}

int Deck::draw() {
    if (cards.empty()) {
        return -1;
    }

    int card = cards.back();
    cards.pop_back();

    return card;
}

void Deck::shuffle() {
    static std::mt19937 rng(std::random_device{}());

    std::shuffle(cards.begin(), cards.end(), rng);
}
```

</details>

<details>
<summary><code>include/Hand.hpp</code> (unchanged)</summary>

<!-- file: include/Hand.hpp -->
```cpp
#pragma once

#include <vector>

class Hand {
private:
    std::vector<int> cards;

public:
    int size() const;

    void add(int cardId);
    int getCard(int index) const;
    void clear();
};
```

</details>

<details>
<summary><code>src/Hand.cpp</code> (unchanged)</summary>

<!-- file: src/Hand.cpp -->
```cpp
#include "Hand.hpp"

int Hand::size() const {
    return static_cast<int>(cards.size());
}

void Hand::add(int cardId) {
    if (cardId >= 0 && cardId < 52) {
        cards.push_back(cardId);
    }
}

int Hand::getCard(int index) const {
    if (index < 0 || index >= size()) {
        return -1;
    }

    return cards[index];
}

void Hand::clear() {
    cards.clear();
}
```

</details>

<details>
<summary><code>include/HandView.hpp</code> (changed)</summary>

<!-- file: include/HandView.hpp -->
```cpp
#pragma once

#include <string>

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>

#include "Card.hpp"
#include "Hand.hpp"

// Draws one card. Lives here because HandView is its main user.
ftxui::Element renderCard(const Card& card);

class HandView {
private:
    const Hand& hand;
    int selectedCard = 0;

public:
    HandView(const Hand& h);

    int selectedIndex() const;
    void resetSelection();

    bool handleEvent(ftxui::Event event);

    ftxui::Element render() const;

    std::string selectedCardName() const;

    ftxui::Component attach(ftxui::Component child);
};
```

</details>

<details>
<summary><code>src/HandView.cpp</code> (changed)</summary>

<!-- file: src/HandView.cpp -->
```cpp
#include "HandView.hpp"

#include <vector>

using namespace ftxui;

namespace {

std::string shortRank(const Card& card) {
    const std::string ranks = "A23456789TJQK";
    return std::string(1, ranks[card.getRank()]);
}

std::string suitSymbol(const Card& card) {
    static const std::vector<std::string> suits = {
        "♣", "♦", "♥", "♠"
    };

    return suits[card.getSuit()];
}

}

Element renderCard(const Card& card) {

    std::string rank = shortRank(card);
    std::string suit = suitSymbol(card);

    bool isRed = card.getSuit() == 1 || card.getSuit() == 2;

    auto face = vbox({
        text(rank),
        filler(),
        text(suit) | center,
        filler(),
        text(rank) | align_right,
    })
    | size(WIDTH, EQUAL, 7)
    | size(HEIGHT, EQUAL, 5)
    | border;

    if (isRed) {
        return face | color(Color::Red);
    }

    return face;
}

HandView::HandView(const Hand& h) : hand(h) {
}

int HandView::selectedIndex() const {
    return selectedCard;
}

void HandView::resetSelection() {
    selectedCard = 0;
}

bool HandView::handleEvent(Event event) {
    if (event == Event::ArrowRight) {
        if (selectedCard + 1 < hand.size()) {
            selectedCard++;
        }
        return true;
    }

    if (event == Event::ArrowLeft) {
        if (selectedCard > 0) {
            selectedCard--;
        }
        return true;
    }

    return false;
}

Element HandView::render() const {
    Elements elements;

    for (int i = 0; i < hand.size(); i++) {
        Card card(hand.getCard(i));

        auto element = renderCard(card);

        if (i == selectedCard) {
            element = element | bgcolor(Color::Blue);
        }

        elements.push_back(element);
        elements.push_back(text(" "));
    }

    return hbox(std::move(elements));
}

std::string HandView::selectedCardName() const {
    if (hand.size() == 0) {
        return "No card selected";
    }

    Card card(hand.getCard(selectedCard));

    return card.toString();
}

Component HandView::attach(Component child) {
    return CatchEvent(child, [this](Event event) {
        return handleEvent(event);
    });
}
```

</details>

<details>
<summary><code>include/Player.hpp</code> (new)</summary>

<!-- file: include/Player.hpp -->
```cpp
#pragma once

#include <string>

#include "Hand.hpp"

class Player {
private:
    std::string name;
    Hand hand;

public:
    Player(const std::string& name);

    std::string getName() const;
    int cardCount() const;

    void receiveCard(int cardId);

    const Hand& getHand() const;
};
```

</details>

<details>
<summary><code>src/Player.cpp</code> (new)</summary>

<!-- file: src/Player.cpp -->
```cpp
#include "Player.hpp"

Player::Player(const std::string& name)
    : name(name) {
}

std::string Player::getName() const {
    return name;
}

int Player::cardCount() const {
    return hand.size();
}

void Player::receiveCard(int cardId) {
    hand.add(cardId);
}

const Hand& Player::getHand() const {
    return hand;
}
```

</details>

> **Linker errors?** Make sure `src/Player.cpp` is listed in `add_executable(war ...)` in `CMakeLists.txt`.

---

## Commit your work

```bash
git add .
git commit -m "Lesson 14: Player class"
```

### Next: Lesson 15 — The Rules of War

Each player plays a card, the higher rank wins both, and ties trigger a *war*. The real design question: **where should those rules live?** Not in `Player`, not in `Deck`, so we'll need a new class.
