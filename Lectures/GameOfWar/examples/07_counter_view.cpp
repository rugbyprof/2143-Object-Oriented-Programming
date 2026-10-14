#include "Counter.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

class CounterView {
private:
    Counter& counter;

    Component increment;
    Component decrement;
    Component reset;

public:
    CounterView(Counter& c) : counter(c) {

        increment = Button("Increment", [this] {
            counter.increment();
        });

        decrement = Button("Decrement", [this] {
            counter.decrement();
        });

        reset = Button("Reset", [this] {
            counter.reset();
        });
    }

    Component build() {

        auto row = Container::Horizontal({
            increment,
            decrement,
        });

        auto buttons = Container::Vertical({
            row,
            reset,
        });

        return Renderer(buttons, [this] {
            return vbox({
                text("GameOfWar 07") | bold | center,

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
    }
};

int main() {

    Counter counter;

    CounterView view(counter);

    auto screen = ScreenInteractive::TerminalOutput();

    screen.Loop(view.build());
}
