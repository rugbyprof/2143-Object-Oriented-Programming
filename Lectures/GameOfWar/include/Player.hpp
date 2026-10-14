#pragma once

#include <string>

#include "Hand.hpp"

class Player {
private:
    std::string name;
    Hand hand;

public:
    Player(const std::string& name);

    std::string getName() const;
    int cardCount() const;

    void receiveCard(int cardId);
    int playCard();

    const Hand& getHand() const;
};
