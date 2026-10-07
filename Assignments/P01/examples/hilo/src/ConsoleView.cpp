#include "ConsoleView.hpp"

#include <iostream>
#include <string>

ConsoleView::ConsoleView(HiLo &game) : game(game) {}

void ConsoleView::showState() const {
  // Turning a Result into words is the VIEW's job.
  switch (game.lastResult()) {
  case Result::Correct: std::cout << "  Correct!\n"; break;
  case Result::Wrong:   std::cout << "  Wrong!\n";   break;
  case Result::Tie:     std::cout << "  Tie - no harm done.\n"; break;
  case Result::None:    break;
  }
  if (game.lastResult() != Result::None)
    std::cout << "  " << game.previousCard().toString() << " -> "
              << game.currentCard().toString() << '\n';

  std::cout << "Card: " << game.currentCard().toString()
            << "   Score: " << game.score()
            << "   Lives: " << game.lives()
            << "   Cards left: " << game.cardsLeft() << '\n';
}

void ConsoleView::run() {
  std::string line;
  while (true) {
    showState();

    if (game.phase() == Phase::GameOver) {
      std::cout << "GAME OVER. Final score: " << game.score()
                << "\nPlay again? (y/n): ";
      if (!std::getline(std::cin, line) || line != "y")
        return;
      game.restart();
      continue;
    }

    std::cout << "Higher or lower? (h/l, q to quit): ";
    if (!std::getline(std::cin, line) || line == "q")
      return;

    // Each command is ONE call into the game. No rules here.
    if (line == "h")
      game.guess(Guess::Higher);
    else if (line == "l")
      game.guess(Guess::Lower);
    else
      std::cout << "  Please type h, l, or q.\n";
  }
}
