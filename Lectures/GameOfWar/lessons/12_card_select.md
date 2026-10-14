# GameOfWar 12 — Selecting Cards with the Keyboard

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 12 - Selecting Cards
previous: Lesson 11 (src/main.cpp)
changed_file: src/main.cpp
concepts:
  - Selection state (position vs value)
  - CatchEvent and keyboard events
  - Consuming vs passing on events
  - Rendering from state
```

Our hand is drawn with `renderCard()`, which returns an FTXUI **`Element`**.

**An `Element` describes what something looks like. A `Component` can also respond to input.**

Today we'll let the player move a highlight across the hand with the arrow keys. We'll do it without creating any new class or file. Then, in Lesson 13, we'll look at what we wrote and decide whether it deserves a class.

The road from here to a finished game:

| Lesson         | Topic                          | Main concept                     |
| -------------- | ------------------------------ | -------------------------------- |
| **12 — Today** | Selecting cards                | Events and focus                 |
| 13             | Building a reusable `HandView` | Refactoring into a class         |
| 14             | Creating a `Player`            | Ownership and const-correctness  |
| 15             | Implementing War               | Game rules in their own class    |
| 16             | Completing the game            | State, edge cases, and testing   |

---

## Step 12.1 — Introduce selection state

Inside `main()`, right after creating the hand:

```cpp
Deck deck;
Hand hand;

int selectedCard = 0;
```

`selectedCard` is a **position in the hand**, not a card ID:

```text
Hand position:     0       1       2       3
                 ┌─────┐ ┌─────┐ ┌─────┐ ┌─────┐
Card ID:         │  51 │ │  12 │ │  29 │ │  44 │
                 └─────┘ └─────┘ └─────┘ └─────┘
                           ▲
                     selectedCard = 1
```

`hand.getCard(selectedCard)` turns the position into a card ID.

For now, add a line to the renderer's `vbox`, just below "Cards in hand":

```cpp
text("Selected position: " + std::to_string(selectedCard)) | center,
```

Change the title to `"GameOfWar 12"`, then compile and run.

**Checkpoint:** We have selection state, but nothing changes it yet.

---

## Step 12.2 — Catch keyboard events

FTXUI's `CatchEvent()` wraps a component and lets us look at every event *before* the component does.

At the top of `main.cpp`, add:

```cpp
#include <ftxui/component/event.hpp>
```

Find the last line of `main()`:

```cpp
screen.Loop(renderer);
```

Just before it, add:

```cpp
auto interactive = CatchEvent(renderer, [&](Event event) {
    if (event == Event::ArrowRight) {
        selectedCard++;
        return true;
    }

    return false;
});
```

Then change the loop to use the wrapped component:

```cpp
screen.Loop(interactive);
```

Compile and run. Press the right arrow a few times:

```text
Selected position: 0
Selected position: 1
Selected position: 2
```

**Question:** What do `return true` and `return false` mean?

- `true`: "I handled this event. Stop here."
- `false`: "Not mine. Pass it on to the wrapped component." That's how Enter still reaches the buttons.

**Notice** this lambda takes a parameter, `(Event event)`. FTXUI calls it once per event and tells us which event happened.

---

## Step 12.3 — Keep the selection valid

Problem: the selection grows forever, even with three cards in the hand.

Replace the event handler's body:

```cpp
auto interactive = CatchEvent(renderer, [&](Event event) {
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
});
```

Compile, run, draw several cards, and use both arrows. The selection now stays between `0` and `hand.size() - 1`.

When the hand is empty, `selectedCard` stays `0` even though there's no card there. We'll handle that when rendering.

**Trade-off:** Our handler now *consumes* Left and Right, so those keys no longer move focus between buttons. Use **Tab** / **Shift+Tab** to move between buttons. We'll revisit this design in Lesson 13.

---

## Step 12.4 — Highlight the selected card

Find the loop that builds the hand:

```cpp
handElements.push_back(
    renderCard(card)
);
```

Replace that `push_back` with:

```cpp
auto element = renderCard(card);

if (i == selectedCard) {
    element = element | bgcolor(Color::Blue);
}

handElements.push_back(element);
```

(Keep the `text(" ")` spacer after it.)

Compile, run, draw three cards, and press the arrows. The selected card gets a blue background.

### What changed?

We didn't touch `Card`, `Deck`, or `Hand`. We added a visual property **computed from application state**:

```text
  Application State   (selectedCard, hand)
          │
          ▼
   Renderer Lambda    (decides: is this card selected?)
          │
          ▼
   FTXUI Elements     (blue background or not)
          │
          ▼
  Terminal Display
```

We never "set a card's color". We change the **state**, and the next render reflects it. This is the core pattern of every GUI and TUI.

---

## Step 12.5 — Show the selected card's name

Inside the renderer lambda, before `return vbox(...)`, add:

```cpp
std::string selectedText = "No card selected";

if (hand.size() > 0) {
    Card card(hand.getCard(selectedCard));
    selectedText = "Selected: " + card.toString();
}
```

Add it to the layout, right below the "Selected position" line:

```cpp
text(selectedText) | center,
```

Compile and run:

```text
Selected position: 2
Selected: Jack of Spades
```

---

## Step 12.6 — Fix Clear Hand

Try this: draw five cards, move the selection to position 4, then click **Clear Hand**, then draw one card.

The selection is still `4`, but the hand only has one card. Nothing is highlighted.

Fix the Clear Hand callback so it also resets the selection:

```cpp
auto clearButton = Button("Clear Hand", [&] {
    hand.clear();
    selectedCard = 0;
    lastCard = -1;
});
```

**Lesson:** whenever you change data, think about what *other* state depended on it.

(If you did the Lesson 09 Reset challenge, reset `selectedCard` there too.)

---

## Step 12.7 — Student challenge

Add two keyboard shortcuts to the event handler:

- **Home:** select the first card.
- **End:** select the last card.

Home is free:

```cpp
if (event == Event::Home) {
    selectedCard = 0;
    return true;
}
```

Write End yourself. **Remember the hand might be empty.**

**Bonus:** make the selection wrap around: `0 → 1 → 2 → 0 → 1 ...`

```cpp
(selectedCard + 1) % hand.size()
```

But check that the hand isn't empty first. Modulo by zero is undefined behavior, which usually means a crash.

---

## An important design observation

Look at what `main()` now juggles for the hand display:

- The variable `selectedCard`
- Keyboard handling in `CatchEvent(...)`
- Highlighting in the render loop
- The "Selected: ..." text

All four are about **displaying and navigating a hand**. They're spread across `main()`, tangled with deck and button code.

That's our justification for creating a `HandView` class in Lesson 13. **We didn't invent the class in advance. The code told us it needed one.**

No new files this lesson.

## Putting it Together

Here is every file in the War app at the end of Lesson 12. Files marked **new** or **changed** were touched in this lesson; the rest are the same as last lesson.

### `src/main.cpp` (changed)

<!-- file: src/main.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
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

    int selectedCard = 0;
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
        selectedCard = 0;
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

        std::string selectedText = "No card selected";

        if (hand.size() > 0) {
            Card card(hand.getCard(selectedCard));
            selectedText = "Selected: " + card.toString();
        }

        Elements handElements;

        for (int i = 0; i < hand.size(); i++) {
            Card card(hand.getCard(i));

            auto element = renderCard(card);

            if (i == selectedCard) {
                element = element | bgcolor(Color::Blue);
            }

            handElements.push_back(element);

            handElements.push_back(
                text(" ")
            );
        }

        return vbox({
            text("GameOfWar 12") | bold | center,

            separator(),

            text("Cards remaining: " + std::to_string(deck.size())) | center,
            text("Cards in hand: " + std::to_string(hand.size())) | center,
            text("Selected position: " + std::to_string(selectedCard)) | center,
            text(selectedText) | center,

            separator(),

            text(cardText) | center,

            separator(),

            text("Your Hand") | bold | center,

            hbox(std::move(handElements)) | center,

            separator(),

            buttons->Render() | center,

        }) | border;
    });

    auto interactive = CatchEvent(renderer, [&](Event event) {
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
    });

    screen.Loop(interactive);
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
git commit -m "Lesson 12: keyboard selection"
```

### Next: Lesson 13 — Creating `HandView`

We'll move the selection state, keyboard handling, and hand rendering into a `HandView` class that **refers to** a `Hand` without owning it:

```text
┌───────────────────────────┐
│         HandView          │
│  Hand& hand  ─────────────┼──► the real Hand in main()
│  int selectedCard         │
│                           │
│  handleEvent()            │
│  render()                 │
└───────────────────────────┘
```
