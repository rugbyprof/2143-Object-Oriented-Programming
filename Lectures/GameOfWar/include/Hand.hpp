#pragma once

#include <vector>

class Hand {
private:
    std::vector<int> cards;

public:
    int size() const;

    void add(int cardId);
    int getCard(int index) const;
    void clear();

    int removeCard();
};
