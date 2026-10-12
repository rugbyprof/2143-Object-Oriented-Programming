// 07_input_slider: getting a number or text from the user.
//
// Build:  g++ -std=c++17 07_input_slider.cpp -I$(brew --prefix ftxui)/include \
//           -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom \
//           -lftxui-screen -o 07_input_slider
// Use:    Tab between controls, type in the box, ← → on the slider, Esc quits
//
// Input(&str, placeholder)          a text box that edits `str` directly.
// Slider(label, &value, min, max, step)  edits an int directly.
// Both change your variables for you, so the renderer just reads them.

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::TerminalOutput();

  std::string name;
  int amount = 1;

  auto nameBox = Input(&name, "type your name");
  auto amountSlider = Slider("amount ", &amount, 1, 10, 1);

  auto form = Container::Vertical({nameBox, amountSlider});

  auto renderer = Renderer(form, [&] {
    // Typed text is a string. Convert carefully if you need a number:
    // std::stoi throws on bad input, so wrap it in try/catch.
    return vbox({
               hbox({text("name:   "), nameBox->Render()}),
               amountSlider->Render(),
               separator(),
               text("hello, " + (name.empty() ? std::string("?") : name)),
               text("amount = " + std::to_string(amount)) | bold,
               text("Tab switch   Esc quit") | dim,
           }) |
           border | size(WIDTH, EQUAL, 40);
  });

  // Use Esc to quit here: 'q' is a letter someone might type in the box.
  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::Escape) { screen.Exit(); return true; }
    return false;
  });

  screen.Loop(app);
}
