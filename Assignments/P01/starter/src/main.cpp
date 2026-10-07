// Starter main. Right now it only proves the classes link together.
// Replace the body as described in the assignment README:
//
//   ./game          -> runs your TuiView (FTXUI)
//   ./game --text   -> runs your ConsoleView (cout/cin)
//
// Final shape (sketch):
//
//   VideoPoker game;            // or Blackjack game;
//   std::unique_ptr<GameView> view;
//   if (textMode) view = std::make_unique<ConsoleView>(game);
//   else          view = std::make_unique<TuiView>(game);
//   view->run();

#include "Card.hpp"
#include "Deck.hpp"

#include <iostream>
#include <string>

int main(int argc, char **argv) {
  Deck deck;
  deck.shuffle();

  std::cout << "Five random cards: ";
  for (int i = 0; i < 5; i++)
    std::cout << deck.deal().toString() << ' ';
  std::cout << "\nCards left: " << deck.size() << '\n';

  // Stacked deck demo: the first card listed is dealt first.
  Deck stacked({Card(0), Card(13), Card(26), Card(39), Card(12)});
  std::cout << "Stacked deck deals: ";
  while (!stacked.empty())
    std::cout << stacked.deal().toString() << ' ';
  std::cout << '\n';

  return 0;
}
