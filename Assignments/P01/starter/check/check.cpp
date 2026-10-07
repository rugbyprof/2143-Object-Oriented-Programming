// Milestone 0 - toolchain check.
// If you can see a box with four colored suits and the arrow keys move
// the highlight, your compiler, CMake, FTXUI, and terminal all work.
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>
#include <vector>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::TerminalOutput();

  std::vector<std::string> suits = {"♣", "♦", "♥", "♠"};
  int selected = 0;

  auto renderer = Renderer([&] {
    Elements row;
    for (int i = 0; i < (int)suits.size(); ++i) {
      Color c = (i == 1 || i == 2) ? Color::Red : Color::White;
      Element card = text(" " + suits[i] + " ") | color(c) | bold;
      row.push_back(i == selected ? card | borderDouble : card | border);
    }
    return vbox({
               text("TOOLCHAIN CHECK: it works!") | bold | center,
               hbox(row) | center,
               text("<- -> move    q quit") | dim | center,
           }) |
           border;
  });

  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::ArrowLeft)  { selected = (selected + 3) % 4; return true; }
    if (e == Event::ArrowRight) { selected = (selected + 1) % 4; return true; }
    if (e == Event::Character('q')) { screen.Exit(); return true; }
    return false;
  });

  screen.Loop(app);
  return 0;
}
