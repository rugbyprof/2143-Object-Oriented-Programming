#include "poker.hpp"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  Deck deck;

  deck.shuffle();

  int rank = 14;
  int suit = 3;

  std::cout << rankName.at(rank) << "," << suitName.at(suit) << endl;

  Hand hand;

  for (int i = 0; i < 5; i++) {
    hand.addCard(deck.deal());
  }

  cout << deck.size() << endl;
  cout << hand.size() << endl;

  hand.sortHand();

  cout << hand << endl;

  return 0;
}