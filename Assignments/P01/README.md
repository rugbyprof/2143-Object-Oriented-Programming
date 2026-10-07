<details>
<summary>⚙️ Metadata (auto-managed by <code>readmees</code> — edit values, not structure)</summary>

```yaml
is_due: false
id: P01
name: P01
title: Terminal Card Game
description: Video Poker or Blackjack with a polymorphic UI (FTXUI)
category: Assignments
date_due:
  month: '11'
  day: '02'
  year: 2026
  hour: 11
```

</details>

## P01 — Terminal Card Game: Video Poker *or* Blackjack

You will build a playable card game that runs in the terminal. **You choose the game:**

| | Video Poker (Jacks or Better) | Blackjack |
| --- | --- | --- |
| Hardest part | Evaluating a 5-card poker hand | Aces count as 1 **or** 11; the dealer's rules |
| UI | Pick cards to hold, then draw | Hit or stand, dealer's hole card hidden |
| Good pick if… | You like logic puzzles | You like state and turn flow |

Both are worth the same and graded with the same rubric. Pick one and stick with it.

> **Before you start, read these:**
>
> 1. **[SETUP.md](./SETUP.md)**: install the tools and finish Milestone 0. Nearly every student who struggles on this project struggles with the setup, not the C++. Get it working in week one, while there's still time to get help.
> 2. **[CMake_Basics.md](./CMake_Basics.md)**: what CMake is, the two commands you'll use, what each line of `CMakeLists.txt` means, and how to tell which step an error came from.
> 3. **[Game_vs_View.md](./Game_vs_View.md)**: the design handout. It builds a small complete game (Hi-Lo) step by step, in exactly the structure this assignment requires. Its code is in [`examples/hilo/`](./examples/hilo/).

---

## 1. The big idea: the game doesn't know how it's being drawn

You will write **one** game and **two** ways to show it:

```text
            ┌───────────────────────────┐
            │      GameView (abstract)  │   virtual void run() = 0;
            └─────────────┬─────────────┘
                 ┌────────┴─────────┐
        ┌────────┴──────┐   ┌───────┴───────┐
        │  ConsoleView  │   │    TuiView    │
        │  cout / cin   │   │    FTXUI      │
        └────────┬──────┘   └───────┬───────┘
                 │   both talk to   │
                 └────────┬─────────┘
             ┌────────────┴────────────┐
             │  VideoPoker / Blackjack │   the rules + state
             │  (no cout, no FTXUI)    │
             └────────────┬────────────┘
                     has a│Deck, Hand(s)
                        Card
```

```bash
./build/game          # FTXUI terminal UI
./build/game --text   # plain cout/cin version
./build/game --test   # runs your rule tests and prints PASS/FAIL
```

Why bother with two views?

- **It's this unit's lesson.** `main()` holds a `std::unique_ptr<GameView>` and calls `view->run()`. It never knows or cares which kind of view it has. That is run-time polymorphism (W06), with composition (`Deck` *has* `Card`s) under it.
- **It protects you.** The console view needs nothing but `g++`. If your FTXUI setup breaks at 11 PM, your game logic still compiles, runs, and earns points.
- **It forces clean design.** If the rules live in the game class, the second view takes little work: it only *asks* the game what to show and *tells* it what the player did. If you put rules inside the first view (for example, scoring a poker hand inside a key-press handler), the second view can't reach them. Your only choices are to copy-paste the rules, so two copies drift apart, or to move them into the game class where they belonged. Writing the second view is how you *find out* whether you decoupled your code. See [Game_vs_View.md](./Game_vs_View.md) for the full walkthrough.

**The one hard rule:** your game class (`VideoPoker` or `Blackjack`) may **not** `#include <iostream>` or any FTXUI header, and may not print or read anything. It only stores state and enforces rules. The views do all the input and output.

---

## 2. What you're given (`starter/`)

```text
starter/
├── CMakeLists.txt     downloads + builds FTXUI for you; builds `check` and `game`
├── check/check.cpp    Milestone 0 toolchain test, don't change
├── include/
│   ├── Card.hpp       done: one int 0-51, rank = v % 13 (Ace = 0), suit = v / 13
│   ├── Deck.hpp       done: shuffle, deal, and a *stacked* constructor for testing
│   └── GameView.hpp   done: the abstract base class
└── src/
    ├── Card.cpp       done
    ├── Deck.cpp       done
    └── main.cpp       replace this
```

Also in this folder is [`examples/hilo/`](./examples/hilo/): a complete, working Hi-Lo game built exactly the way P01 asks, with a game class, `ConsoleView`, `TuiView`, and `--test`. It uses the same `Card`, `Deck`, and `GameView` as your starter. When you're unsure where something goes, look at how Hi-Lo does it. Build it the same way as the starter, from inside `examples/hilo/`.

`Card` and `Deck` match what we built in the Poker_Game lecture, with two additions:

- `Card` can describe itself two ways: `toString()` gives ASCII like `"10H"` for the console, and `rankSymbol()` + `suitSymbol()` give `"10"` + `"♥"` for the TUI.
- `Deck` has a **stacked** constructor. You choose exactly which cards come out, in order. This is how you test "does a flush pay 6?" without shuffling 10,000 times:

  ```cpp
  // A, 2, 3, 4, 5 of hearts (Hearts = 26..38): a straight flush, ace-low
  Deck d({Card(26), Card(27), Card(28), Card(29), Card(30)});
  ```

You may change `Card` and `Deck` if you have a good reason, but explain it in your README.

---

## 3. What you write

Every class goes in its own `.hpp` in `include/` and `.cpp` in `src/`. After you **add** a new `.cpp`, re-run the configure line (`cmake -S . -B build ...`).

### 3.1 `Hand`

A hand **has** cards (composition, so do **not** inherit from `Deck` or `vector`). At minimum:

```cpp
void addCard(const Card& c);
void clear();
int size() const;
const Card& at(int i) const;   // throws std::out_of_range on a bad index
```

Add what your game needs: `replace(int i, const Card& c)` for poker, `value()` and `isSoft()` for blackjack, and so on. Put the method on the class that **owns the data it uses**.

### 3.2 The game class: `VideoPoker` **or** `Blackjack`

Model it as a **state machine**. An `enum class Phase` says what the player is allowed to do right now, and every public method checks the phase before it does anything. If a call isn't allowed in the current phase, it does nothing and returns `false`. It never crashes. The suggested interfaces below are a strong starting point. You may rename things or add to them.

#### Option A — Video Poker (Jacks or Better)

**Rules**

1. Start with **100 credits**. The player bets **1–5 credits** and can't bet more than they have. The bet is subtracted right away.
2. Use a **fresh shuffled deck every hand**. Deal 5 cards face up.
3. The player marks any of the 5 cards as **held** (toggle on/off).
4. **Draw:** every card that is *not* held is replaced from the same deck.
5. Evaluate the final hand and pay `bet × multiplier` from the table. A royal flush bet at 5 credits pays **4000**, not 1250.
6. The game is over when credits reach 0.

| Hand | Pays (per credit bet) |
| --- | ---: |
| Royal Flush (10-J-Q-K-A, same suit) | 250 (**800** at 5 credits) |
| Straight Flush | 50 |
| Four of a Kind | 25 |
| Full House | 9 |
| Flush | 6 |
| Straight (A-2-3-4-5 **and** 10-J-Q-K-A both count) | 4 |
| Three of a Kind | 3 |
| Two Pair | 2 |
| Pair of **Jacks or better** (J, Q, K, A) | 1 |
| Anything else (including a pair of 10s or lower) | 0 |

"Pays 1" means you get your bet back. You don't come out ahead.

**Suggested interface**

```cpp
enum class Phase { Betting, Holding, GameOver };
enum class HandRank { Nothing, JacksOrBetter, TwoPair, ThreeOfAKind, Straight,
                      Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush };

class VideoPoker {
public:
  VideoPoker(int startingCredits = 100);

  bool deal(int bet);            // Betting -> Holding
  bool toggleHold(int index);    // only during Holding
  bool draw();                   // Holding -> Betting (or GameOver); scores + pays

  Phase phase() const;
  int credits() const;
  const Hand& hand() const;
  bool isHeld(int index) const;
  HandRank lastResult() const;
  int lastPayout() const;

  static HandRank evaluate(const Hand& h);   // pure function: easy to test
  static int multiplier(HandRank r, int bet);
  static std::string rankName(HandRank r);   // "Full House", ...
};
```

Testing tip: give `VideoPoker` a way to accept a stacked `Deck` (a constructor parameter, or a `setNextDeck()` used only by tests).

#### Option B — Blackjack

**Rules**

1. Start with **100 chips**. The player bets **1 to all their chips**. Use a **fresh shuffled deck every round**.
2. Deal in this order: player, dealer, player, dealer. The dealer's **second card is face down** (the "hole card") until the dealer plays.
3. **Card values:** 2–10 are face value, J/Q/K are 10, and an Ace is 11 unless that would make the hand go over 21, in which case it's 1. A hand with an Ace still counted as 11 is **soft**.
4. **Natural blackjack** means an Ace plus a 10-value card on the first two cards.
   - Player natural, dealer doesn't have one: the player wins **3:2**, which is `bet * 3 / 2` with integer division.
   - Both have one: **push** (the bet is returned).
   - Dealer natural only: the player loses.
   - Check for naturals right after the deal. The player doesn't get to act.
5. **Player turn:** **Hit** (take a card) or **Stand**. Going over 21 is a **bust** and an instant loss. The dealer doesn't play.
6. **Dealer turn:** reveal the hole card. The dealer **must hit on 16 or less** and **must stand on 17 or more**, including soft 17.
7. **Settle:** a dealer bust means the player wins. Otherwise the higher total wins, and a tie is a push. A normal win pays **1:1**.
8. The game is over when the player has 0 chips.

**Suggested interface**

```cpp
enum class Phase   { Betting, PlayerTurn, RoundOver, GameOver };
enum class Outcome { None, PlayerBlackjack, PlayerWin, DealerWin, Push,
                     PlayerBust, DealerBust };

class Blackjack {
public:
  Blackjack(int startingChips = 100);

  bool startRound(int bet);      // Betting -> PlayerTurn (or RoundOver on a natural)
  bool hit();                    // only during PlayerTurn; may bust -> RoundOver
  bool stand();                  // dealer plays, round is settled -> RoundOver
  bool nextRound();              // RoundOver -> Betting (or GameOver)

  Phase phase() const;
  int chips() const;
  const Hand& playerHand() const;
  const Hand& dealerHand() const;
  bool dealerHoleHidden() const;  // the views must respect this!
  Outcome outcome() const;

  static int handValue(const Hand& h);     // pure function: easy to test
  static bool isSoft(const Hand& h);
  static std::string outcomeName(Outcome o);
};
```

> Notice `dealerHoleHidden()`. The **game** decides whether the hole card is secret, and the **views** obey. If your TuiView decides that on its own, you've put a rule in the view.

### 3.3 `ConsoleView : public GameView`

- A plain text loop using `cout` and `cin`. Show the state, read a command, and call **one** method on the game.
- Use **ASCII only** (`card.toString()`, e.g. `AS 10H KD`). No ♠ symbols here, because the Windows console mangles them.
- Handle bad input: letters where a number was expected, out-of-range bets, and indexes. Clear `cin` and re-prompt. It must **never** crash or loop forever.

Example (Video Poker):

```text
Credits: 100   Bet (1-5, q to quit): 5
  [1] KH   [2] KS   [3] 4D   [4] 9C   [5] 2H
Toggle holds (e.g. "1 2"), or press Enter to draw: 1 2
  [1] KH*  [2] KS*  [3] 4D   [4] 9C   [5] 2H
Toggle holds, or press Enter to draw:
  [1] KH*  [2] KS*  [3] KC   [4] 7S   [5] 3D
THREE OF A KIND! Pays 15.   Credits: 110
```

### 3.4 `TuiView : public GameView` (FTXUI)

Start from the demo in `Resources/ftxui/main.cpp`. It already draws cards, moves a cursor, and toggles HOLD. Your job is to wire it to **your game class** instead of the hard-coded `std::array<Card, 5>`:

- The `Renderer([&]{ ... })` lambda only **reads** from the game: `game.hand()`, `game.isHeld(i)`, `game.credits()`, `game.phase()`, and so on.
- The `CatchEvent(...)` handler only translates keys into **one game call**, like `game.toggleHold(selected)` or `game.hit()`. If you're writing an `if` about poker or blackjack rules in there, stop, and move it into the game class.
- Show, at minimum: the cards (red ♦ ♥, white ♣ ♠), credits/chips, current bet, a message line (result, payout, or "Not enough credits"), and the available keys for the current phase.
- Blackjack: draw the hole card face down (for example, a box full of `░`) while `dealerHoleHidden()` is true, and show both hand totals, except the dealer's while the hole card is hidden.

Key bindings are up to you. Show them on screen.

### 3.5 `main.cpp`

```cpp
int main(int argc, char** argv) {
  std::string mode = (argc > 1) ? argv[1] : "";
  if (mode == "--test") return runTests();   // see section 4

  VideoPoker game;   // or Blackjack
  std::unique_ptr<GameView> view;
  if (mode == "--text") view = std::make_unique<ConsoleView>(game);
  else                  view = std::make_unique<TuiView>(game);
  view->run();
}
```

Each view stores a **reference** to the game (`VideoPoker& game;`), set in its member initializer list. The view doesn't own the game, it just uses it.

---

## 4. Tests (`./build/game --test`)

Write a `runTests()` function (in `src/Tests.cpp`) that uses **stacked decks** and pure functions to check your rules. For each check, print one `PASS`/`FAIL` line, then return `0` if everything passed and `1` if anything failed.

**Video Poker — at minimum, one test for each:**

- every `HandRank` from Nothing to RoyalFlush (10 tests)
- a pair of 10s → `Nothing`; a pair of Jacks → `JacksOrBetter`
- A-2-3-4-5 → `Straight`; 10-J-Q-K-A mixed suits → `Straight`; Q-K-A-2-3 → **not** a straight
- royal flush pays 4000 at bet 5, and 250 per credit at bets 1–4
- held cards survive `draw()`, and unheld cards are replaced

**Blackjack — at minimum:**

- `A + K` = 21 and is a natural; `A + 6` = 17 soft; `A + 6 + 10` = 17 hard; `A + A + 9` = 21
- `K + Q + 5` busts
- the dealer stands on soft 17 and hits on 16 (stack the deck to force it)
- a natural pays 3:2 (bet 10 → +15), and a natural vs. a dealer natural pushes
- `hit()` during `Betting` returns `false` and changes nothing

---

## 5. Milestones & submission

| # | Due | What | Points |
| --- | --- | --- | ---: |
| M0 | end of **week 1** | Screenshot of `./build/check` running ([SETUP.md](./SETUP.md)) | 10 |
| M1 | end of **week 2** | `Hand` + game class + `ConsoleView` + `--test`. Fully playable with `--text`. | 45 |
| M2 | end of **week 3** | `TuiView`, `main` selects views polymorphically, README | 45 |

Submit your `starter/` folder **without** the `build/` directory (it's huge) to your course repo under `Assignments/P01/`. Include a `README.md` with:

- which game you chose
- how to build and run it (copy your exact commands)
- a screenshot of the TUI mid-game
- anything that doesn't work (being honest earns more partial credit than hiding it)
- any changes you made to `Card` or `Deck`, and why

---

## 6. Grading (100)

| Area | Pts | What "full credit" looks like |
| --- | ---: | --- |
| M0 toolchain screenshot | 10 | On time, `check` visibly running |
| Game rules correct | 20 | Matches every rule in §3.2; tests prove it |
| Tests (`--test`) | 10 | All required cases, clear PASS/FAIL output |
| OOP design | 25 | Game class has **no** I/O; private data; `const` getters; composition (`Hand` *has* `Card`s); state enforced by `Phase`; `GameView` used polymorphically through a `unique_ptr` |
| ConsoleView | 10 | Playable, ASCII-only, survives garbage input |
| TuiView | 20 | Playable, readable, red/black suits, shows keys, messages, and credits |
| Code quality + README | 5 | Consistent names, one class per file pair, short functions, README complete |

**Automatic deductions:** doesn't compile (−50 for that milestone); `cout`/`cin`/FTXUI inside the game class (−10); game rules inside a view (−10); `using namespace std;` in a header (−5).

---

## 7. Extra credit (max +10)

- **Video Poker:** a "Deuces Wild" variant. Make `PayTable` an abstract class with `JacksOrBetterTable` and `DeucesWildTable` subclasses, chosen at startup. (+5)
- **Blackjack:** Double Down, and/or Split. (+5 each)
- A third view: `SdlView : public GameView` that uses the card images in `Resources/sdl3/png/`. The file number is the same as `Card::getValue()`. (+5, and it's on you to get SDL3 installed)
- A high-score or bankroll file saved between runs (+3)

---

## 8. Common mistakes (read these before you start)

1. **Starting with the TUI.** Get `--text` fully working first. FTXUI is just a different face on a game that already works.
2. **Rules in the key handler.** `if (event == Event::Return) { /* 40 lines of poker */ }` is the #1 design deduction. The handler should be a one-line call into the game.
3. **Forgetting the phase.** What happens if someone presses Draw twice? Or Hit after the round ended? The game class must say no.
4. **`Hand : public std::vector<Card>`** or **`Hand : public Deck`**. A hand is not a vector, and a hand is not a deck. Use composition.
5. **Testing by playing.** You'll never see a royal flush by playing. Stack the deck.
6. **Treating `build/` as precious.** If CMake acts strange, delete the `build/` folder and configure again.
