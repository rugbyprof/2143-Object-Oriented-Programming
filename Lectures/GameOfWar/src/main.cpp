#include <ftxui/component/animation.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <chrono>
#include <string>
#include "Card.hpp"
#include "HandView.hpp"
#include "WarGame.hpp"
using namespace ftxui;
using Clock = std::chrono::steady_clock;
const auto REVEAL_DELAY = std::chrono::milliseconds(750);
Element renderPlayedCard(int cardId) {
    if (cardId < 0) {
        return text("No card");
    }
    return renderCard(Card(cardId));
}
// Same outer size as renderCard(), so the layout doesn't jump.
// style: 15 is ⠏, style: 12 is ◐◓◑◒, 17 is a [===   ] bar, and 22 is a wave.
Element renderSpinnerCard(int frame) {
    return spinner(12, frame) | center | size(WIDTH, EQUAL, 7) | size(HEIGHT, EQUAL, 5) | border;
}
int main() {
    WarGame game;
    game.reset();
    RoundResult lastRound;
    // While Clock::now() < revealAt, we're "shuffling".
    Clock::time_point revealAt;
    // Card counts from before the round, so they don't spoil the result.
    int shownCount1 = game.getPlayer1().cardCount();
    int shownCount2 = game.getPlayer2().cardCount();
    auto screen = ScreenInteractive::TerminalOutput();
    auto playButton = Button("Play Round", [&] {
        bool revealing = Clock::now() < revealAt;
        if (!game.isGameOver() && !revealing) {
            shownCount1 = game.getPlayer1().cardCount();
            shownCount2 = game.getPlayer2().cardCount();
            lastRound = game.playRound();
            revealAt = Clock::now() + REVEAL_DELAY;
        }
    });
    auto newGameButton = Button("New Game", [&] {
        game.reset();
        lastRound = RoundResult{};
        revealAt = Clock::time_point{};
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
        auto now = Clock::now();
        bool revealing = now < revealAt;
        int frame = 0;
        int count1 = game.getPlayer1().cardCount();
        int count2 = game.getPlayer2().cardCount();
        if (revealing) {
            // Ask FTXUI to draw again on the next frame, so the spinner moves.
            animation::RequestAnimationFrame();
            auto elapsed = now - (revealAt - REVEAL_DELAY);
            frame = static_cast<int>(elapsed / std::chrono::milliseconds(80));
            count1 = shownCount1;
            count2 = shownCount2;
        }
        std::string status = "Ready to play";
        if (revealing) {
            status = "Drawing cards...";
        } else if (game.isGameOver()) {
            status = "Game Over: " + game.winnerName();
        } else if (lastRound.winner == 1) {
            status = game.getPlayer1().getName() + " wins the round!";
        } else if (lastRound.winner == 2) {
            status = game.getPlayer2().getName() + " wins the round!";
        }
        if (lastRound.wasWar && !revealing) {
            status += " (WAR!)";
        }
        auto card1 = revealing ? renderPlayedCard(rand() % 52) : renderPlayedCard(lastRound.card1);
        auto card2 = revealing ? renderPlayedCard(rand() % 52) : renderPlayedCard(lastRound.card2);
        // auto card1 = revealing ? renderSpinnerCard(frame) : renderPlayedCard(lastRound.card1);
        // auto card2 = revealing ? renderSpinnerCard(frame) : renderPlayedCard(lastRound.card2);
        auto player1Display = vbox({
                                  text(game.getPlayer1().getName()) | bold | center,
                                  text("Cards: " + std::to_string(count1)) | center,
                                  card1 | center,
                              }) |
                              border;
        auto player2Display = vbox({
                                  text(game.getPlayer2().getName()) | bold | center,
                                  text("Cards: " + std::to_string(count2)) | center,
                                  card2 | center,
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
