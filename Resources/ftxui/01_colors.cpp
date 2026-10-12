// 01_colors: text styles and colors.
//
// Build:  g++ -std=c++17 01_colors.cpp -I$(brew --prefix ftxui)/include \
//           -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom \
//           -lftxui-screen -o 01_colors
// Keys:   ← →  change the number    q  quit

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

// Pick a color based on a value. The decision is just an if statement.
Color colorFor(int n) {
  if (n >= 50) return Color::Green;
  if (n >= 20) return Color::Yellow;
  return Color::Red;
}

int main() {
  auto screen = ScreenInteractive::TerminalOutput();
  int number = 50;

  auto renderer = Renderer([&] {
    return vbox({
               // Decorators are applied with `|`, read left to right.
               hbox({text("bold") | bold, text("  "),
                     text("dim") | dim, text("  "),
                     text("underlined") | underlined, text("  "),
                     text("inverted") | inverted}),
               separator(),

               // Text (foreground) colors.
               hbox({text("Red ") | color(Color::Red),
                     text("Green ") | color(Color::Green),
                     text("Blue ") | color(Color::Blue),
                     text("Yellow ") | color(Color::Yellow),
                     text("Cyan ") | color(Color::Cyan),
                     text("Magenta") | color(Color::Magenta)}),
               separator(),

               // Background colors. Color::RGB(r, g, b) picks an exact color.
               hbox({text(" bgcolor ") | bgcolor(Color::Blue),
                     text(" "),
                     text(" RGB ") | bgcolor(Color::RGB(255, 140, 0)) |
                         color(Color::Black)}),
               separator(),

               // Decorators combine: color + bold + border, all at once.
               hbox({text(" styled box ") | color(Color::Cyan) | bold | border}),
               separator(),

               // A color that depends on a variable.
               hbox({text("number: "),
                     text(std::to_string(number)) | bold |
                         color(colorFor(number))}),
               text("← → change    q quit") | dim,
           }) |
           border;
  });

  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::ArrowLeft)  { number -= 5; return true; }
    if (e == Event::ArrowRight) { number += 5; return true; }
    if (e == Event::Character('q')) { screen.Exit(); return true; }
    return false;
  });

  screen.Loop(app);
}
