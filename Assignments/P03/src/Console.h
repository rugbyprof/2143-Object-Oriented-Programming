#pragma once

#include <iostream>
#include <string>

#include <ftxui/dom/elements.hpp>   // text, hbox, color, bold, ...
#include <ftxui/screen/screen.hpp>  // Screen, Render

// -----------------------------------------------------------------------
// Console — colored terminal output with FTXUI.  (provided)
//
// In P01 you used FTXUI to draw an interactive screen. Here we only use
// its drawing half: build one Element, render it, print it, done.
//
// 'inline' lets a function be DEFINED in a header that several .cpp files
// include. Without it, every .cpp that includes this header would get its
// own copy, and the linker would fail with "duplicate symbol printLine".
//
// Why every name is written ftxui::something:
//   FTXUI has its own classes named ftxui::Image and ftxui::Color. This
//   project has an Image class (and gets a Color class in P04). With
//   'using namespace ftxui;' the compiler would see two Images and stop:
//       error: reference to 'Image' is ambiguous
//   So FTXUI stays inside this one header, fully qualified, and the rest
//   of the program calls the small helpers below. That is exactly the
//   problem namespaces exist to solve.
// -----------------------------------------------------------------------

// Draws one FTXUI element and prints it, followed by a newline.
// Sends output to std::cout unless you pass std::cerr.
inline void printLine(ftxui::Element line, std::ostream& out = std::cout) {
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(line));
    ftxui::Render(screen, line);
    out << screen.ToString() << "\n";
}

// "Error: <msg>" with a bold red label, to std::cerr.
inline void printError(const std::string& msg) {
    printLine(ftxui::hbox({
        ftxui::text("Error: ") | ftxui::color(ftxui::Color::Red) | ftxui::bold,
        ftxui::text(msg),
    }), std::cerr);
}

// "Warning: <msg>" with a yellow label, to std::cerr.
inline void printWarning(const std::string& msg) {
    printLine(ftxui::hbox({
        ftxui::text("Warning: ") | ftxui::color(ftxui::Color::Yellow),
        ftxui::text(msg),
    }), std::cerr);
}

// The usage line, to std::cerr.
inline void printUsage() {
    printLine(ftxui::hbox({
        ftxui::text("Usage: ") | ftxui::color(ftxui::Color::Red),
        ftxui::text("./imgtool <input_image> <output_image> [options]")
            | ftxui::color(ftxui::Color::Blue),
    }), std::cerr);
}

// "<label> <value>" with a green label and yellow value, to std::cout.
// Example: printStatus("Saved:", "out.png");
inline void printStatus(const std::string& label, const std::string& value) {
    printLine(ftxui::hbox({
        ftxui::text(label + " ") | ftxui::color(ftxui::Color::Green),
        ftxui::text(value) | ftxui::color(ftxui::Color::Yellow),
    }));
}
