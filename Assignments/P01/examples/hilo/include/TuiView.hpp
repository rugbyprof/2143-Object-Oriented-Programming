#pragma once

#include "GameView.hpp"
#include "HiLo.hpp"

// A VIEW: shows the same game with FTXUI.
class TuiView : public GameView {
private:
  HiLo &game;

public:
  explicit TuiView(HiLo &game);
  void run() override;
};
