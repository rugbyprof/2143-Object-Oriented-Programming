#include "Deck.hpp"

#include <algorithm>
#include <random>
#include <stdexcept>

Deck::Deck() { reset(); }

Deck::Deck(const std::vector<Card> &stacked)
    : cards(stacked.rbegin(), stacked.rend()) {}

void Deck::reset() {
  cards.clear();
  for (int i = 0; i < 52; i++)
    cards.push_back(Card(i));
}

void Deck::shuffle() {
  static std::mt19937 gen{std::random_device{}()};
  std::shuffle(cards.begin(), cards.end(), gen);
}

Card Deck::deal() {
  if (cards.empty())
    throw std::runtime_error("Cannot deal from an empty deck");
  Card top = cards.back();
  cards.pop_back();
  return top;
}

bool Deck::empty() const { return cards.empty(); }
int Deck::size() const { return (int)cards.size(); }
