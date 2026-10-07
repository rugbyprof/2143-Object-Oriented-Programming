#pragma once

#include "GameView.hpp"
#include "HiLo.hpp"

// A VIEW: shows the game with cout, reads commands with getline.
class ConsoleView : public GameView {
private:
  HiLo &game; // uses the game, does not own it

  void showState() const;

public:
  explicit ConsoleView(HiLo &game);
  void run() override;
};
