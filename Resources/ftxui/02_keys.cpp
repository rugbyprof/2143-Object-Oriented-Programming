// 02_keys: reacting to the keyboard.
//
// Build:  g++ -std=c++17 02_keys.cpp -I$(brew --prefix ftxui)/include \
//           -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom \
//           -lftxui-screen -o 02_keys
// Keys:   ← →  move    1-3  jump to a box    Enter  toggle    q  quit
//
// CatchEvent(component, handler) sees each event before the component does.
// Return true if you used the event, false to let it pass through.
// FTXUI redraws after every event, so changing a variable is all it takes.

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>
#include <vector>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::TerminalOutput();

  int selected = 0;                         // which box the cursor is on
  std::vector<bool> on = {false, false, false};
  std::string lastKey = "(none)";

  auto renderer = Renderer([&] {
    Elements row;
    for (int i = 0; i < 3; i++) {
      Element box = text(on[i] ? " ON  " : " off ");
      box = (i == selected) ? box | borderDouble : box | border;
      row.push_back(box);
    }
    return vbox({
               hbox(row),
               text("last key: " + lastKey) | dim,
               text("← → move   1-3 jump   Enter toggle   q quit") | dim,
           }) |
           border;
  });

  auto app = CatchEvent(renderer, [&](Event e) {
    // Show what came in. e.character() is the typed text, like "a" or "1".
    if (e.is_character())             lastKey = "'" + e.character() + "'";
    else if (e == Event::ArrowLeft)   lastKey = "ArrowLeft";
    else if (e == Event::ArrowRight)  lastKey = "ArrowRight";
    else if (e == Event::Return)      lastKey = "Return";

    // Special keys are named constants.
    if (e == Event::ArrowLeft && selected > 0)  { selected--; return true; }
    if (e == Event::ArrowRight && selected < 2) { selected++; return true; }
    if (e == Event::Return) { on[selected] = !on[selected]; return true; }

    // A range of typed keys: '1' -> 0, '2' -> 1, '3' -> 2.
    if (e.is_character() && e.character() >= "1" && e.character() <= "3") {
      selected = e.character()[0] - '1';
      return true;
    }

    if (e == Event::Character('q')) { screen.Exit(); return true; }
    return false;
  });

  screen.Loop(app);
}
