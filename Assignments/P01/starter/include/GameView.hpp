#pragma once

// A GameView is anything that can show a game to a human and collect
// their input. The game itself must NOT know which view is being used.
//
// You will write (at least) two views:
//   ConsoleView - plain cout/cin, ASCII only, no FTXUI
//   TuiView     - the FTXUI terminal interface
//
// main() picks one at run time and only ever talks to it through a
// GameView pointer. That is the polymorphism part of this assignment.
class GameView {
public:
  virtual ~GameView() = default;
  virtual void run() = 0; // play until the user quits
};
