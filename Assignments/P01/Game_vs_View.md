# Handout: Separating the Game from the Screen

> **Read this before you write any code for P01.** It walks through one small, complete game (Hi-Lo), built the right way, one step at a time. Then you do the same steps for Video Poker or Blackjack.
>
> The full working example is in [`examples/hilo/`](./examples/hilo/). Build it, play it, and read it.

---

## 1. The idea in one sentence

**The code that knows the rules should not know how the game is shown, and the code that shows the game should not know the rules.**

That's it. Everything else in this handout explains *why* and *how*.

The fancy word for this is **decoupling**. Two pieces of code are **coupled** when you can't change one without breaking or rewriting the other. **Decoupled** code is code you can change, replace, or test one piece at a time.

---

## 2. An analogy: your bank account

Think about all the ways you can reach your bank account:

```text
   ATM machine      phone app       teller window
        │               │                 │
        └───────────────┼─────────────────┘
                        │  "withdraw $40"
                        ▼
              ┌───────────────────┐
              │   THE BANK        │
              │   balance: $65    │
              │   rule: no going  │
              │   below $0        │
              └───────────────────┘
```

- The **rule** ("you can't withdraw more than you have") lives in **the bank**, in one place.
- The ATM, the app, and the teller just **ask**: "Can this person withdraw $40?" The bank says yes or no.
- The bank doesn't care whether the request came from a touchscreen or a person at a counter.

Now imagine each ATM had its own copy of the rule, and someone updated the app's copy but forgot the ATMs'. Now the app says you're broke while the ATM hands you cash. That's what tangled code does to a program.

**In P01:**

| Bank world | P01 world |
| --- | --- |
| The bank | Your game class (`VideoPoker` / `Blackjack`). We'll call it the **model**. |
| ATM, app, teller | `ConsoleView`, `TuiView`. These are the **views**. |
| "Withdraw $40" | `game.draw()`, `game.hit()`. These are **actions**. |
| "What's my balance?" | `game.credits()`, `game.hand()`. These are **questions** (getters). |

---

## 3. What the problem looks like

Here is Hi-Lo written the *tempting* way. It's a perfectly natural thing to write when you start from the FTXUI demo, and it **works**:

```cpp
// main.cpp: everything in one place. Don't do this.
int main() {
  Deck deck;  deck.shuffle();
  Card current = deck.deal();
  int score = 0, lives = 3;
  std::string message;

  auto screen = ScreenInteractive::TerminalOutput();
  auto renderer = Renderer([&] { /* draw current, score, lives, message */ });

  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::ArrowUp) {               // guessed "higher"
      Card next = deck.deal();
      if (next.getRank() > current.getRank()) { score++;  message = "Correct!"; }
      else if (next.getRank() < current.getRank()) { lives--; message = "Wrong!"; }
      else message = "Tie";
      current = next;
      if (lives == 0) message = "GAME OVER";
      return true;
    }
    if (e == Event::ArrowDown) {             // guessed "lower"
      // ...the SAME logic again, flipped...
    }
    return false;
  });
  screen.Loop(app);
}
```

Nothing seems wrong until someone asks you to do something new. Try to answer these four questions about the code above:

1. **"Add a cout/cin version."** All the rules are inside an FTXUI lambda. A `cin` loop can't call them. You'd have to **copy and paste** them, and now the rules exist twice.
2. **"Prove that a tie doesn't cost a life."** How would you test that? You'd have to run the program and press keys until a tie happens. There's nothing you can call from a test.
3. **"What happens if they keep pressing ↑ after GAME OVER?"** Look closely. Nothing stops it. `lives` goes to -1, -2, ... and `deck.deal()` eventually throws on an empty deck. Every view would need its own guard, and one of them will forget.
4. **"Change the rule: a tie should end the game."** You have to find every place the rule was copied. Miss one, and the two versions of your game disagree.

Every one of these problems has the same cause: **the rules live inside the screen code.**

---

## 4. The fix, step by step

We'll rebuild Hi-Lo properly. Do these steps **in this order**. The order is the point.

### Step 1: List what the game must REMEMBER (state)

Pretend there's no screen. You're the game's brain. What do you have to keep track of between turns?

- the deck
- the current card (and the previous one, so a view can show "was → now")
- score
- lives
- which phase the game is in (still playing? over?)
- what happened on the last guess (correct / wrong / tie)

These become **private** data members. Nobody outside can change them directly.

```cpp
class HiLo {
private:
  Deck deck_;
  Card current_;
  Card previous_;
  int score_ = 0;
  int lives_ = 3;
  Phase phase_ = Phase::Guessing;
  Result last_ = Result::None;
```

> Notice `last_` is a `Result` (an enum), **not** a string like `"Correct!"`. Words and colors are how something *looks*, so they're the view's decision. The game only records **what happened**.

### Step 2: List what the player can DO (actions)

What can a player *ask for*? Use verbs:

- guess higher, or guess lower
- start over (after the game ends)

Each action becomes a **public method that returns `bool`**: `true` means "done", and `false` means "not allowed right now, nothing changed".

```cpp
public:
  bool guess(Guess g);   // Guess::Higher or Guess::Lower
  bool restart();
```

### Step 3: List what a screen needs to KNOW (questions)

Imagine you're drawing the screen. What do you need to ask the game?

```cpp
  Phase phase() const;
  const Card& currentCard() const;
  const Card& previousCard() const;
  int score() const;
  int lives() const;
  Result lastResult() const;
  int cardsLeft() const;
```

All of them are `const`. Asking a question must **never** change the game. Note that there's **no** `getDeck()`. A view has no business touching the deck. Only expose what a view actually needs to draw.

### Step 4: Draw the phases, and guard every action

A **phase** says what's allowed *right now*. Draw it before you code it:

```text
             guess()
            ┌───────┐
            ▼       │
 start ──► Guessing ─┴── guess() when lives hit 0 or deck runs out ──► GameOver
            ▲                                                             │
            └─────────────────────────── restart() ───────────────────────┘
```

| Phase | `guess()` | `restart()` |
| --- | --- | --- |
| Guessing | ✅ allowed | ❌ returns `false` |
| GameOver | ❌ returns `false` | ✅ allowed |

Make this table for your own game. Every ❌ is an `if` at the top of an action method.

Then **every action checks the phase first**:

```cpp
bool HiLo::guess(Guess g) {
  if (phase_ != Phase::Guessing)   // not allowed right now?
    return false;                  // refuse, change nothing

  previous_ = current_;
  current_  = deck_.deal();

  int before = previous_.getRank();
  int after  = current_.getRank();

  if (after == before) {
    last_ = Result::Tie;
  } else if ((g == Guess::Higher) == (after > before)) {
    last_ = Result::Correct;
    score_++;
  } else {
    last_ = Result::Wrong;
    lives_--;
  }

  if (lives_ == 0 || deck_.empty())
    phase_ = Phase::GameOver;
  return true;
}
```

Compare this to question 3 in section 3. Pressing ↑ after game over **can't** break anything now, in *any* view, because the game itself refuses. The views don't need to remember to check.

### Step 5: Prove it works with NO screen at all

Before you write a single line of `cout` or FTXUI, test the game by calling its methods. A **stacked deck** lets you pick the exact cards:

```cpp
// Cards come out in this order: 5C, 9C, 2C, 2D, ...
HiLo g(Deck({Card(4), Card(8), Card(1), Card(14), Card(0), Card(13)}));

check(g.guess(Guess::Higher) && g.lastResult() == Result::Correct, "5 -> 9 higher");
check(g.guess(Guess::Higher) && g.lastResult() == Result::Wrong,   "9 -> 2 higher");
check(g.guess(Guess::Lower)  && g.lastResult() == Result::Tie,     "2 -> 2 tie");
check(g.lives() == 2 && g.score() == 1, "tie changes nothing");
```

Run `./build/hilo --test`:

```text
PASS  first card is 5C
PASS  5 -> 9, guessed higher: correct
...
PASS  guess refused after game over
```

**This is the test that proves you decoupled.** If you can play your entire game from `main()` with no view, the rules are in the right place.

### Step 6: Write the first view: ConsoleView

A view does three things in a loop, and that's all it does:

```text
  ┌──► 1. ASK the game questions, and SHOW the answers
  │    2. READ what the user typed or pressed
  └─── 3. Make ONE call to the game
```

```cpp
void ConsoleView::run() {
  std::string line;
  while (true) {
    showState();                                   // 1. ask + show

    if (game.phase() == Phase::GameOver) { /* ask play again? */ }

    std::cout << "Higher or lower? (h/l, q to quit): ";
    if (!std::getline(std::cin, line) || line == "q") return;   // 2. read

    if (line == "h")      game.guess(Guess::Higher);   // 3. one call
    else if (line == "l") game.guess(Guess::Lower);
    else std::cout << "  Please type h, l, or q.\n";
  }
}
```

Look at what is **not** here: no rank comparisons, no `score++`, no `lives--`. The view doesn't know how Hi-Lo is scored, and it doesn't need to.

Turning a `Result` into words **is** the view's job, and that's fine:

```cpp
switch (game.lastResult()) {
  case Result::Correct: std::cout << "  Correct!\n"; break;
  case Result::Wrong:   std::cout << "  Wrong!\n";   break;
  ...
}
```

### Step 7: Write the second view: TuiView

Same three jobs, different tools. FTXUI happens to split them into two pieces for you:

| Job | FTXUI piece | Rule of thumb |
| --- | --- | --- |
| Ask + show | `Renderer([&]{ ... })` | Only **reads** from the game. Calls only `const` methods. |
| Read input + one call | `CatchEvent(..., [&](Event e){ ... })` | Each key → **one line**, one game call. |

```cpp
auto app = CatchEvent(renderer, [&](Event e) {
  if (e == Event::ArrowUp)        return game.guess(Guess::Higher);
  if (e == Event::ArrowDown)      return game.guess(Guess::Lower);
  if (e == Event::Character('r')) return game.restart();
  if (e == Event::Character('q')) { screen.Exit(); return true; }
  return false;
});
```

Compare that to the 15-line handler in section 3. **This is what the finished handler should look like in your project too:** short, boring lines that each make one call.

Writing the second view should feel *easy*. If it feels like rewriting the game, some rules are still stuck in your first view. Go find them and move them into the game class.

### Step 8: Let `main()` choose a view (polymorphism)

Both views inherit from `GameView`, so `main()` can treat them the same:

```cpp
HiLo game;
std::unique_ptr<GameView> view;
if (mode == "--text") view = std::make_unique<ConsoleView>(game);
else                  view = std::make_unique<TuiView>(game);
view->run();     // main() doesn't know or care which one it got
```

Each view holds a **reference** to the game (`HiLo& game;`). It *uses* the game but doesn't *own* it. There is exactly one game, and the views are different windows into it.

---

## 5. Practice: where does it go?

For each line, decide: **Game** (model) or **View**? Cover the answers first.

| # | Code / task |
| --- | --- |
| 1 | `if (lives_ == 0) phase_ = Phase::GameOver;` |
| 2 | Choose red for ♥ and ♦ |
| 3 | Decide that a pair of Jacks pays 1× the bet |
| 4 | `std::cout << "Credits: " << game.credits();` |
| 5 | Remember which card the arrow-key cursor is on |
| 6 | Remember which cards the player is holding |
| 7 | Refuse a bet bigger than the player's credits |
| 8 | Turn `HandRank::FullHouse` into the text `"Full House!"` |
| 9 | Count an Ace as 1 instead of 11 so the hand doesn't bust |
| 10 | Clear `cin` after the user types `abc` for a bet |
| 11 | Hide the dealer's hole card until the player stands |
| 12 | Draw the hidden hole card as a box full of `░` |

<details>
<summary><b>Answers</b> (try first!)</summary>

| # | Answer | Why |
| --- | --- | --- |
| 1 | **Game** | A rule about when the game ends. |
| 2 | **View** | Color is appearance. The console view doesn't even use color. |
| 3 | **Game** | A payout rule. It has to be identical in every view. |
| 4 | **View** | Printing. The game only *answers* `credits()`. |
| 5 | **View** | ⚠️ Tricky! The cursor only exists in the TUI. The console has no cursor. That makes it *view state*, so it belongs in `TuiView`, like `int selected` in the demo. |
| 6 | **Game** | ⚠️ Tricky! Which cards are held affects `draw()`, so it's *game state*. Both views must agree on it. |
| 7 | **Game** | A rule. `deal(bet)` returns `false`, and the view then decides how to tell the user. |
| 8 | **View** | Words are appearance. The game provides the enum, or at most a `rankName()` helper both views can share. |
| 9 | **Game** | Scoring rule. |
| 10 | **View** | It's about *how input arrives*. The FTXUI view never deals with `cin`. |
| 11 | **Game** | Whether a card is secret is a rule (`dealerHoleHidden()`). |
| 12 | **View** | *How* a secret card looks is appearance. |

**The test for any line:** *"If I wrote a third view tomorrow, would I need this exact same logic again?"* If yes, it belongs in the **game**. If each view would do it differently, it belongs in the **view**.

</details>

---

## 6. "But what about…?"

**Can a view have its own variables?**
Yes! The FTXUI cursor position (`selected`), a half-typed input string, and which screen of a menu you're on are all *view state*. The rule isn't "views have no data". It's "views have no **rules**."

**How does the view know an action failed, so it can show a message?**
Actions return `bool`. For example:

```cpp
if (!game.deal(bet)) message = "You can't bet that much.";
```

The game says *no*. The view decides how to *say* no.

**Isn't this more code than the tangled version?**
A little more at first, yes. But the second view is mostly free, testing becomes possible, and bugs get fixed in one place. You pay a small cost up front to avoid a huge cost later.

**Do I need `ConsoleView` if I already have `TuiView`?**
For P01, yes, it's required. It's also your safety net: if FTXUI breaks on your machine at 11 PM, the console version still compiles with plain `g++`.

**Where do helpers like `rankName(HandRank)` go?**
Text that *every* view would show the same way can be a `static` helper on the game class, so both views share it. It's fine as long as it doesn't print anything. It just returns a string.

---

## 7. Self-check before you submit

**1. The "no I/O" check.** Your game files must not mention `cout`, `cin`, or `ftxui`.

macOS / Linux:

```bash
grep -nE "cout|cin|ftxui" include/VideoPoker.hpp src/VideoPoker.cpp
```

Windows PowerShell:

```powershell
Select-String -Pattern "cout|cin|ftxui" include\VideoPoker.hpp, src\VideoPoker.cpp
```

(Use `Blackjack` if that's your game.) **No output = pass.**

**2. The "delete the views" check.** Could your `--test` mode play a full hand using only game methods? If yes, you're decoupled.

**3. The "boring handler" check.** Is every branch in your `CatchEvent` handler about one line long? If any branch has an `if` about cards, scores, or money, move that logic into the game.

**4. The "spam the keys" check.** In both views, press Draw/Hit/Stand many times quickly, including after the round or game is over. Nothing should crash or go negative.

---

## 8. Now do it for your game

Fill this in **on paper** before you write code. It's Steps 1–4 for your own game, with a few rows started for you.

### Video Poker

| Step | Your list |
| --- | --- |
| 1. State (remember) | deck, hand, which cards are held, credits, current bet, phase, last result, last payout, … |
| 2. Actions (do) | `deal(bet)`, `toggleHold(i)`, `draw()`, … |
| 3. Questions (know) | `hand()`, `isHeld(i)`, `credits()`, `phase()`, … |
| 4. Phases | `Betting` → `Holding` → `Betting` … → `GameOver`. Which actions are allowed in each phase? |

### Blackjack

| Step | Your list |
| --- | --- |
| 1. State (remember) | deck, player hand, dealer hand, chips, bet, phase, outcome, is the hole card hidden?, … |
| 2. Actions (do) | `startRound(bet)`, `hit()`, `stand()`, `nextRound()`, … |
| 3. Questions (know) | `playerHand()`, `dealerHand()`, `dealerHoleHidden()`, `chips()`, … |
| 4. Phases | `Betting` → `PlayerTurn` → `RoundOver` → `Betting` … → `GameOver`. Where does a natural blackjack skip to? Where does the dealer play? |

Then build in the same order as Hi-Lo: **game → tests → ConsoleView → TuiView.** Don't skip ahead to the pretty part.
