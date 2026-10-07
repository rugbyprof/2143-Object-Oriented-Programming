#pragma once

#include "Card.hpp"

#include <vector>

class Deck {
private:
  std::vector<Card> cards; // undealt cards; the back is the top

public:
  Deck(); // a fresh, ordered 52-card deck

  // A "stacked" deck for testing. The FIRST card in the list is dealt first.
  // Example: Deck d({Card(0), Card(13), Card(26), Card(39), Card(1)});
  explicit Deck(const std::vector<Card> &stacked);

  void reset(); // back to a fresh, ordered 52-card deck
  void shuffle();
  Card deal(); // throws std::runtime_error if empty

  bool empty() const;
  int size() const;
};
