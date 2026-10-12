// 05_show_hide: showing different controls at different times.
//
// Build:  g++ -std=c++17 05_show_hide.cpp -I$(brew --prefix ftxui)/include \
//           -L$(brew --prefix ftxui)/lib -lftxui-component -lftxui-dom \
//           -lftxui-screen -o 05_show_hide
// Use:    click the buttons    q  quit
//
// Maybe(component, &flag) shows a component only while `flag` is true.
// A hidden Maybe also ignores clicks. Without it, a button you stopped
// drawing remembers its old position and can still be "clicked".

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {
  auto screen = ScreenInteractive::TerminalOutput();

  bool showingA = true;     // which set of buttons is visible
  bool showingB = false;
  std::string message = "Screen A";

  // A function stored in a variable, so several buttons can share it.
  auto swap = [&] {
    showingA = !showingA;
    showingB = !showingB;
  };

  auto setA = Container::Horizontal({
      Button("Say hi", [&] { message = "Hi from A"; }),
      Button("Go to B", [&] { swap(); message = "Screen B"; }),
  });
  auto setB = Container::Horizontal({
      Button("Say bye", [&] { message = "Bye from B"; }),
      Button("Back to A", [&] { swap(); message = "Screen A"; }),
  });

  auto all = Container::Vertical({
      Maybe(setA, &showingA),
      Maybe(setB, &showingB),
  });

  auto renderer = Renderer(all, [&] {
    return vbox({
               text(message) | bold,
               separator(),
               all->Render(),   // draws whichever set is visible
               text("q quit") | dim,
           }) |
           border;
  });

  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::Character('q')) { screen.Exit(); return true; }
    return false;
  });

  screen.Loop(app);
}
