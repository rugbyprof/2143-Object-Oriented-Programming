// 04_buttons: a row of buttons, each running a function when clicked.
//
// Build:  g++ -std=c++17 04_buttons.cpp -I$(brew --prefix ftxui)/include \
//           -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom \
//           -lftxui-screen -o 04_buttons
// Use:    click, or Tab / arrows + Enter    q  quit
//
// Button(label, function, style) calls `function` on each click.
// Buttons only get clicks and focus if they are inside a Container, and
// that Container is passed to Renderer(...).

#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::TerminalOutput();
  int value = 0;

  // A few built-in looks. Animated() changes color when focused/hovered.
  auto minus = Button(" - ", [&] { value--; }, ButtonOption::Animated(Color::Red));
  auto plus  = Button(" + ", [&] { value++; }, ButtonOption::Animated(Color::Green));
  auto reset = Button("Reset", [&] { value = 0; }, ButtonOption::Ascii());
  auto big   = Button("Default style", [&] { value += 10; });

  auto buttons = Container::Horizontal({minus, plus, reset, big});

  auto renderer = Renderer(buttons, [&] {
    return vbox({
               text("value: " + std::to_string(value)) | bold,
               separator(),
               // Draw each button wherever you want it. The styles have
               // different heights, so vcenter lines up the short one.
               hbox({minus->Render(), text(" "), plus->Render(), text(" "),
                     reset->Render() | vcenter, text(" "), big->Render()}),
               text("click, or Tab + Enter    q quit") | dim,
           }) |
           border;
  });

  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::Character('q')) { screen.Exit(); return true; }
    return false;
  });

  screen.Loop(app);
}
