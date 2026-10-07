#include "HiLo.hpp"

HiLo::HiLo() {
  deck_.shuffle();
  start();
}

HiLo::HiLo(const Deck &stacked) : deck_(stacked) { start(); }

void HiLo::start() {
  current_ = deck_.deal();
  previous_ = current_;
  score_ = 0;
  lives_ = 3;
  phase_ = Phase::Guessing;
  last_ = Result::None;
}

bool HiLo::guess(Guess g) {
  if (phase_ != Phase::Guessing) // the GAME enforces turn order,
    return false;                // not the view

  previous_ = current_;
  current_ = deck_.deal();

  int before = previous_.getRank(); // Ace is low (0)
  int after = current_.getRank();

  if (after == before) {
    last_ = Result::Tie; // ties cost nothing
  } else if ((g == Guess::Higher) == (after > before)) {
    last_ = Result::Correct;
    score_++;
  } else {
    last_ = Result::Wrong;
    lives_--;
  }

  if (lives_ == 0 || deck_.empty())
    phase_ = Phase::GameOver;
  return true;
}

bool HiLo::restart() {
  if (phase_ != Phase::GameOver)
    return false;
  deck_.reset();
  deck_.shuffle();
  start();
  return true;
}

Phase HiLo::phase() const { return phase_; }
const Card &HiLo::currentCard() const { return current_; }
const Card &HiLo::previousCard() const { return previous_; }
int HiLo::score() const { return score_; }
int HiLo::lives() const { return lives_; }
Result HiLo::lastResult() const { return last_; }
int HiLo::cardsLeft() const { return deck_.size(); }
