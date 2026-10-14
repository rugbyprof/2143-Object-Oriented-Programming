#pragma once

#include <vector>

class Deck {
private:
    std::vector<int> cards;

public:
    Deck();

    int size() const;
    int draw();
    void shuffle();
};
