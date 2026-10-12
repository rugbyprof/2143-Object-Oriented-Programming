// g++ -std=c++20 button.cpp -I$(brew --prefix ftxui)/include -L$(brew --prefix
// ftxui)/lib -lftxui-component -lftxui-dom -lftxui-screen -o button

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

int main() {

  int counter = 0;

  auto button = Button("Click Me", [&] { counter++; });

  auto renderer = Renderer(button, [&] {
    return vbox({text("Counter: " + std::to_string(counter)), separator(),
                 button->Render()});
  });

  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);
}