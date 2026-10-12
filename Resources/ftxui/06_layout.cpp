// 06_layout: arranging elements with hbox, vbox, filler, size, and borders.
//
// Build:  g++ -std=c++17 06_layout.cpp -I$(brew --prefix ftxui)/include \
//           -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom \
//           -lftxui-screen -o 06_layout
// This one just draws a picture and exits. No event loop needed.

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <iostream>

using namespace ftxui;

// A reusable "tile": a fixed-size box with text in the corners and center.
// Write small functions like this that return an Element, then reuse them.
Element tile(const std::string &corner, const std::string &middle) {
  return vbox({
             hbox({text(corner), filler()}),          // top-left
             filler(),
             text(middle) | bold | center,             // centered
             filler(),
             hbox({filler(), text(corner)}),           // bottom-right
         }) |
         size(WIDTH, EQUAL, 7) | size(HEIGHT, EQUAL, 5) | border;
}

int main() {
  Element page = vbox({
      // hbox: left to right. filler() pushes things apart.
      hbox({text("left"), filler(), text("right")}),
      separator(),

      // hbox of reusable tiles.
      hbox({tile("1", "*"), text(" "), tile("2", "#"), text(" "),
            tile("3", "@")}) | center,
      separator(),

      // Border styles.
      hbox({text("border") | border, text("rounded") | borderRounded,
            text("double") | borderDouble, text("heavy") | borderHeavy,
            text("dashed") | borderDashed}),
      separator(),

      // A titled panel: window(title, content).
      window(text(" Panel ") | bold, vbox({text("line 1"), text("line 2")})),
      separator(),

      // A shaded "back side" made of a repeated character. Wrapping it in
      // an hbox keeps it its natural width instead of stretching.
      hbox({vbox({text("░░░░░"), text("░░░░░"), text("░░░░░")}) |
            color(Color::Blue) | border}),
  });

  // Draw once to the terminal (no ScreenInteractive needed for a static picture).
  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(page));
  Render(screen, page);
  screen.Print();
  std::cout << std::endl;
}
