# GameOfWar 13 — Creating a Reusable `HandView`

```yaml
course: 2143 - Object-Oriented Programming
project: GameOfWar
lesson: 13 - HandView
previous: Lesson 12 (src/main.cpp)
new_files:
  - include/HandView.hpp
  - src/HandView.cpp
concepts:
  - Refactoring toward a class
  - Reference members
  - Capturing [this] in a lambda
  - Composition vs inheritance
  - Headers without "using namespace"
```

At the end of Lesson 12, `main()` was juggling four things that all belong to **showing and navigating a hand**: the selection variable, the keyboard handler, the highlighting loop, and the "selected card" text.

Today we'll move them into a class, **one responsibility at a time, compiling after each move**. Then we'll give the class its own files.

This brings us back to the course's central question:

> Should we extend FTXUI's classes, or wrap them in our own?

We'll use **composition** (wrapping) and then discuss what inheritance would have bought us.

---

## Step 13.1 — An empty `HandView`

In `main.cpp`, add this class **between `renderCard()` and `main()`**. It will call `renderCard()` soon, so it must come after it.

```cpp
class HandView {
private:
    Hand& hand;
    int selectedCard = 0;

public:
    HandView(Hand& h) : hand(h) {
    }
};
```

Two data members:

- `hand` **refers to** an existing `Hand`. It doesn't own or copy it.
- `selectedCard` is the view's own state: which position is highlighted.

### Why a reference?

If we stored `Hand hand;`, the view would have its **own copy**. Drawing a card into `main()`'s hand wouldn't show up in the view's copy.

```text
     main()
       │ owns
       ▼
   ┌────────┐
   │  Hand  │ ◄──── reference ────  HandView
   └────────┘
```

Now, inside `main()`, right after creating the hand:

```cpp
Deck deck;
Hand hand;

HandView handView(hand);
```

Compile. Nothing changes yet.

---

## Step 13.2 — Move the selection state into the class

Add two public methods to `HandView`:

```cpp
int selectedIndex() const {
    return selectedCard;
}

void resetSelection() {
    selectedCard = 0;
}
```

Now **delete** `int selectedCard = 0;` from `main()`. The compiler will point at every place that used it. Fix each one:

| Where                          | Change to                                       |
| ------------------------------ | ----------------------------------------------- |
| Clear Hand callback            | `handView.resetSelection();`                    |
| Renderer: highlight loop       | `if (i == handView.selectedIndex())`            |
| Renderer: `selectedText` code  | `hand.getCard(handView.selectedIndex())`        |
| Renderer: "Selected position"  | `std::to_string(handView.selectedIndex())`      |
| `CatchEvent` handler           | Temporarily replace the whole body with `return false;` |

The event handler *changes* the selection, and nothing outside the class can do that anymore. That's the point of `private`. We'll move that logic into the class next.

Compile and run.

**Checkpoint:** Cards display, but the arrow keys temporarily do nothing. That's fine; we're refactoring one responsibility at a time.

---

## Step 13.3 — Move keyboard handling into the class

Add this method to `HandView`. It's the logic from Lesson 12, now inside the class:

```cpp
bool handleEvent(Event event) {
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
```

It returns `bool` for the same reason as before: `true` means "handled".

In `main()`, make the `CatchEvent` handler forward to it:

```cpp
auto interactive = CatchEvent(renderer, [&](Event event) {
    return handView.handleEvent(event);
});
```

Compile and run.

**Checkpoint:** Arrow keys work again, but `main()` no longer knows *how* selection works. It just forwards events. That's **encapsulation**.

---

## Step 13.4 — Move hand rendering into the class

`renderCard()` stays a free function. It has one job: draw **one** card. `HandView` will use it to draw a **whole hand**.

Add to `HandView`:

```cpp
Element render() const {
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
```

`render()` is `const` because drawing shouldn't change the view.

In `main()`'s renderer, **delete** the `Elements handElements;` loop, and replace:

```cpp
hbox(std::move(handElements)) | center,
```

with:

```cpp
handView.render() | center,
```

Compile and run. **Checkpoint:** Cards display and highlight exactly as before.

---

## Step 13.5 — Move the selected-card description

Add to `HandView`:

```cpp
std::string selectedCardName() const {
    if (hand.size() == 0) {
        return "No card selected";
    }

    Card card(hand.getCard(selectedCard));

    return card.toString();
}
```

In the renderer, **delete** the `selectedText` block and replace `text(selectedText)` with:

```cpp
text(handView.selectedCardName()) | center,
```

Compile and run.

---

## Step 13.6 — Let `HandView` attach its own event handler

`main()` still builds the `CatchEvent` wrapper. Let the view do it.

Add to `HandView`:

```cpp
Component attach(Component child) {
    return CatchEvent(child, [this](Event event) {
        return handleEvent(event);
    });
}
```

In `main()`, replace the whole `CatchEvent(...)` block with:

```cpp
auto interactive = handView.attach(renderer);
```

Compile and run.

### Why `[this]`?

The lambda lives inside a member function and needs to call `handleEvent()` on **this particular** `HandView`. Capturing `this` gives it a pointer to the object.

**Lifetime rule:** the `HandView` must stay alive as long as FTXUI might call the lambda. In `main()` that's guaranteed: `handView` lives until `screen.Loop()` returns.

---

## Step 13.7 — Give `HandView` its own files

The class works. Now let's move it out of `main.cpp`, just like `Card`, `Deck`, and `Hand`.

### One rule for headers: no `using namespace`

A header is pasted into every file that includes it. If `HandView.hpp` said `using namespace ftxui;`, every one of those files would get all of FTXUI's names dumped into it, whether they wanted them or not.

So in the header we write the full names: `ftxui::Element`, `ftxui::Event`, `ftxui::Component`. In the `.cpp` file, `using namespace ftxui;` is fine.

### Create `include/HandView.hpp`

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
    Hand& hand;
    int selectedCard = 0;

public:
    HandView(Hand& h);

    int selectedIndex() const;
    void resetSelection();

    bool handleEvent(ftxui::Event event);

    ftxui::Element render() const;

    std::string selectedCardName() const;

    ftxui::Component attach(ftxui::Component child);
};
```

### Create `src/HandView.cpp`

Move `shortRank()`, `suitSymbol()`, and `renderCard()` here from `main.cpp`, along with the method bodies:

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

HandView::HandView(Hand& h) : hand(h) {
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

**What's `namespace { ... }`?** An *unnamed namespace*. `shortRank()` and `suitSymbol()` are helpers that only this file needs. Putting them in an unnamed namespace makes them **private to this `.cpp` file**. No other file can see or accidentally collide with them.

### Update `main.cpp` and CMake

In `main.cpp`:

1. **Delete** `shortRank()`, `suitSymbol()`, `renderCard()`, and `class HandView`.
2. Add `#include "HandView.hpp"`.
3. You can remove `#include <vector>` and `#include <ftxui/component/event.hpp>`; `main.cpp` no longer uses them directly.

In `CMakeLists.txt`:

```cmake
add_executable(war
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Hand.cpp
    src/HandView.cpp
)
```

Compile and run:

```bash
cmake -S . -B build
cmake --build build --target war
./build/war
```

**Checkpoint:** Same behavior. `main.cpp` is now about half its Lesson 12 size.

---

## Step 13.8 — What did composition buy us?

`HandView` **uses** FTXUI (it builds a `CatchEvent` component and returns `Element`s), but it doesn't **inherit** from anything.

### What about inheritance?

FTXUI does support custom components through inheritance:

```cpp
class HandView : public ftxui::ComponentBase {
public:
    bool OnEvent(ftxui::Event event) override;
    ftxui::Element OnRender() override;
};
```

That's a legitimate design. It makes `HandView` *be* an FTXUI component. It could then sit inside a `Container`, receive focus like a button, and handle arrow keys **only when focused**.

That last point is a real limitation of our version: `attach()` wraps the *whole* interface, so `HandView` grabs Left/Right no matter what has focus. For this app that's fine. For a screen with several hands, inheritance (or FTXUI's focus tools) would be worth the extra complexity.

| Approach                     | Says…                                  | Good when…                                  |
| ---------------------------- | -------------------------------------- | ------------------------------------------- |
| Composition (what we did)    | "HandView **uses** FTXUI components"   | You just need to assemble existing pieces   |
| Inheritance from ComponentBase | "HandView **is** an FTXUI component" | You need custom focus/event behavior        |

**Start with composition. Reach for inheritance when you have a concrete need it solves.**

---

## Step 13.9 — Student challenge

Add a method to `HandView`:

```cpp
int selectedCardId() const;
```

- Return the ID of the selected card, or `-1` when the hand is empty.
- Don't expose the hand's vector.

**Bonus:** Add Home and End support inside `HandView::handleEvent()`. **`main.cpp` should not need to change at all.** That's what encapsulating the selection behavior buys us.

---

## Project structure after Lesson 13

```text
GameOfWar/
├── CMakeLists.txt
├── examples/          (Lessons 01–07)
├── include/
│   ├── Card.hpp
│   ├── Deck.hpp
│   ├── Hand.hpp
│   └── HandView.hpp
└── src/
    ├── main.cpp
    ├── Card.cpp
    ├── Deck.cpp
    ├── Hand.cpp
    └── HandView.cpp
```

| Class / function | Responsibility                       |
| ---------------- | ------------------------------------ |
| `Card`           | Represent a playing card             |
| `Deck`           | Manage available cards               |
| `Hand`           | Store cards                          |
| `renderCard()`   | Draw one card                        |
| `HandView`       | Display a hand and manage selection  |
| `main()`         | Create objects and wire them together |

We **refactored toward** an abstraction instead of inventing one up front: messy code first, then a class once the shape was obvious.

## Putting it Together

Here is every file in the War app at the end of Lesson 13. Files marked **new** or **changed** were touched in this lesson; the rest are the same as last lesson.

### `src/main.cpp` (changed)

<!-- file: src/main.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

#include "Card.hpp"
#include "Deck.hpp"
#include "Hand.hpp"
#include "HandView.hpp"

using namespace ftxui;

int main() {

    Deck deck;
    Hand hand;

    HandView handView(hand);

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
        handView.resetSelection();
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

        return vbox({
            text("GameOfWar 13") | bold | center,

            separator(),

            text("Cards remaining: " + std::to_string(deck.size())) | center,
            text("Cards in hand: " + std::to_string(hand.size())) | center,
            text("Selected position: " + std::to_string(handView.selectedIndex())) | center,
            text(handView.selectedCardName()) | center,

            separator(),

            text(cardText) | center,

            separator(),

            text("Your Hand") | bold | center,

            handView.render() | center,

            separator(),

            buttons->Render() | center,

        }) | border;
    });

    auto interactive = handView.attach(renderer);

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

<details>
<summary><code>include/HandView.hpp</code> (new)</summary>

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
    Hand& hand;
    int selectedCard = 0;

public:
    HandView(Hand& h);

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
<summary><code>src/HandView.cpp</code> (new)</summary>

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

HandView::HandView(Hand& h) : hand(h) {
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

> **Linker errors?** Make sure `src/HandView.cpp` is listed in `add_executable(war ...)` in `CMakeLists.txt`.

---

## Commit your work

```bash
git add .
git commit -m "Lesson 13: HandView class"
```

### Next: Lesson 14 — Introducing `Player`

A player has a name and a hand. Should `Player` *contain* a `Hand`, or *refer to* one? And should it ever *inherit* from `Hand`? We'll answer those questions, then deal cards to two players.
