// Milestone 0 - toolchain check.
// If you can see a box with four colored suits and the arrow keys move
// the highlight, your compiler, CMake, FTXUI, and terminal all work.
//
// What this program does:
//   - Draws one row of four "cards", each showing a suit symbol.
//   - Gives the selected card a double-line border and the others a single line.
//   - Left/Right arrows move the selection, and 'q' quits.
//
// What it proves:
//   - The compiler handles modern C++ (lambdas, auto, etc.).
//   - CMake found FTXUI and linked it.
//   - The terminal can show UTF-8 symbols (♣ ♦ ♥ ♠) and colors.
//   - The terminal passes keyboard events through to the program.

// ---------------------------------------------------------------------------
// FTXUI headers
// ---------------------------------------------------------------------------
// FTXUI is split into three layers:
//   dom/       -> "Elements": static things you draw (text, borders, boxes).
//   component/ -> "Components": interactive things that react to input.
//   screen/    -> the terminal canvas (pulled in by the headers below).
#include <ftxui/component/component.hpp>           // Renderer, CatchEvent, Event
#include <ftxui/component/screen_interactive.hpp>  // ScreenInteractive (the event loop)
#include <ftxui/dom/elements.hpp>                  // text, hbox, vbox, border, color, ...

// Standard library headers
#include <string>  // std::string for the suit symbols
#include <vector>  // std::vector to hold the four suits

// Lets us write `text(...)` instead of `ftxui::text(...)`.
// Fine in a small .cpp file like this one. Never put it in a header (.hpp),
// because every file that includes the header would get it too.
using namespace ftxui;

int main() {
  // -------------------------------------------------------------------------
  // 1. Create the screen.
  // -------------------------------------------------------------------------
  // TerminalOutput() draws inline, right where the cursor is, and only uses
  // as many lines as the UI needs. Other options:
  //   ScreenInteractive::Fullscreen()  -> takes over the whole terminal
  //   ScreenInteractive::FitComponent() -> sizes the screen to the component
  auto screen = ScreenInteractive::TerminalOutput();

  // -------------------------------------------------------------------------
  // 2. Program state.
  // -------------------------------------------------------------------------
  // These are the only data the UI depends on. The renderer reads them and
  // the event handler changes them. FTXUI redraws after each event, so
  // changing `selected` is enough to update what's on screen.
  //
  // Suit order: index 0 = clubs, 1 = diamonds, 2 = hearts, 3 = spades.
  // The symbols are UTF-8 strings, not single chars. One symbol takes
  // several bytes, which is why we use std::string and not char.
  std::vector<std::string> suits = {"♣", "♦", "♥", "♠"};

  // Index of the highlighted card (0..3).
  int selected = 0;

  // -------------------------------------------------------------------------
  // 3. The Renderer: a function that turns state into a picture.
  // -------------------------------------------------------------------------
  // Renderer(...) wraps a lambda in a Component. FTXUI calls the lambda each
  // time it needs to redraw, and the lambda returns a fresh Element tree.
  //
  // [&] means "capture by reference". The lambda refers to the real
  // `suits` and `selected` variables in main(), not copies, so it always
  // sees the current value of `selected`.
  auto renderer = Renderer([&] {
    // `Elements` is just std::vector<Element>. We fill it with one Element
    // per card and then lay them out side by side.
    Elements row;

    // The (int) cast avoids a signed/unsigned comparison warning:
    // size() returns size_t, which is unsigned.
    for (int i = 0; i < (int)suits.size(); ++i) {
      // Diamonds (1) and hearts (2) are red; clubs and spades are white.
      Color c = (i == 1 || i == 2) ? Color::Red : Color::White;

      // Build one card. The `|` operator is FTXUI's "decorator" syntax:
      // each `| something` wraps the element on its left in a new style.
      // Read it left to right: text -> colored -> bold.
      // The spaces around the symbol add a bit of padding inside the border.
      Element card = text(" " + suits[i] + " ") | color(c) | bold;

      // The selected card gets a double-line border (╔═╗) and the others get
      // a single-line border (┌─┐). This is the only visual change when you
      // press an arrow key.
      row.push_back(i == selected ? card | borderDouble : card | border);
    }

    // Put everything together and return it:
    //   vbox -> stacks children vertically (top to bottom)
    //   hbox -> lays children out horizontally (left to right)
    //   center -> centers an element in the space it's given
    //   dim    -> draws text faded, good for hints
    // The final `| border` draws a frame around the whole UI.
    return vbox({
               text("TOOLCHAIN CHECK: it works!") | bold | center,  // title
               hbox(row) | center,                                  // the cards
               text("<- -> move    q quit") | dim | center,         // help line
           }) |
           border;
  });

  // -------------------------------------------------------------------------
  // 4. Keyboard handling.
  // -------------------------------------------------------------------------
  // CatchEvent(component, handler) returns a new Component. Every event
  // (key press, mouse, resize, ...) goes to `handler` first.
  //   return true  -> "I handled it", so the event stops here.
  //   return false -> "not mine", so the event goes on to the wrapped
  //                   component (here, `renderer`, which ignores it).
  //
  // This is the Decorator pattern from OOP: wrap an object to add behavior
  // without changing the object itself. `renderer` doesn't know about
  // keys. `app` is a renderer that also handles keys.
  auto app = CatchEvent(renderer, [&](Event e) {
    // Move left with wrap-around. Adding 3 and taking % 4 is the same as
    // subtracting 1 but never goes negative: 0 -> 3, 1 -> 0, 2 -> 1, 3 -> 2.
    // (In C++, (-1) % 4 is -1, not 3, so (selected - 1) % 4 would break.)
    if (e == Event::ArrowLeft)  { selected = (selected + 3) % 4; return true; }

    // Move right with wrap-around: 3 -> 0.
    if (e == Event::ArrowRight) { selected = (selected + 1) % 4; return true; }

    // 'q' tells the screen to leave its event loop, so screen.Loop() below
    // returns. The lambda captured `screen` by reference to make this call.
    if (e == Event::Character('q')) { screen.Exit(); return true; }

    // Ignore any other event.
    return false;
  });

  // -------------------------------------------------------------------------
  // 5. Run the event loop.
  // -------------------------------------------------------------------------
  // Loop() blocks until screen.Exit() is called. Each pass it:
  //   1. waits for an event (key, mouse, resize, ...)
  //   2. sends the event to `app`, which runs our CatchEvent handler
  //   3. calls the renderer to rebuild the Element tree
  //   4. draws the result in the terminal
  // That's why we never call "draw" ourselves. We change state and FTXUI
  // redraws.
  screen.Loop(app);

  // Exit code 0 tells the shell that the program succeeded.
  return 0;
}
