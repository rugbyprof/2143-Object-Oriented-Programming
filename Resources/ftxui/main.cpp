#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <array>
#include <string>

using namespace ftxui;

struct Card {
  std::string rank;
  std::string suit;
  bool held = false;
};

Element DrawCard(const Card &card, bool selected) {

  auto suit_color =
      (card.suit == "♥" || card.suit == "♦") ? Color::Red : Color::White;

  auto body = vbox({hbox({text(card.rank), filler(), text(card.suit)}),

                    filler(),

                    text(card.suit) | bold | center,

                    filler(),

                    hbox({text(card.suit), filler(), text(card.rank)})}) |
              color(suit_color) | size(WIDTH, EQUAL, 9) |
              size(HEIGHT, EQUAL, 7);

  // Different border for cursor position.
  if (selected)
    body = body | borderDouble;
  else
    body = body | border;

  // Put HOLD underneath independently of selection.
  return vbox({body, card.held ? text("HOLD") | bold | center : text("    ")});
}

int main() {

  auto screen = ScreenInteractive::Fullscreen();

  std::array<Card, 5> hand = {
      {{"A", "♠"}, {"K", "♥"}, {"Q", "♦"}, {"7", "♣"}, {"2", "♠"}}};

  int selected = 0;
  std::string message = "Select cards to hold";

  auto renderer = Renderer([&] {
    Elements cards;

    for (int i = 0; i < hand.size(); ++i) {

      cards.push_back(DrawCard(hand[i], i == selected));

      // Space between cards.
      if (i != hand.size() - 1)
        cards.push_back(text(" "));
    }

    return vbox({

               text("VIDEO POKER") | bold | center, separator(),
               hbox(std::move(cards)) | center, separator(),
               text(message) | center, separator(),
               hbox({text("← →"), text(" Move    "), text("SPACE"),
                     text(" Hold    "), text("ENTER"), text(" Draw    "),
                     text("Q"), text(" Quit")}) |
                   dim | center

           }) |
           border;
  });

  auto app = CatchEvent(renderer, [&](Event event) {
    // ----------------------------
    // Move cursor
    // ----------------------------

    if (event == Event::ArrowLeft) {

      selected--;

      if (selected < 0)
        selected = 4;

      return true;
    }

    if (event == Event::ArrowRight) {

      selected++;

      if (selected > 4)
        selected = 0;

      return true;
    }

    // ----------------------------
    // Toggle HOLD
    // ----------------------------

    if (event == Event::Character(' ')) {

      hand[selected].held = !hand[selected].held;

      if (hand[selected].held)
        message = hand[selected].rank + hand[selected].suit + " HELD";
      else
        message = hand[selected].rank + hand[selected].suit + " RELEASED";

      return true;
    }

    // ----------------------------
    // Draw
    // ----------------------------

    if (event == Event::Return) {

      message = "Drawing replacement cards...";

      //
      // Eventually:
      //
      // for each card:
      //     if (!held)
      //         replace from deck
      //

      return true;
    }

    // ----------------------------
    // Quit
    // ----------------------------

    if (event == Event::Character('q') || event == Event::Character('Q')) {

      screen.Exit();
      return true;
    }

    return false;
  });

  screen.Loop(app);

  return 0;
}