#include "TuiView.hpp"

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <string>

using namespace ftxui;

// Drawing ONE card is pure presentation, so it lives in the view file.
static Element drawCard(const Card &card) {
  Color c = card.isRed() ? Color::Red : Color::White;
  return vbox({
             hbox({text(card.rankSymbol()), filler()}),
             filler(),
             text(card.suitSymbol()) | bold | center,
             filler(),
             hbox({filler(), text(card.rankSymbol())}),
         }) |
         color(c) | size(WIDTH, EQUAL, 9) | size(HEIGHT, EQUAL, 7) | border;
}

static std::string resultText(Result r) {
  switch (r) {
  case Result::Correct: return "Correct!";
  case Result::Wrong:   return "Wrong!";
  case Result::Tie:     return "Tie - no harm done.";
  case Result::None:    return "Will the next card be higher or lower?";
  }
  return "";
}

TuiView::TuiView(HiLo &game) : game(game) {}

void TuiView::run() {
  auto screen = ScreenInteractive::TerminalOutput();

  // RENDERER: only READS from the game. It never changes anything.
  auto renderer = Renderer([&] {
    std::string hearts;
    for (int i = 0; i < game.lives(); i++)
      hearts += "♥ ";

    Element previous = game.lastResult() == Result::None
                           ? text("")
                           : vbox({text("was") | dim | center,
                                   drawCard(game.previousCard()) | dim});

    std::string keys = game.phase() == Phase::GameOver
                           ? "r  play again    q  quit"
                           : "↑ higher    ↓ lower    q  quit";

    return vbox({
               text("HI-LO") | bold | center,
               separator(),
               hbox({previous, text("   "),
                     vbox({text("now") | center, drawCard(game.currentCard())})}) |
                   center,
               separator(),
               text(game.phase() == Phase::GameOver
                        ? "GAME OVER - final score " + std::to_string(game.score())
                        : resultText(game.lastResult())) |
                   bold | center,
               hbox({text("Score: " + std::to_string(game.score())), filler(),
                     text(hearts) | color(Color::Red), filler(),
                     text("Cards left: " + std::to_string(game.cardsLeft()))}),
               separator(),
               text(keys) | dim | center,
           }) |
           border | size(WIDTH, EQUAL, 44);
  });

  // EVENT HANDLER: each key becomes ONE call into the game. No rules here.
  auto app = CatchEvent(renderer, [&](Event e) {
    if (e == Event::ArrowUp)        return game.guess(Guess::Higher);
    if (e == Event::ArrowDown)      return game.guess(Guess::Lower);
    if (e == Event::Character('r')) return game.restart();
    if (e == Event::Character('q')) { screen.Exit(); return true; }
    return false;
  });

  screen.Loop(app);
}
