#pragma once

#include <string>

class Card {
private:
    int id;

public:
    Card(int id = 0);

    int getId() const;
    int getSuit() const;
    int getRank() const;

    std::string rankName() const;
    std::string suitName() const;
    std::string toString() const;

    void setId(int newId);
};
