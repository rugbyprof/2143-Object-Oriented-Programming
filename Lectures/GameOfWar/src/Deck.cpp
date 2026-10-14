#include "Deck.hpp"

#include <algorithm>
#include <random>

Deck::Deck() {
    for (int i = 0; i < 52; i++) {
        cards.push_back(i);
    }
}

int Deck::size() const {
    return static_cast<int>(cards.size());
}

int Deck::draw() {
    if (cards.empty()) {
        return -1;
    }

    int card = cards.back();
    cards.pop_back();

    return card;
}

void Deck::shuffle() {
    static std::mt19937 rng(std::random_device{}());

    std::shuffle(cards.begin(), cards.end(), rng);
}
