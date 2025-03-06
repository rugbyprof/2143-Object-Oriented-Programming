#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Card struct and drawCard function from earlier
struct Card {
    string rank;
    string suit;
};

Card getCard(int n) {
    array<string, 13> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    array<string, 4> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};
    int rankIndex = n % 13;
    int suitIndex = n / 13;
    return Card{ranks[rankIndex], suits[suitIndex]};
}

string drawCard(const string &rank, const string &suit) {
    string top_border = "┌─────────┐";
    string bottom_border = "└─────────┘";
    string suitSymbol;

    // Simple suit symbol lookup for demonstration
    if (suit == "Hearts")
        suitSymbol = "\033[31m\u2665\033[0m";
    else if (suit == "Diamonds")
        suitSymbol = "\033[31m\u2666\033[0m";
    else if (suit == "Clubs")
        suitSymbol = "\033[32m\u2663\033[0m";
    else if (suit == "Spades")
        suitSymbol = "\u2660";
    else
        suitSymbol = "?";

    // Adjust spacing for rank "10"
    string left_rank, right_rank;
    if (rank == "10") {
        left_rank = rank;
        right_rank = rank;
    } else {
        left_rank = rank + " ";
        right_rank = " " + rank;
    }

    string line1 = "│" + left_rank + "       │";
    string line2 = "│         │";
    string line3 = "│    " + suitSymbol + "    │";
    string line4 = "│         │";
    string line5 = "│       " + right_rank + "│";

    return top_border + "\n" + line1 + "\n" + line2 + "\n" + line3 + "\n" + line4 + "\n" + line5 + "\n" + bottom_border;
}

// Helper function: split a multi-line string into a vector of strings.
vector<string> splitLines(const string &str) {
    vector<string> lines;
    istringstream iss(str);
    string line;
    while (getline(iss, line)) {
        lines.push_back(line);
    }
    return lines;
}

// Function to print multiple cards horizontally.
// It accepts a vector of card numbers (0-51), draws each card, splits into lines, and prints side-by-side.
void printCardsHorizontally(const vector<int> &cardNumbers) {
    vector<vector<string>> cardLines;

    // Generate each card's lines
    for (int n : cardNumbers) {
        Card c = getCard(n);
        string cardStr = drawCard(c.rank, c.suit);
        cardLines.push_back(splitLines(cardStr));
    }

    // Assume all cards have the same height.
    int numLines = cardLines[0].size();

    // Print corresponding lines from each card, separated by some spaces.
    for (int i = 0; i < numLines; i++) {
        for (const auto &lines : cardLines) {
            cout << lines[i] << "  "; // Two spaces between cards.
        }
        cout << endl;
    }
}

int main() {
    // Example: print cards for indices 0, 10, 25, and 51
    vector<int> cardsToPrint = {0, 10, 25, 51};
    printCardsHorizontally(cardsToPrint);
    return 0;
}