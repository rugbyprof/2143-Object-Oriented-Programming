#include "Player.hpp"

Player::Player(const std::string& name)
    : name(name) {
}

std::string Player::getName() const {
    return name;
}

int Player::cardCount() const {
    return hand.size();
}

void Player::receiveCard(int cardId) {
    hand.add(cardId);
}

int Player::playCard() {
    return hand.removeCard();
}

const Hand& Player::getHand() const {
    return hand;
}
