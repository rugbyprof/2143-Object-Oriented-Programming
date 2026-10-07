#pragma once

#include <string>

// A card is stored as one integer 0-51, same as in lecture:
//   suit = value / 13   (0 Clubs, 1 Diamonds, 2 Hearts, 3 Spades)
//   rank = value % 13   (0 Ace, 1 Two, ... 9 Ten, 10 Jack, 11 Queen, 12 King)
// A card never changes after it is built, so there are no setters.
class Card {
private:
  int value;

public:
  explicit Card(int value = 0);

  int getValue() const;
  int getRank() const; // 0-12, Ace is 0
  int getSuit() const; // 0-3

  std::string rankSymbol() const; // "A", "2", ... "10", "J", "Q", "K"
  std::string suitSymbol() const; // "♣" "♦" "♥" "♠"  (use in the TUI)
  char suitLetter() const;        // 'C' 'D' 'H' 'S'  (use in the console)
  bool isRed() const;

  std::string toString() const; // plain ASCII, e.g. "10H", "AS"
};
