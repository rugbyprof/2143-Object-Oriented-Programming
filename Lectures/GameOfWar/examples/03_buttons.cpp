#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

int main() {

    // Application state
    int counter = 0;

    // Interactive terminal
    auto screen = ScreenInteractive::TerminalOutput();

    // Interactive component
    auto button = Button("Increment", [&] {
        counter++;
    });

    // Renderer with button as child
    auto renderer = Renderer(button, [&] {
        return vbox({
            text("TinyChunks 03") | bold,

            separator(),

            text("Counter: " + std::to_string(counter)),

            separator(),

            button->Render(),

        }) | border;
    });

    // Start event loop
    screen.Loop(renderer);
}
