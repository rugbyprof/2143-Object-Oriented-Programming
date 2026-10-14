#include "WarGame.hpp"

#include <algorithm>
#include <random>
#include <vector>

namespace {

int warValue(int cardId) {
    int rank = cardId % 13;
    return rank == 0 ? 14 : rank + 1;
}

}

WarGame::WarGame()
    : player1("Alice"), player2("Bob") {
}

const Player& WarGame::getPlayer1() const {
    return player1;
}

const Player& WarGame::getPlayer2() const {
    return player2;
}

void WarGame::deal() {
    deck.shuffle();

    for (int i = 0; i < 26; i++) {
        player1.receiveCard(deck.draw());
        player2.receiveCard(deck.draw());
    }

    started = true;
}

void WarGame::reset() {
    deck = Deck();

    player1 = Player("Alice");
    player2 = Player("Bob");

    started = false;
    finished = false;
    draw = false;

    deal();
}

bool WarGame::isGameOver() const {
    if (!started) {
        return false;
    }

    return finished ||
           player1.cardCount() == 0 ||
           player2.cardCount() == 0;
}

bool WarGame::isDraw() const {
    return finished && draw;
}

std::string WarGame::winnerName() const {
    if (!isGameOver()) {
        return "";
    }

    if (isDraw()) {
        return "Draw";
    }

    if (player2.cardCount() == 0) {
        return player1.getName();
    }

    return player2.getName();
}

RoundResult WarGame::playRound() {
    RoundResult result;

    if (!started || isGameOver()) {
        return result;
    }

    std::vector<int> pot;

    while (true) {
        result.card1 = player1.playCard();
        result.card2 = player2.playCard();

        pot.push_back(result.card1);
        pot.push_back(result.card2);

        int value1 = warValue(result.card1);
        int value2 = warValue(result.card2);

        if (value1 > value2) {
            result.winner = 1;
            break;
        }

        if (value2 > value1) {
            result.winner = 2;
            break;
        }

        // Tie: each player places up to three cards face down,
        // then the loop compares another face-up card.
        result.wasWar = true;

        for (int i = 0; i < 3; i++) {
            if (player1.cardCount() > 0) {
                pot.push_back(player1.playCard());
            }

            if (player2.cardCount() > 0) {
                pot.push_back(player2.playCard());
            }
        }

        bool p1CanContinue = player1.cardCount() > 0;
        bool p2CanContinue = player2.cardCount() > 0;

        if (!p1CanContinue && !p2CanContinue) {
            finished = true;
            draw = true;
            break;
        }

        if (!p1CanContinue) {
            result.winner = 2;
            break;
        }

        if (!p2CanContinue) {
            result.winner = 1;
            break;
        }
    }

    result.cardsPlayed = static_cast<int>(pot.size());

    // Without this, the same card order can repeat forever.
    static std::mt19937 rng(std::random_device{}());
    std::shuffle(pot.begin(), pot.end(), rng);

    if (result.winner == 1) {
        for (int id : pot) {
            player1.receiveCard(id);
        }
    }
    else if (result.winner == 2) {
        for (int id : pot) {
            player2.receiveCard(id);
        }
    }

    return result;
}
