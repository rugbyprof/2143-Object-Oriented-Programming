# TinyChunks 16 — Finishing the Game of War

```yaml
course: 2143 - Object-Oriented Programming
project: tinychunks
lesson: 16 - Completing War
previous: Lesson 15
changed_files:
  - include/WarGame.hpp
  - src/WarGame.cpp
  - src/main.cpp
concepts:
  - Game state (not started / playing / over)
  - Edge cases
  - Value semantics and reset
  - Testing with invariants
  - Separation of model and UI
```

**Final lesson!** We started with a single box. Now we have five classes, a reusable view, and a game engine that knows nothing about the terminal.

Today we finish the application **without adding another class**:

1. Track whether the game is over (and who won).
2. Handle the rare "both players run out" case.
3. Add a New Game operation.
4. Fix games that **never end**.
5. Build the final interface with real card graphics.
6. Test it.

**Compile after each step.**

---

## Step 16.1 — Track game status

If you did the Lesson 15 challenge, compare your version with this one.

In `WarGame.hpp`, add `#include <string>` at the top, then add three **private** members:

```cpp
bool started = false;
bool finished = false;
bool draw = false;
```

and three **public** methods:

```cpp
bool isGameOver() const;
bool isDraw() const;
std::string winnerName() const;
```

Why `started`? Before `deal()`, both players have zero cards. Without `started`, a brand-new game would look like it was already over.

At the end of `deal()`, add:

```cpp
started = true;
```

Implement in `WarGame.cpp`:

```cpp
bool WarGame::isGameOver() const {
    if (!started) {
        return false;
    }

    return finished ||
           player1.cardCount() == 0 ||
           player2.cardCount() == 0;
}

bool WarGame::isDraw() const {
    return finished && draw;
}

std::string WarGame::winnerName() const {
    if (!isGameOver()) {
        return "";
    }

    if (isDraw()) {
        return "Draw";
    }

    if (player2.cardCount() == 0) {
        return player1.getName();
    }

    return player2.getName();
}
```

Finally, replace the first check in `playRound()`:

```cpp
if (player1.cardCount() == 0 || player2.cardCount() == 0) {
    return result;
}
```

with:

```cpp
if (!started || isGameOver()) {
    return result;
}
```

Compile:

```bash
cmake --build build --target war
```

The game can now tell the difference between **not started**, **playing**, and **over**.

---

## Step 16.2 — Both players run out at once

Look at this part of the war loop from Lesson 15:

```cpp
if (player1.cardCount() == 0 && player2.cardCount() == 0) {
    break;
}
```

If both players use their last cards in the same war, the loop ends with `winner == 0`. Nobody gets the pot, both players have zero cards, and the game is stuck in limbo.

We need a rule. Ours: **if neither player can continue a war, the game ends in a draw.**

Replace the three "can't continue" checks at the bottom of the loop with:

```cpp
bool p1CanContinue = player1.cardCount() > 0;
bool p2CanContinue = player2.cardCount() > 0;

if (!p1CanContinue && !p2CanContinue) {
    finished = true;
    draw = true;
    break;
}

if (!p1CanContinue) {
    result.winner = 2;
    break;
}

if (!p2CanContinue) {
    result.winner = 1;
    break;
}
```

Naming the conditions (`p1CanContinue`) makes the rule easier to read than three raw `cardCount()` checks.

**This is a simplified rule.** A stricter War variant requires four cards to go to war. Either rule is fine, as long as it's documented and applied consistently.

---

## Step 16.3 — Record whether a war happened

The UI should be able to say "WAR!". Add one field to `RoundResult`:

```cpp
bool wasWar = false;
```

In `playRound()`, right after the comment `// Tie: ...` (when we know the ranks were equal), add:

```cpp
result.wasWar = true;
```

This is why returning a struct was a good idea: adding new information didn't change `playRound()`'s signature or any code that calls it.

---

## Step 16.4 — New Game

In `WarGame.hpp`:

```cpp
void reset();
```

In `WarGame.cpp`:

```cpp
void WarGame::reset() {
    deck = Deck();

    player1 = Player("Alice");
    player2 = Player("Bob");

    started = false;
    finished = false;
    draw = false;

    deal();
}
```

`deck = Deck();` builds a brand-new full deck and **assigns** it over the old one. The same goes for the players.

This works because all our classes hold ordinary value members (`int`, `std::string`, `std::vector`). The compiler-generated assignment operator copies them member by member. **We didn't write any copy code at all.**

Notice that `player1` is still the *same object at the same address*. Only its contents changed. Any `const Player&` someone got from `getPlayer1()` still refers to the current player 1.

---

## Step 16.5 — Games that never end

Here's a bug you'd probably never notice by clicking: **some games of War never finish.**

We found it by writing a small test that played 10,000 games automatically with our Lesson 15 code. About **1 game in 9** was still going after 10,000 rounds.

**Why?** Our game has no randomness after the initial shuffle. Winners always put the pot on the bottom in the same order. With some starting deals, the cards fall into a **cycle**: after enough rounds, both hands return to an arrangement they've had before, and the game repeats forever.

The fix is small. Shuffle the pot before the winner collects it. Real players don't pick up cards in a perfectly predictable order either.

At the top of `WarGame.cpp`:

```cpp
#include <algorithm>
#include <random>
```

In `playRound()`, right after `result.cardsPlayed = ...`:

```cpp
// Without this, the same card order can repeat forever.
static std::mt19937 rng(std::random_device{}());
std::shuffle(pot.begin(), pot.end(), rng);
```

After this fix, a test of 20,000 games had **every game finish**, averaging about 240 rounds.

**Lesson:** "it worked when I tried it" is not testing. Some bugs only appear after thousands of runs. Because `WarGame` doesn't depend on FTXUI, we could test it with a plain loop in a few lines.

Compile:

```bash
cmake --build build --target war
```

---

## Checkpoint: the finished model

<details>
<summary><code>include/WarGame.hpp</code></summary>

<!-- checkpoint: WarGame.hpp -->
```cpp
#pragma once

#include <string>

#include "Deck.hpp"
#include "Player.hpp"

struct RoundResult {
    int card1 = -1;
    int card2 = -1;
    int winner = 0;
    int cardsPlayed = 0;
    bool wasWar = false;
};

class WarGame {
private:
    Deck deck;
    Player player1;
    Player player2;

    bool started = false;
    bool finished = false;
    bool draw = false;

public:
    WarGame();

    void deal();
    void reset();

    RoundResult playRound();

    bool isGameOver() const;
    bool isDraw() const;
    std::string winnerName() const;

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

#include <algorithm>
#include <random>
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

    started = true;
}

void WarGame::reset() {
    deck = Deck();

    player1 = Player("Alice");
    player2 = Player("Bob");

    started = false;
    finished = false;
    draw = false;

    deal();
}

bool WarGame::isGameOver() const {
    if (!started) {
        return false;
    }

    return finished ||
           player1.cardCount() == 0 ||
           player2.cardCount() == 0;
}

bool WarGame::isDraw() const {
    return finished && draw;
}

std::string WarGame::winnerName() const {
    if (!isGameOver()) {
        return "";
    }

    if (isDraw()) {
        return "Draw";
    }

    if (player2.cardCount() == 0) {
        return player1.getName();
    }

    return player2.getName();
}

RoundResult WarGame::playRound() {
    RoundResult result;

    if (!started || isGameOver()) {
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
        result.wasWar = true;

        for (int i = 0; i < 3; i++) {
            if (player1.cardCount() > 0) {
                pot.push_back(player1.playCard());
            }

            if (player2.cardCount() > 0) {
                pot.push_back(player2.playCard());
            }
        }

        bool p1CanContinue = player1.cardCount() > 0;
        bool p2CanContinue = player2.cardCount() > 0;

        if (!p1CanContinue && !p2CanContinue) {
            finished = true;
            draw = true;
            break;
        }

        if (!p1CanContinue) {
            result.winner = 2;
            break;
        }

        if (!p2CanContinue) {
            result.winner = 1;
            break;
        }
    }

    result.cardsPlayed = static_cast<int>(pot.size());

    // Without this, the same card order can repeat forever.
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(pot.begin(), pot.end(), rng);

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

---

## Step 16.6 — Show the played cards

Now we switch to `main.cpp`.

We already have `renderCard()` in `HandView.hpp`. **Reuse it.** In `main.cpp`, add:

```cpp
#include "Card.hpp"
#include "HandView.hpp"
```

Add this helper above `main()`:

```cpp
Element renderPlayedCard(int cardId) {
    if (cardId < 0) {
        return text("No card");
    }

    return renderCard(Card(cardId));
}
```

Before the first round, `lastRound.card1` is `-1`. This helper shows "No card" instead of quietly turning `-1` into the Ace of Clubs.

---

## Step 16.7 — Buttons

In `main()`, change:

```cpp
WarGame game;
game.deal();
```

to:

```cpp
WarGame game;
game.reset();
```

Then replace the single Play button with three buttons and a container:

```cpp
auto playButton = Button("Play Round", [&] {
    if (!game.isGameOver()) {
        lastRound = game.playRound();
    }
});

auto newGameButton = Button("New Game", [&] {
    game.reset();
    lastRound = RoundResult{};
});

auto quitButton = Button("Quit", [&] {
    screen.Exit();
});

auto buttons = Container::Horizontal({
    playButton,
    newGameButton,
    quitButton,
});
```

`RoundResult{}` creates a fresh result with all the default values (`-1`, `0`, `false`), which clears the display.

`screen.Exit()` ends `screen.Loop()`. No more Ctrl+C.

---

## Step 16.8 — The final renderer

Replace the renderer. Notice how it reads: it only **asks** the game questions and **draws** the answers. No rules live here.

```cpp
auto renderer = Renderer(buttons, [&] {

    std::string status = "Ready to play";

    if (game.isGameOver()) {
        status = "Game Over: " + game.winnerName();
    }
    else if (lastRound.winner == 1) {
        status = game.getPlayer1().getName() + " wins the round!";
    }
    else if (lastRound.winner == 2) {
        status = game.getPlayer2().getName() + " wins the round!";
    }

    if (lastRound.wasWar) {
        status += " (WAR!)";
    }

    auto player1Display = vbox({
        text(game.getPlayer1().getName()) | bold | center,
        text("Cards: " + std::to_string(game.getPlayer1().cardCount())) | center,
        renderPlayedCard(lastRound.card1) | center,
    }) | border;

    auto player2Display = vbox({
        text(game.getPlayer2().getName()) | bold | center,
        text("Cards: " + std::to_string(game.getPlayer2().cardCount())) | center,
        renderPlayedCard(lastRound.card2) | center,
    }) | border;

    return vbox({
        text("TINYCHUNKS - WAR") | bold | center,

        separator(),

        hbox({
            player1Display,
            text("   VS   ") | vcenter,
            player2Display,
        }) | center,

        separator(),

        text(status) | center,

        separator(),

        buttons->Render() | center,

    }) | border;
});
```

Compile and run:

```bash
cmake --build build --target war
./build/war
```

```text
┌─────────────────────────────────────────────┐
│               TINYCHUNKS - WAR              │
├─────────────────────────────────────────────┤
│        ┌─────────────┐       ┌─────────────┐│
│        │    Alice    │       │     Bob     ││
│        │  Cards: 27  │       │  Cards: 25  ││
│        │  ┌───────┐  │       │  ┌───────┐  ││
│        │  │K      │  │       │  │8      │  ││
│        │  │       │  │  VS   │  │       │  ││
│        │  │   ♠   │  │       │  │   ♥   │  ││
│        │  │       │  │       │  │       │  ││
│        │  │      K│  │       │  │      8│  ││
│        │  └───────┘  │       │  └───────┘  ││
│        └─────────────┘       └─────────────┘│
├─────────────────────────────────────────────┤
│            Alice wins the round!            │
├─────────────────────────────────────────────┤
│      [ Play Round ] [ New Game ] [ Quit ]   │
└─────────────────────────────────────────────┘
```

**We have a playable game.**

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
#include "HandView.hpp"
#include "WarGame.hpp"

using namespace ftxui;

Element renderPlayedCard(int cardId) {
    if (cardId < 0) {
        return text("No card");
    }

    return renderCard(Card(cardId));
}

int main() {

    WarGame game;
    game.reset();

    RoundResult lastRound;

    auto screen = ScreenInteractive::TerminalOutput();

    auto playButton = Button("Play Round", [&] {
        if (!game.isGameOver()) {
            lastRound = game.playRound();
        }
    });

    auto newGameButton = Button("New Game", [&] {
        game.reset();
        lastRound = RoundResult{};
    });

    auto quitButton = Button("Quit", [&] {
        screen.Exit();
    });

    auto buttons = Container::Horizontal({
        playButton,
        newGameButton,
        quitButton,
    });

    auto renderer = Renderer(buttons, [&] {

        std::string status = "Ready to play";

        if (game.isGameOver()) {
            status = "Game Over: " + game.winnerName();
        }
        else if (lastRound.winner == 1) {
            status = game.getPlayer1().getName() + " wins the round!";
        }
        else if (lastRound.winner == 2) {
            status = game.getPlayer2().getName() + " wins the round!";
        }

        if (lastRound.wasWar) {
            status += " (WAR!)";
        }

        auto player1Display = vbox({
            text(game.getPlayer1().getName()) | bold | center,
            text("Cards: " + std::to_string(game.getPlayer1().cardCount())) | center,
            renderPlayedCard(lastRound.card1) | center,
        }) | border;

        auto player2Display = vbox({
            text(game.getPlayer2().getName()) | bold | center,
            text("Cards: " + std::to_string(game.getPlayer2().cardCount())) | center,
            renderPlayedCard(lastRound.card2) | center,
        }) | border;

        return vbox({
            text("TINYCHUNKS - WAR") | bold | center,

            separator(),

            hbox({
                player1Display,
                text("   VS   ") | vcenter,
                player2Display,
            }) | center,

            separator(),

            text(status) | center,

            separator(),

            buttons->Render() | center,

        }) | border;
    });

    screen.Loop(renderer);
}
```

</details>

---

## Step 16.9 — Test the game

Before calling it finished, test these scenarios on purpose:

| # | Scenario         | Check that…                                                                |
| - | ---------------- | -------------------------------------------------------------------------- |
| 1 | Ordinary round   | The higher rank wins both cards. The two counts still add up to 52.          |
| 2 | War              | "(WAR!)" appears, several cards move at once, and the total stays 52.      |
| 3 | Aces             | An Ace beats a King. (Remember `warValue()`.)                              |
| 4 | Game over        | "Game Over: …" appears and Play Round does nothing.                        |
| 5 | New Game         | Counts return to 26 / 26 and the played cards disappear.                   |
| 6 | Quit             | The program exits cleanly.                                                 |

A full game takes a couple of hundred clicks, so scenarios 4 and 5 are tedious by hand. That's what the challenge below is for.

---

## Step 16.10 — Invariants

The most useful idea in this lesson is the **invariant**: something that must *always* be true.

For our game:

```cpp
player1.cardCount() + player2.cardCount() == 52
```

after every round. The only exception is a draw (Step 16.2), where the last pot goes to nobody.

Invariants are great test targets. We found the Lesson 15 "disappearing cards" bug because the Total line stopped saying 52.

To make the invariant hold even for draws, the game could keep the unclaimed cards:

```cpp
std::vector<int> unresolvedPot;
```

so that *Player 1 + Player 2 + unresolved pot = 52*, always. That's a worthwhile extension.

---

## Step 16.11 — Student challenges

1. **Auto-play.** Add a "Play 10 Rounds" button. Should it stop early when the game ends?
2. **Score.** Use your Lesson 14 `roundsWon` counter to show how many rounds each player has won.
3. **Test program.** Add a second executable, `war_test`, built from a `tests/war_test.cpp` and every `src/*.cpp` **except** `main.cpp`. It should play 1,000 complete games and print how many ended, how many were draws, and the average number of rounds. It should print an error if the total ever isn't 52. (Hint: copy the `add_executable(war ...)` block in CMake. Why can't the test program include `main.cpp`?)
4. **Show the hands.** Use `HandView` to display each player's whole hand under their played card. Is the screen big enough? What would you change?

---

## Final project structure

```text
tinychunks/
├── CMakeLists.txt
├── .gitignore
│
├── examples/              Lessons 01–07: FTXUI + Counter warm-ups
│   ├── 01_box.cpp
│   ├── 02_renderer.cpp
│   ├── 03_buttons.cpp
│   ├── 04_containers.cpp
│   ├── 05_counter.cpp
│   ├── 06_counter.cpp
│   ├── 07_counter_view.cpp
│   ├── Counter.hpp
│   └── Counter.cpp
│
├── include/               Lessons 08–16: class declarations
│   ├── Card.hpp
│   ├── Deck.hpp
│   ├── Hand.hpp
│   ├── HandView.hpp
│   ├── Player.hpp
│   └── WarGame.hpp
│
└── src/                   Lessons 08–16: the War application
    ├── main.cpp
    ├── Card.cpp
    ├── Deck.cpp
    ├── Hand.cpp
    ├── HandView.cpp
    ├── Player.cpp
    └── WarGame.cpp
```

Your git log is the history of how it got here:

```bash
git log --oneline
```

---

## What did we actually learn?

| OOP / C++ concept                  | Where it showed up                       |
| ---------------------------------- | ---------------------------------------- |
| Lambdas and captures               | Renderers and button callbacks (02–04)   |
| Classes, constructors, init lists  | `Counter` (05), `Card` (08), `Player` (14) |
| Header / implementation files      | `Counter` (06), every class after 09     |
| Compiling vs linking               | Lesson 06                                |
| Encapsulation and invariants       | `Card::setId`, `Hand::add`, `WarGame`    |
| `std::vector`                      | `Deck`, `Hand`, the pot                  |
| Composition (*has-a*)              | `Player` has a `Hand`; `WarGame` has players and a deck |
| References (*uses-a*)              | `CounterView`, `HandView`                |
| Const-correctness                  | `getHand()`, `HandView`, getters         |
| Delegation                         | `Player::playCard()` → `Hand::removeCard()` |
| Events                             | `CatchEvent`, `HandView::handleEvent`    |
| Separation of concerns             | Rules in `WarGame`, drawing in `main()` / `HandView` |
| Testing with invariants            | The 52-card total                        |

### Did we need inheritance?

**Not once.** We built a complete application with composition, encapsulation, delegation, and plain value semantics.

That's not an argument against inheritance. It's the right tool when you have a genuine *is-a* relationship and need **polymorphism**: several types used through one interface. (Lesson 13 showed a case where FTXUI's `ComponentBase` would be the right choice.) But inheritance isn't the foundation of every good object-oriented design.

### The architecture we ended with

```text
┌────────────────────────────────────┐
│     FTXUI Interface  (main.cpp)    │
│   buttons, rendering, events       │
└────────────────┬───────────────────┘
                 │ asks / tells
                 ▼
┌────────────────────────────────────┐
│             WarGame                │
│   rules, rounds, game state        │
└────────────────┬───────────────────┘
                 │ owns
                 ▼
┌────────────────────────────────────┐
│          Domain Objects            │
│   Player, Hand, Deck, Card         │
└────────────────────────────────────┘
```

Arrows only point **down**. Nothing below the top layer knows FTXUI exists. We could swap the terminal UI for SDL, a web page, or a test program without changing a single rule of War. Challenge 3 does exactly that.

## Commit your work

```bash
git add .
git commit -m "Lesson 16: finished War"
```

**Sixteen lessons. Five model classes and one view. One game of War. No unnecessary inheritance.**
