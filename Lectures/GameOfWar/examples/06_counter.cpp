#include "Counter.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    Counter counter;

    auto screen = ScreenInteractive::TerminalOutput();

    auto increment = Button("Increment", [&] {
        counter.increment();
    });

    auto decrement = Button("Decrement", [&] {
        counter.decrement();
    });

    auto reset = Button("Reset", [&] {
        counter.reset();
    });

    auto row = Container::Horizontal({
        increment,
        decrement,
    });

    auto buttons = Container::Vertical({
        row,
        reset,
    });

    auto renderer = Renderer(buttons, [&] {
        return vbox({
            text("GameOfWar 06") | bold | center,

            separator(),

            text("Counter: " + std::to_string(counter.getValue())) | center,

            separator(),

            hbox({
                increment->Render(),
                text("  "),
                decrement->Render(),
            }) | center,

            separatorEmpty(),

            reset->Render() | center,

        }) | border;
    });

    screen.Loop(renderer);
}
