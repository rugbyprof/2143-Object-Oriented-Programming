#pragma once

#include <string>

#include "Deck.hpp"
#include "Player.hpp"

struct RoundResult {
    int card1 = -1;
    int card2 = -1;
    int winner = 0;
    int cardsPlayed = 0;
    bool wasWar = false;
};

class WarGame {
private:
    Deck deck;
    Player player1;
    Player player2;

    bool started = false;
    bool finished = false;
    bool draw = false;

public:
    WarGame();

    void deal();
    void reset();

    RoundResult playRound();

    bool isGameOver() const;
    bool isDraw() const;
    std::string winnerName() const;

    const Player& getPlayer1() const;
    const Player& getPlayer2() const;
};
