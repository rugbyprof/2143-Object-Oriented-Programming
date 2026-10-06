#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<string> Rank = {"",     "Two",   "Three", "Four", "Five",
                       "Six",  "Seven", "Eight", "Nine", "Ten",
                       "Jack", "Queen", "King",  "Ace"};
vector<string> Suit = {"Clubs", "Diamonds", "Hearts", "Spades"};

////////////////////////////////////////////////////////////////////////////////////

std::map<int, std::string> rankName = {
    {2, "2"}, {3, "3"},   {4, "4"},  {5, "5"},  {6, "6"},  {7, "7"}, {8, "8"},
    {9, "9"}, {10, "10"}, {11, "J"}, {12, "Q"}, {13, "K"}, {14, "A"}};

std::map<int, std::string> suitName = {{0, "♣"}, {1, "♦"}, {2, "♥"}, {3, "♠"}};

////////////////////////////////////////////////////////////////////////////////////

enum class Suit { Clubs, Diamonds, Hearts, Spades };

enum class Rank {
  Two = 2,
  Three,
  Four,
  Five,
  Six,
  Seven,
  Eight,
  Nine,
  Ten,
  Jack,
  Queen,
  King,
  Ace,
};
////////////////////////////////////////////////////////////////////////////////////

/*****************************************************************
   ___   _   ___ ___     ___ _      _   ___ ___
  / __| /_\ | _ \   \   / __| |    /_\ / __/ __|
 | (__ / _ \|   / |) | | (__| |__ / _ \\__ \__ \
  \___/_/ \_\_|_\___/   \___|____/_/ \_\___/___/
*****************************************************************/
class Card {
private:
  int value; // 0-51

public:
  Card(int value = 0);

  int getValue() const;
  int getRank() const;
  int getSuit() const;

  std::string getRankName() const;
  std::string getSuitName() const;
  //   std::string toString() const;
};

string Card::getRankName() const { return Rank[getRank()]; }
string Card::getSuitName() const { return Suit[getSuit()]; }

Card::Card(int v) { value = v; }

int Card::getRank() const { return value % 13; }

int Card::getSuit() const { return value / 13; }

int Card::getValue() const { return value; }

/*****************************************************************
  ___  ___ ___ _  __   ___ _      _   ___ ___
 |   \| __/ __| |/ /  / __| |    /_\ / __/ __|
 | |) | _| (__| ' <  | (__| |__ / _ \\__ \__ \
 |___/|___\___|_|\_\  \___|____/_/ \_\___/___/
******************************************************************/

class Deck {
private:
  std::vector<Card> deck;

public:
  Deck();

  void shuffle();
  Card deal();
  bool empty() const;
  int size() const;
};

Deck::Deck() {
  for (int i = 0; i < 52; i++) {
    deck.push_back(Card(i));
  }
}

void Deck::shuffle() {
  static std::random_device rd;
  static std::mt19937 gen(rd());

  std::shuffle(deck.begin(), deck.end(), gen);
}

Card Deck::deal() {
  Card card = deck.back();
  deck.pop_back();
  return card;
}

bool Deck::empty() const { return deck.size() == 0; }
int Deck::size() const { return deck.size(); }

/*****************************************************************
  _  _   _   _  _ ___     ___ _      _   ___ ___
 | || | /_\ | \| |   \   / __| |    /_\ / __/ __|
 | __ |/ _ \| .` | |) | | (__| |__ / _ \\__ \__ \
 |_||_/_/ \_\_|\_|___/   \___|____/_/ \_\___/___/
******************************************************************/

class Hand {
private:
  std::vector<Card> hand;

public:
  void sortHand();
  void addCard(const Card &card);
  void clear();

  int size() const;
  void show() const;

  friend ostream &operator<<(ostream &os, const Hand &h) {
    for (auto &c : h.hand) {
      os << "[" << c.getRank() << "," << c.getSuit() << "]";
    }
    return os;
  }
};

void Hand::addCard(const Card &card) { hand.push_back(card); }

void Hand::clear() { hand.clear(); }

int Hand::size() const { return hand.size(); }

void Hand::sortHand() {
  std::sort(hand.begin(), hand.end(), [](const Card &a, const Card &b) {
    return a.getRank() > b.getRank();
  });
}

void Hand::show() const {
  for (auto &c : hand) {
    cout << "[" << c.getRank() << "," << c.getSuit() << "," << c.getValue()
         << "]";
  }
}