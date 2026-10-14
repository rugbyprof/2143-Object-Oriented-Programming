# GameOfWar 11 — Rendering Playing Cards with FTXUI

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 11 - Rendering Playing Cards
previous: Lesson 10 (src/main.cpp)
changed_file: src/main.cpp
concepts:
  - Reusable functions
  - Pass by const reference
  - FTXUI decorators (size, filler, color)
  - Separating models from presentation
```

We can draw cards, shuffle the deck, and list the hand. But our cards look like this:

```text
King of Spades
Queen of Spades
Jack of Spades
```

**Today's goal:** write one reusable function that takes a `Card` and returns an FTXUI `Element` that looks like a playing card.

We won't create another class. We don't need one yet.

---

## Step 11.1 — Render one card

In `main.cpp`, above `main()`, add:

```cpp
Element renderCard(const Card& card) {
    return vbox({
        text(card.rankName()),
        separator(),
        text(card.suitName()),
    }) | border;
}
```

The parameter is a **const reference**:

```cpp
const Card& card
```

The function can read the card without copying it, and the compiler won't let it modify the card.

### Test it by itself

Inside the renderer lambda, **temporarily** comment out the existing `return vbox({...}) | border;` and put this in its place:

```cpp
return vbox({
    text("GameOfWar 11") | bold | center,
    separator(),
    renderCard(Card(51)) | center,
}) | border;
```

Compile and run:

```bash
cmake --build build --target war
./build/war
```

```text
┌─────────────────────┐
│    GameOfWar 11     │
├─────────────────────┤
│     ┌──────┐        │
│     │King  │        │
│     ├──────┤        │
│     │Spades│        │
│     └──────┘        │
└─────────────────────┘
```

### Stop and discuss

`Card` didn't change at all. It still only knows about IDs, ranks, and suits. **The new function knows how to display a card.**

That's **separation of concerns**. We could write ten different rendering functions without touching `Card`.

---

## Step 11.2 — Use a one-character rank

Real playing cards show `K`, not `King`. Add this function **above** `renderCard()`:

```cpp
std::string shortRank(const Card& card) {
    const std::string ranks = "A23456789TJQK";
    return std::string(1, ranks[card.getRank()]);
}
```

`T` stands for ten so every rank is one character. The rank index (0–12) picks a character out of the string. `std::string(1, c)` turns that one `char` into a string.

Update `renderCard()`:

```cpp
Element renderCard(const Card& card) {
    return vbox({
        text(shortRank(card)),
        separator(),
        text(card.suitName()),
    }) | border;
}
```

Compile and run.

---

## Step 11.3 — Add suit symbols

Add this function above `renderCard()`:

```cpp
std::string suitSymbol(const Card& card) {
    static const std::vector<std::string> suits = {
        "♣", "♦", "♥", "♠"
    };

    return suits[card.getSuit()];
}
```

Make sure `main.cpp` has:

```cpp
#include <vector>
```

**Question:** Why is each symbol a `std::string` and not a `char`?

Because `♠` is not a single byte. In UTF-8 it takes three bytes, so it can't fit in one `char`.

Update `renderCard()`:

```cpp
Element renderCard(const Card& card) {
    return vbox({
        text(shortRank(card)),
        separator(),
        text(suitSymbol(card)) | center,
    }) | border;
}
```

Compile and run:

```text
┌─────┐
│K    │
├─────┤
│  ♠  │
└─────┘
```

> If you see `?` or boxes instead of suit symbols, your terminal font doesn't support them. Try a different terminal font, or temporarily use `"C", "D", "H", "S"`.

---

## Step 11.4 — Give every card the same size

Right now a card's width depends on its content. When we line up several cards, we want them all the same size.

Replace `renderCard()` with:

```cpp
Element renderCard(const Card& card) {

    std::string rank = shortRank(card);
    std::string suit = suitSymbol(card);

    return vbox({
        text(rank),
        filler(),
        text(suit) | center,
        filler(),
        text(rank) | align_right,
    })
    | size(WIDTH, EQUAL, 7)
    | size(HEIGHT, EQUAL, 5)
    | border;
}
```

Compile and run:

```text
┌───────┐
│K      │
│       │
│   ♠   │
│       │
│      K│
└───────┘
```

- `filler()` is an empty element that **stretches** to soak up extra space. Two fillers push the suit to the middle.
- `size(WIDTH, EQUAL, 7)` fixes the inside width at 7 columns. The border adds one more on each side.

We've chained several decorators with `|`, which is operator overloading making the code read almost like a sentence.

---

## Step 11.5 — Add card colors

Hearts and diamonds are red. Clubs and spades use the terminal's normal text color, because terminal backgrounds vary.

Update `renderCard()`:

```cpp
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
```

Try changing the test card:

| Test                   | Expected                |
| ---------------------- | ----------------------- |
| `renderCard(Card(25))` | King of Diamonds, red   |
| `renderCard(Card(38))` | King of Hearts, red     |
| `renderCard(Card(51))` | King of Spades, default |
| `renderCard(Card(0))`  | Ace of Clubs, default   |

---

## Step 11.6 — Render the whole hand

Now put the real interface back. **Delete** the temporary test `return` and uncomment your original `return vbox({...}) | border;`.

Find the loop that builds the hand:

```cpp
handElements.push_back(
    text(card.toString())
);
```

Change it to use our function, and add a space after each card:

```cpp
handElements.push_back(
    renderCard(card)
);

handElements.push_back(
    text(" ")
);
```

Then change the hand's layout from vertical to horizontal:

```cpp
vbox(std::move(handElements)) | center,
```

becomes:

```cpp
hbox(std::move(handElements)) | center,
```

Compile, run, and draw three cards:

```text
┌───────────────────────────────────────────┐
│               GameOfWar 11                │
├───────────────────────────────────────────┤
│            Cards remaining: 49            │
│             Cards in hand: 3              │
├───────────────────────────────────────────┤
│              Jack of Spades               │
├───────────────────────────────────────────┤
│                 Your Hand                 │
│     ┌───────┐  ┌───────┐  ┌───────┐       │
│     │K      │  │Q      │  │J      │       │
│     │       │  │       │  │       │       │
│     │   ♠   │  │   ♠   │  │   ♠   │       │
│     │       │  │       │  │       │       │
│     │      K│  │      Q│  │      J│       │
│     └───────┘  └───────┘  └───────┘       │
├───────────────────────────────────────────┤
│ [ Draw Card ] [ Shuffle ] [ Clear Hand ]  │
└───────────────────────────────────────────┘
```

**Checkpoint:** Real-looking cards, and we didn't modify `Card`, `Deck`, or `Hand`.

For a handful of cards this works nicely. With 52 cards, the row gets far wider than the terminal. That's a **layout** problem, not a card-model problem.

---

## Step 11.7 — Student challenge

Add a second visual style with a parameter:

```cpp
Element renderCard(const Card& card, bool compact = false);
```

**Compact:**

```text
┌─────┐
│ A ♠ │
└─────┘
```

**Full** (what we have now):

```text
┌───────┐
│A      │
│       │
│   ♠   │
│       │
│      A│
└───────┘
```

Use an `if` statement to pick the layout. Add a button that toggles a `bool compact` variable so you can switch styles while the program runs.

**Constraint:** Do not create `CompactCard` or `FullCard` subclasses. We're changing the *presentation*, not the *kind* of card.

---

## Where we are

| Piece          | Responsibility                            |
| -------------- | ----------------------------------------- |
| `Card`         | Represents a playing card                 |
| `Deck`         | Manages available cards                   |
| `Hand`         | Stores drawn cards                        |
| `renderCard()` | Turns a card into an FTXUI element        |
| `main()`       | Handles interaction and displays the hand |

No new files this lesson.

## Putting it Together

Here is every file in the War app at the end of Lesson 11. Files marked **new** or **changed** were touched in this lesson; the rest are the same as last lesson.

### `src/main.cpp` (changed)

<!-- file: src/main.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>
#include <vector>

#include "Card.hpp"
#include "Deck.hpp"
#include "Hand.hpp"

using namespace ftxui;

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
                renderCard(card)
            );

            handElements.push_back(
                text(" ")
            );
        }

        return vbox({
            text("GameOfWar 11") | bold | center,

            separator(),

            text("Cards remaining: " + std::to_string(deck.size())) | center,
            text("Cards in hand: " + std::to_string(hand.size())) | center,

            separator(),

            text(cardText) | center,

            separator(),

            text("Your Hand") | bold | center,

            hbox(std::move(handElements)) | center,

            separator(),

            buttons->Render() | center,

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

---

## Commit your work

```bash
git add .
git commit -m "Lesson 11: renderCard"
```

### Next: GameOfWar 12 — Selecting Cards in a Hand

Our cards are **elements**: we can see them, but we can't interact with them individually. Next, we'll let the player move a highlight across the hand with the arrow keys. That means catching keyboard events ourselves.
