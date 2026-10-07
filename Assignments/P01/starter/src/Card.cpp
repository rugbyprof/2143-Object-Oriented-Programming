#include "Card.hpp"

#include <stdexcept>

Card::Card(int value) : value(value) {
  if (value < 0 || value > 51)
    throw std::out_of_range("Card value must be 0-51");
}

int Card::getValue() const { return value; }
int Card::getRank() const { return value % 13; }
int Card::getSuit() const { return value / 13; }

std::string Card::rankSymbol() const {
  static const std::string names[] = {"A", "2", "3",  "4", "5", "6", "7",
                                      "8", "9", "10", "J", "Q", "K"};
  return names[getRank()];
}

std::string Card::suitSymbol() const {
  static const std::string symbols[] = {"♣", "♦", "♥", "♠"};
  return symbols[getSuit()];
}

char Card::suitLetter() const { return "CDHS"[getSuit()]; }

bool Card::isRed() const { return getSuit() == 1 || getSuit() == 2; }

std::string Card::toString() const { return rankSymbol() + suitLetter(); }
