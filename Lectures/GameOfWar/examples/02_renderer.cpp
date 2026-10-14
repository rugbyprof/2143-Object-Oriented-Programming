#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    int counter = 0;

    auto screen = ScreenInteractive::TerminalOutput();

    auto renderer = Renderer([&] {
        return vbox({
            text("GameOfWar 02") | bold,
            separator(),
            text("Counter: " + std::to_string(counter)),
        }) | border;
    });

    counter = 100;

    screen.Loop(renderer);
}
