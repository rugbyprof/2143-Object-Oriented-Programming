#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include "Card.hpp"
#include "HandView.hpp"
#include "WarGame.hpp"
using namespace ftxui;
Element renderPlayedCard(int cardId) {
    if (cardId < 0) {
        return text("No card");
    }
    return renderCard(Card(cardId));
}
int main() {
    WarGame game;
    game.reset();
    Deck deck;
    RoundResult lastRound;
    auto screen = ScreenInteractive::TerminalOutput();
    auto playButton = Button("Play Round", [&] {
        if (!game.isGameOver()) {
            lastRound = game.playRound();
        }
    });
    auto newGameButton = Button("New Game", [&] {
        game.reset();
        lastRound = RoundResult{};
    });
    auto quitButton = Button("Quit", [&] {
        screen.Exit();
    });
    auto buttons = Container::Horizontal({
        playButton,
        newGameButton,
        quitButton,
    });
    auto renderer = Renderer(buttons, [&] {
        std::string status = "Ready to play";
        if (game.isGameOver()) {
            status = "Game Over: " + game.winnerName();
        } else if (lastRound.winner == 1) {
            status = game.getPlayer1().getName() + " wins the round!";
        } else if (lastRound.winner == 2) {
            status = game.getPlayer2().getName() + " wins the round!";
        }
        if (lastRound.wasWar) {
            status += " (WAR!)";
        }
        auto player1Display = vbox({
                                  text(game.getPlayer1().getName()) | bold | center,
                                  text("Cards: " + std::to_string(game.getPlayer1().cardCount())) | center,
                                  renderPlayedCard(lastRound.card1) | center,
                              }) |
                              border;
        auto player2Display = vbox({
                                  text(game.getPlayer2().getName()) | bold | center,
                                  text("Cards: " + std::to_string(game.getPlayer2().cardCount())) | center,
                                  renderPlayedCard(lastRound.card2) | center,
                              }) |
                              border;
        return vbox({
                   text("GAME OF WAR") | bold | center,
                   separator(),
                   hbox({
                       player1Display,
                       text("   VS   ") | vcenter,
                       player2Display,
                   }) | center,
                   separator(),
                   text(status) | center,
                   separator(),
                   buttons->Render() | center,
               }) |
               border;
    });
    screen.Loop(renderer);
}
