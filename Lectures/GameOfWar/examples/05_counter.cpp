#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

class Counter {
private:
    int value;

public:
    Counter() : value(0) {
    }

    void increment() {
        value++;
    }

    void decrement() {
        value--;
    }

    void reset() {
        value = 0;
    }

    int getValue() const {
        return value;
    }
};

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
            text("TinyChunks 05") | bold | center,

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
