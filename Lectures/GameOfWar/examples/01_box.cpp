#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <iostream>

using namespace ftxui;

int main() {

    Element document = vbox({
        text("TinyChunks 01") | bold | center,

        separator(),

        hbox({
            text("Left") | border,
            text("Middle") | border | flex,
            text("Right") | border,
        }),

        separator(),

        text("Static screens are drawn once.") | color(Color::Green),

    }) | border;

    auto screen = Screen::Create(
        Dimension::Fixed(40),
        Dimension::Fit(document)
    );

    Render(screen, document);
    screen.Print();

    std::cout << '\n';
}
