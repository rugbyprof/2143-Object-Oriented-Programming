// 03_mouse: clicking on any element, not just buttons.
//
// Build:  g++ -std=c++17 03_mouse.cpp -I$(brew --prefix ftxui)/include \
//           -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom \
//           -lftxui-screen -o 03_mouse
// Use:    click a box to change its color    q  quit
//
// Two steps:
//   1. While drawing:  element | reflect(box)   FTXUI writes where it drew
//                                               the element into `box`.
//   2. On a click:     box.Contain(x, y)        was the click inside it?
// The Box variables must live OUTSIDE the render lambda so they survive
// between drawing and clicking.

#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/box.hpp>

#include <string>
#include <vector>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::TerminalOutput();

  std::vector<std::string> labels = {"one", "two", "three"};
  std::vector<bool> clicked(3, false);
  std::vector<Box> boxes(3);   // filled in by reflect() each frame
  std::string status = "click a box";

  auto renderer = Renderer([&] {
    Elements row;
    for (int i = 0; i < 3; i++) {
      Element e = text(" " + labels[i] + " ") | border;
      if (clicked[i]) e = e | color(Color::Green);
      row.push_back(e | reflect(boxes[i]));
    }
    return vbox({hbox(row), text(status) | dim, text("q quit") | dim}) | border;
  });

  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::Character('q')) { screen.Exit(); return true; }
    if (!e.is_mouse()) return false;

    Mouse m = e.mouse();   // m.x, m.y, m.button, m.motion
    status = "mouse at (" + std::to_string(m.x) + ", " + std::to_string(m.y) + ")";

    // Mouse moves arrive too. Only act on a left-button press.
    if (m.button != Mouse::Left || m.motion != Mouse::Pressed) return false;

    for (int i = 0; i < 3; i++) {
      if (boxes[i].Contain(m.x, m.y)) {
        clicked[i] = !clicked[i];
        status = "clicked " + labels[i];
        return true;
      }
    }
    return false;
  });

  screen.Loop(app);
}
