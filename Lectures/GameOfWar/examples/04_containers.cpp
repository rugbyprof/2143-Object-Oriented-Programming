#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    int counter = 0;

    auto screen = ScreenInteractive::TerminalOutput();

    // Individual components
    auto increment = Button("Increment", [&] {
        counter++;
    });

    auto decrement = Button("Decrement", [&] {
        counter--;
    });

    auto reset = Button("Reset", [&] {
        counter = 0;
    });

    // Compose components
    auto row = Container::Horizontal({
        increment,
        decrement,
    });

    auto buttons = Container::Vertical({
        row,
        reset,
    });

    // Render the interface
    auto renderer = Renderer(buttons, [&] {
        return vbox({
            text("GameOfWar 04") | bold | center,

            separator(),

            text("Counter: " + std::to_string(counter)) | center,

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
