#include "termio.h"
#include <iostream>
#include <string>

using namespace std;


const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4] = {"♠", "♦", "♣", "♥"};
const string colors[4] = {"&60", "&20", "&60", "&20"};
//const string colors[4] = {"&16", "&12", "&16", "&12"};
const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

class Card {
private:
    int suitNum;        // value 0-3 : num index of suit
    int rank;           // 0-13      : num value of rank
    int number;         // 1-52      : unique value determines card
    int value;          // 1-14      : numeric value used for comparison         
    string suitChar;    // "♠", "♦", "♣", "♥"
    string rankChar;    // Ace, 1 ,2 ,3 ... Q, K
    string color;       // Spade=blue, Diamond=red, etc.

public:
    /**
     * Public : Card
     * 
     * Description:
     *      Represents a single card in a deck of cards to include a 
     *      value along with rank and suit. We are assuming a standard
     *      card type in a deck of playing cards.
     * 
     * Params:
     *      int :  value from 0 - 51 that represents a card in a deck.
     * 
     * Returns:
     *      None
     */
    Card(int num) {
        number = num;
        suitNum = number / 13;
        suitChar = suits[suitNum];
        color = colors[suitNum];
        rank = number % 13;
        rankChar = ranks[rank];
    }

    /**
     * Public : Repr
     * 
     * Description:
     *      Returns a string representation of the card class with 
     *      colors embedded. 
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      [string] - representation of card
     */
    string Repr() {
        string s = "";
        s += color + "┌────┐&00 \n";
        s += color + "│";
        if (rank != 9) {
            s += color + " ";
        }
        s += color + rankChar + " " + suitChar + "│&00 \n";
        s += color + "└────┘&00 ";
        return s;
    }

    /**
     * Public : operator <<
     * 
     * Description:
     *      Overload ostream and send the string representation "Repr"
     *      of the card. 
     * 
     * Params:
     *      [ostream&] : os 
     *      [Card]     : obj
     * 
     * Returns:
     *      [ostream&]
     */
    friend ostream &operator<<(ostream &os, Card obj) {

        os << obj.Repr();

        return os;
    }

    bool operator<(const Card& rhs){
        return this->rank < rhs.rank;
    }

    bool operator>(const Card& rhs){
        return this->rank > rhs.rank;
    }

    bool operator==(const Card& rhs){
        return this->rank == rhs.rank;
    }


};

class Deck {
    // dealCard
    // shuffleCards
    // resetDeck
};

class Hand {
};

class Game {
};

int main() {
    Term::IO io;
    Card *cards[52];

    // for (int i = 0; i < 52; i++) {
    //     cards[i] = new Card(i);
    //     io << Term::clear;
    //     io << cards[i]->Repr() << "\n";
    //     io << Term::sleep(100);
    // }

    for (int i = 0; i < 100; i++) {
        Card c1(rand() % 52);
        Card c2(rand() % 52);
        Card c3(rand() % 52);
        Card c4(rand() % 52);
        Card c5(rand() % 52);
        io << Term::clear;
        io << Term::fuse({c1.Repr(),c2.Repr(), c3.Repr(), c4.Repr(), c5.Repr()}) << "\n";
        io << Term::sleep(100);
    }

    //io<<Term::Point(5,0);

    return 0;
}