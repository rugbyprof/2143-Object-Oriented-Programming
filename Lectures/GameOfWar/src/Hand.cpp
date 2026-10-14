#include "Hand.hpp"

int Hand::size() const {
    return static_cast<int>(cards.size());
}

void Hand::add(int cardId) {
    if (cardId >= 0 && cardId < 52) {
        cards.push_back(cardId);
    }
}

int Hand::getCard(int index) const {
    if (index < 0 || index >= size()) {
        return -1;
    }

    return cards[index];
}

void Hand::clear() {
    cards.clear();
}

int Hand::removeCard() {
    if (cards.empty()) {
        return -1;
    }

    int id = cards.front();
    cards.erase(cards.begin());

    return id;
}
