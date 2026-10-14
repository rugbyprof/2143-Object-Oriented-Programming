# TinyChunks 15 — Implementing the Rules of War

```yaml
course: 2143 - Object-Oriented Programming
project: tinychunks
lesson: 15 - Game of War
previous: Lesson 14
new_files:
  - include/WarGame.hpp
  - src/WarGame.cpp
changed_files:
  - include/Hand.hpp, src/Hand.cpp
  - include/Player.hpp, src/Player.cpp
  - src/main.cpp
concepts:
  - Where do rules belong?
  - A class that coordinates other objects
  - Returning a struct of results
  - Local vs member state
  - Invariants
```

Today our classes actually play War.

The interesting OOP question is:

> Should the rules of War belong to `Player`, `Deck`, or a new class?

We'll answer it by listing the jobs that need doing, and noticing that none of our existing classes should do them.

## Step 15.1 — Our rules

War has many variations. We'll use these:

1. Shuffle a 52-card deck and deal 26 cards to each player.
2. Both players reveal their next card.
3. The higher **rank** wins both cards. Suits don't matter.
4. Equal ranks trigger a **war**: each player places three cards face down, then one more face up. The higher face-up card wins **everything** played this round.
5. If the face-up cards tie again, repeat the war.
6. A player who runs out of cards loses.

One complication: in our encoding, the Ace has rank index **0**, the lowest. In War, the **Ace is the highest card**. We'll handle that without changing `Card`.

---

## Step 15.2 — Let a hand give up a card

Open `include/Hand.hpp` and add:

```cpp
int removeCard();
```

In `src/Hand.cpp`:

```cpp
int Hand::removeCard() {
    if (cards.empty()) {
        return -1;
    }

    int id = cards.front();
    cards.erase(cards.begin());

    return id;
}
```

We remove from the **front**, not the back. In War a player's cards behave like a **queue**: you play from the top and put won cards on the bottom.

```text
FRONT (play from here)            BACK (won cards go here)
  │                                  │
  ▼                                  ▼
[ 12 ][ 43 ][ 7 ][ 51 ][ 26 ][ 8 ]
```

`erase(begin())` shifts every remaining element, which is fine for 52 cards. `std::deque` is built for fast removal at the front. Look it up if you're curious.

### Let a player play a card

In `include/Player.hpp`:

```cpp
int playCard();
```

In `src/Player.cpp`:

```cpp
int Player::playCard() {
    return hand.removeCard();
}
```

Delegation again: `Player` doesn't know how `Hand` stores cards.

Compile:

```bash
cmake --build build --target war
```

---

## Step 15.3 — Where should the rules live?

The game needs someone to:

- Own the deck and both players.
- Shuffle and deal.
- Play a round: take a card from each player and compare them.
- Handle ties (wars).
- Give the won cards to the winner.
- Decide when the game is over.

**Is that `Player`'s job?** No. A player shouldn't know about the other player or the deck.

**Is it `Deck`'s job?** No. A deck is just cards.

**Is it `main()`'s job?** It could be, but then our game rules would be tangled up with FTXUI buttons, and we couldn't reuse or test them without a UI.

So the rules get their own class: **`WarGame`**. It knows the rules and coordinates the other objects. It knows **nothing** about FTXUI.

### The Ace problem

Our rank indices run Ace=0, 2=1, …, King=12. For War, we want 2=2 … King=13, Ace=14. A tiny function does it:

```cpp
int warValue(int cardId) {
    int rank = cardId % 13;
    return rank == 0 ? 14 : rank + 1;
}
```

| Card ID | Card            | `warValue` |
| ------- | --------------- | ---------- |
| 0       | Ace of Clubs    | 14         |
| 12      | King of Clubs   | 13         |
| 13      | Ace of Diamonds | 14         |
| 14      | 2 of Diamonds   | 2          |

**Why not add `warValue()` to `Card`?** Because "Ace is high" is a rule of **War**, not a fact about cards. In Blackjack an Ace is 1 or 11. Putting game rules in `Card` would tie a general-purpose class to one game. So `warValue()` will live in `WarGame.cpp`.

---

## Step 15.4 — Create `WarGame`

Create `include/WarGame.hpp`:

```cpp
#pragma once

#include "Deck.hpp"
#include "Player.hpp"

class WarGame {
private:
    Deck deck;
    Player player1;
    Player player2;

public:
    WarGame();

    void deal();

    const Player& getPlayer1() const;
    const Player& getPlayer2() const;
};
```

`WarGame` **owns** the deck and both players (composition again):

```text
┌───────────────────────────┐
│          WarGame          │
│   Deck    deck            │
│   Player  player1 ─► Hand │
│   Player  player2 ─► Hand │
└───────────────────────────┘
```

Create `src/WarGame.cpp`:

```cpp
#include "WarGame.hpp"

WarGame::WarGame()
    : player1("Alice"), player2("Bob") {
}

const Player& WarGame::getPlayer1() const {
    return player1;
}

const Player& WarGame::getPlayer2() const {
    return player2;
}

void WarGame::deal() {
    deck.shuffle();

    for (int i = 0; i < 26; i++) {
        player1.receiveCard(deck.draw());
        player2.receiveCard(deck.draw());
    }
}
```

**Why must `player1` and `player2` be in the initialization list?** `Player` has no default constructor. It *requires* a name. The only place to pass constructor arguments to a member is the initialization list. (`deck` uses its default constructor, so it doesn't need to be listed.)

The getters return `const Player&`, so the UI can *read* players but can't make them play cards behind the game's back.

> `deal()` should be called once per `WarGame` for now. We'll add a proper restart in Lesson 16.

Add `src/WarGame.cpp` to `CMakeLists.txt`:

```cmake
add_executable(war
    src/main.cpp
    src/Card.cpp
    src/Deck.cpp
    src/Hand.cpp
    src/HandView.cpp
    src/Player.cpp
    src/WarGame.cpp
)
```

Compile.

---

## Step 15.5 — Show the game

In `main.cpp`, add:

```cpp
#include "WarGame.hpp"
```

Replace the whole body of `main()`:

```cpp
int main() {

    WarGame game;
    game.deal();

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        return vbox({
            text("TinyChunks 15 - War") | bold | center,

            separator(),

            text(game.getPlayer1().getName() + ": " + std::to_string(game.getPlayer1().cardCount())),
            text(game.getPlayer2().getName() + ": " + std::to_string(game.getPlayer2().cardCount())),

        }) | border;
    });

    screen.Loop(renderer);
}
```

Compile and run:

```text
┌────────────────────────┐
│  TinyChunks 15 - War   │
├────────────────────────┤
│Alice: 26               │
│Bob: 26                 │
└────────────────────────┘
```

`main()` didn't create a deck or deal a single card. It asked the game to.

---

## Step 15.6 — Play one simple round

A round produces several pieces of information: which two cards were played, and who won. Rather than four separate getters, we'll return them **together** in a small struct.

In `WarGame.hpp`, **above** the class:

```cpp
struct RoundResult {
    int card1 = -1;
    int card2 = -1;
    int winner = 0;     // 0 = nobody, 1 = player 1, 2 = player 2
};
```

Inside the class, under `public:`:

```cpp
RoundResult playRound();
```

In `WarGame.cpp`, add `warValue()` **near the top**, wrapped in an unnamed namespace (Lesson 13) so it's private to this file:

```cpp
namespace {

int warValue(int cardId) {
    int rank = cardId % 13;
    return rank == 0 ? 14 : rank + 1;
}

}
```

Then implement a simple round with **no war yet**:

```cpp
RoundResult WarGame::playRound() {
    RoundResult result;

    if (player1.cardCount() == 0 || player2.cardCount() == 0) {
        return result;
    }

    result.card1 = player1.playCard();
    result.card2 = player2.playCard();

    int value1 = warValue(result.card1);
    int value2 = warValue(result.card2);

    if (value1 > value2) {
        result.winner = 1;

        player1.receiveCard(result.card1);
        player1.receiveCard(result.card2);
    }
    else if (value2 > value1) {
        result.winner = 2;

        player2.receiveCard(result.card1);
        player2.receiveCard(result.card2);
    }

    return result;
}
```

### Add a Play Round button

In `main()`, right after `game.deal();`:

```cpp
RoundResult lastRound;
```

After the screen:

```cpp
auto playButton = Button("Play Round", [&] {
    lastRound = game.playRound();
});
```

Update the renderer. We'll also display the **total** number of cards the players hold:

```cpp
auto renderer = Renderer(playButton, [&] {

    std::string winnerText = "Ready to play";

    if (lastRound.winner == 1) {
        winnerText = game.getPlayer1().getName() + " wins the round!";
    }
    else if (lastRound.winner == 2) {
        winnerText = game.getPlayer2().getName() + " wins the round!";
    }

    int total = game.getPlayer1().cardCount() + game.getPlayer2().cardCount();

    return vbox({
        text("TinyChunks 15 - War") | bold | center,

        separator(),

        text(game.getPlayer1().getName() + ": " + std::to_string(game.getPlayer1().cardCount())),
        text(game.getPlayer2().getName() + ": " + std::to_string(game.getPlayer2().cardCount())),
        text("Total: " + std::to_string(total)),

        separator(),

        text(winnerText) | center,

        playButton->Render() | center,

    }) | border;
});
```

Compile and run. Click **Play Round** many times and **watch the Total**.

**Question:** The total should always be 52. Is it? When does it change?

When both cards have the same rank, `winner` stays `0`, nobody receives the cards, and **two cards vanish from the game**. That's a bug.

---

## Step 15.7 — Wars: collect a pot

The total "should always be 52" is an **invariant**. Our code just broke it. Let's fix it properly.

During a round, especially a war, many cards can be on the table. We'll collect every played card in a **pot**, and when someone finally wins, they take the whole pot.

First, add one more field to `RoundResult`:

```cpp
struct RoundResult {
    int card1 = -1;
    int card2 = -1;
    int winner = 0;     // 0 = nobody, 1 = player 1, 2 = player 2
    int cardsPlayed = 0;
};
```

At the top of `WarGame.cpp`:

```cpp
#include <vector>
```

Now **replace** `playRound()` with the full version:

```cpp
RoundResult WarGame::playRound() {
    RoundResult result;

    if (player1.cardCount() == 0 || player2.cardCount() == 0) {
        return result;
    }

    std::vector<int> pot;

    while (true) {
        result.card1 = player1.playCard();
        result.card2 = player2.playCard();

        pot.push_back(result.card1);
        pot.push_back(result.card2);

        int value1 = warValue(result.card1);
        int value2 = warValue(result.card2);

        if (value1 > value2) {
            result.winner = 1;
            break;
        }

        if (value2 > value1) {
            result.winner = 2;
            break;
        }

        // Tie: each player places up to three cards face down,
        // then the loop compares another face-up card.
        for (int i = 0; i < 3; i++) {
            if (player1.cardCount() > 0) {
                pot.push_back(player1.playCard());
            }

            if (player2.cardCount() > 0) {
                pot.push_back(player2.playCard());
            }
        }

        // A player with no cards left can't continue the war.
        if (player1.cardCount() == 0 && player2.cardCount() == 0) {
            break;
        }

        if (player1.cardCount() == 0) {
            result.winner = 2;
            break;
        }

        if (player2.cardCount() == 0) {
            result.winner = 1;
            break;
        }
    }

    result.cardsPlayed = static_cast<int>(pot.size());

    if (result.winner == 1) {
        for (int id : pot) {
            player1.receiveCard(id);
        }
    }
    else if (result.winner == 2) {
        for (int id : pot) {
            player2.receiveCard(id);
        }
    }

    return result;
}
```

Walk through it:

```text
Alice plays 8    Bob plays 8      → tie!
  3 face down      3 face down
Alice plays K    Bob plays K      → tie again! loop repeats
  3 face down      3 face down
Alice plays 4    Bob plays J      → Bob wins all 20 cards in the pot
```

- The `while (true)` loop keeps going through as many wars as it takes.
- Each `break` ends the round with a decision.
- If a player runs out mid-war, they lose the pot. (If **both** run out at the same instant, nobody wins it. That's a rare edge case we'll handle in Lesson 16.)

### Why is `pot` a local variable?

The pot only exists while one round is being resolved. Nothing needs it between rounds, so it doesn't belong as a member of `WarGame`. **Keep state as local as you can.**

### Show unresolved ties

In `main.cpp`'s renderer, extend the winner text:

```cpp
else if (lastRound.cardsPlayed > 0) {
    winnerText = "Unresolved tie";
}
```

Compile and run. Click **Play Round** many times. The **Total stays at 52**, and sometimes a single click moves a big pile of cards from one player to the other. That was a war.

---

## Checkpoint: complete files

<details>
<summary><code>include/WarGame.hpp</code></summary>

<!-- checkpoint: WarGame.hpp -->
```cpp
#pragma once

#include "Deck.hpp"
#include "Player.hpp"

struct RoundResult {
    int card1 = -1;
    int card2 = -1;
    int winner = 0;     // 0 = nobody, 1 = player 1, 2 = player 2
    int cardsPlayed = 0;
};

class WarGame {
private:
    Deck deck;
    Player player1;
    Player player2;

public:
    WarGame();

    void deal();

    RoundResult playRound();

    const Player& getPlayer1() const;
    const Player& getPlayer2() const;
};
```

</details>

<details>
<summary><code>src/WarGame.cpp</code></summary>

<!-- checkpoint: WarGame.cpp -->
```cpp
#include "WarGame.hpp"

#include <vector>

namespace {

int warValue(int cardId) {
    int rank = cardId % 13;
    return rank == 0 ? 14 : rank + 1;
}

}

WarGame::WarGame()
    : player1("Alice"), player2("Bob") {
}

const Player& WarGame::getPlayer1() const {
    return player1;
}

const Player& WarGame::getPlayer2() const {
    return player2;
}

void WarGame::deal() {
    deck.shuffle();

    for (int i = 0; i < 26; i++) {
        player1.receiveCard(deck.draw());
        player2.receiveCard(deck.draw());
    }
}

RoundResult WarGame::playRound() {
    RoundResult result;

    if (player1.cardCount() == 0 || player2.cardCount() == 0) {
        return result;
    }

    std::vector<int> pot;

    while (true) {
        result.card1 = player1.playCard();
        result.card2 = player2.playCard();

        pot.push_back(result.card1);
        pot.push_back(result.card2);

        int value1 = warValue(result.card1);
        int value2 = warValue(result.card2);

        if (value1 > value2) {
            result.winner = 1;
            break;
        }

        if (value2 > value1) {
            result.winner = 2;
            break;
        }

        // Tie: each player places up to three cards face down,
        // then the loop compares another face-up card.
        for (int i = 0; i < 3; i++) {
            if (player1.cardCount() > 0) {
                pot.push_back(player1.playCard());
            }

            if (player2.cardCount() > 0) {
                pot.push_back(player2.playCard());
            }
        }

        // A player with no cards left can't continue the war.
        if (player1.cardCount() == 0 && player2.cardCount() == 0) {
            break;
        }

        if (player1.cardCount() == 0) {
            result.winner = 2;
            break;
        }

        if (player2.cardCount() == 0) {
            result.winner = 1;
            break;
        }
    }

    result.cardsPlayed = static_cast<int>(pot.size());

    if (result.winner == 1) {
        for (int id : pot) {
            player1.receiveCard(id);
        }
    }
    else if (result.winner == 2) {
        for (int id : pot) {
            player2.receiveCard(id);
        }
    }

    return result;
}
```

</details>

<details>
<summary><code>src/main.cpp</code></summary>

<!-- checkpoint: main.cpp -->
```cpp
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

#include "WarGame.hpp"

using namespace ftxui;

int main() {

    WarGame game;
    game.deal();

    RoundResult lastRound;

    auto screen = ScreenInteractive::TerminalOutput();

    auto playButton = Button("Play Round", [&] {
        lastRound = game.playRound();
    });

    auto renderer = Renderer(playButton, [&] {

        std::string winnerText = "Ready to play";

        if (lastRound.winner == 1) {
            winnerText = game.getPlayer1().getName() + " wins the round!";
        }
        else if (lastRound.winner == 2) {
            winnerText = game.getPlayer2().getName() + " wins the round!";
        }
        else if (lastRound.cardsPlayed > 0) {
            winnerText = "Unresolved tie";
        }

        int total = game.getPlayer1().cardCount() + game.getPlayer2().cardCount();

        return vbox({
            text("TinyChunks 15 - War") | bold | center,

            separator(),

            text(game.getPlayer1().getName() + ": " + std::to_string(game.getPlayer1().cardCount())),
            text(game.getPlayer2().getName() + ": " + std::to_string(game.getPlayer2().cardCount())),
            text("Total: " + std::to_string(total)),

            separator(),

            text(winnerText) | center,

            playButton->Render() | center,

        }) | border;
    });

    screen.Loop(renderer);
}
```

</details>

---

## Step 15.8 — Student challenge

Add to `WarGame`:

```cpp
bool isGameOver() const;
std::string winnerName() const;
```

- `isGameOver()` returns `true` when either player has no cards. Don't add a `bool gameOver` member; compute it from `cardCount()`.
- `winnerName()` returns the winner's name once the game is over.
- Don't expose the players' hands.

Use them in `main()` to show **"Game Over: Alice"** and stop playing rounds.

Lesson 16 starts with our version of these methods, so compare yours.

---

## Is `WarGame` a Facade?

Look at how little `main()` needs to know:

```cpp
game.deal();
game.playRound();
game.getPlayer1().cardCount();
```

`main()` never touches the deck, a hand, or a card ID comparison. `WarGame` hides all of that behind a few simple calls. That's **facade-like**.

But a textbook **Facade** mostly *simplifies access* to an existing subsystem without adding logic of its own. `WarGame` does more than that: it **owns the rules and the game state**. A more precise name for it is a **game model** or **controller**.

Not every class that simplifies an interface is a Facade, and that's OK. The name matters less than the separation: **the rules live in one class that has no idea FTXUI exists.**

---

## Project structure after Lesson 15

```text
tinychunks/
├── CMakeLists.txt
├── examples/          (Lessons 01–07)
├── include/
│   ├── Card.hpp
│   ├── Deck.hpp
│   ├── Hand.hpp
│   ├── HandView.hpp
│   ├── Player.hpp
│   └── WarGame.hpp
└── src/
    ├── main.cpp
    ├── Card.cpp
    ├── Deck.cpp
    ├── Hand.cpp
    ├── HandView.cpp
    ├── Player.cpp
    └── WarGame.cpp
```

This is the final set of classes. Lesson 16 finishes the game without adding any more.

## Commit your work

```bash
git add .
git commit -m "Lesson 15: WarGame rules"
```

### Next: Lesson 16 — Finishing War

We'll handle game over and restarts, show the played cards with `renderCard()`, fix a sneaky bug where some games **never end**, and test the whole thing.
