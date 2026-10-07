#include "ConsoleView.hpp"
#include "HiLo.hpp"
#include "TuiView.hpp"

#include <iostream>
#include <memory>
#include <string>

// Tests talk to the game directly. No view needed, which is
// only possible because the rules are not inside a view.
static int runTests() {
  int failures = 0;
  auto check = [&](bool ok, const std::string &name) {
    std::cout << (ok ? "PASS  " : "FAIL  ") << name << '\n';
    if (!ok) failures++;
  };

  // Stacked deck: 5C, then 9C, then 2C, then 2D, ...
  // Card values: Clubs 0-12 (Ace=0), Diamonds 13-25.
  HiLo g(Deck({Card(4), Card(8), Card(1), Card(14), Card(0), Card(13)}));

  check(g.currentCard().getValue() == 4, "first card is 5C");
  check(g.guess(Guess::Higher) && g.lastResult() == Result::Correct,
        "5 -> 9, guessed higher: correct");
  check(g.score() == 1, "score went up");
  check(g.guess(Guess::Higher) && g.lastResult() == Result::Wrong,
        "9 -> 2, guessed higher: wrong");
  check(g.lives() == 2, "lost a life");
  check(g.guess(Guess::Lower) && g.lastResult() == Result::Tie,
        "2 -> 2: tie");
  check(g.lives() == 2 && g.score() == 1, "tie changes nothing");
  check(!g.restart(), "restart refused while still playing");

  g.guess(Guess::Higher); // 2 -> A(low): wrong, lives 1
  g.guess(Guess::Higher); // A -> A:      tie, deck now empty
  check(g.phase() == Phase::GameOver, "empty deck ends the game");
  check(!g.guess(Guess::Lower), "guess refused after game over");

  return failures == 0 ? 0 : 1;
}

int main(int argc, char **argv) {
  std::string mode = argc > 1 ? argv[1] : "";
  if (mode == "--test")
    return runTests();

  HiLo game;

  // Polymorphism: main() never knows which kind of view it has.
  std::unique_ptr<GameView> view;
  if (mode == "--text")
    view = std::make_unique<ConsoleView>(game);
  else
    view = std::make_unique<TuiView>(game);

  view->run();
  return 0;
}
