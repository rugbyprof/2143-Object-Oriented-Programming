#pragma once

// THE GAME (the "model").
// Knows the rules and remembers the state. Has no idea whether it is
// being shown with cout, FTXUI, or nothing at all (tests).
// Notice: no <iostream>, no FTXUI includes.

#include "Card.hpp"
#include "Deck.hpp"

enum class Guess { Higher, Lower };
enum class Phase { Guessing, GameOver };
enum class Result { None, Correct, Wrong, Tie };

class HiLo {
private:
  // --- STATE: everything the game must remember ---
  Deck deck_;
  Card current_;
  Card previous_;
  int score_ = 0;
  int lives_ = 3;
  Phase phase_ = Phase::Guessing;
  Result last_ = Result::None;

  void start(); // shared by both constructors and restart()

public:
  HiLo();                             // shuffled deck: real games
  explicit HiLo(const Deck &stacked); // stacked deck: tests

  // --- ACTIONS: things the player can ask for ---
  // Each returns false (and changes nothing) if not allowed right now.
  bool guess(Guess g);
  bool restart();

  // --- QUESTIONS: what a view needs to draw the screen ---
  Phase phase() const;
  const Card &currentCard() const;
  const Card &previousCard() const;
  int score() const;
  int lives() const;
  Result lastResult() const;
  int cardsLeft() const;
};
