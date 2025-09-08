#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

#ifdef _WIN32
// Function to enable Virtual Terminal Processing for ANSI escape sequences on Windows 10+
void enableAnsiEscapeSequences() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

#define RESET "\033[0m"
#define BACK "\033[1;34m"

// Create an unordered_map to hold the ANSI escape sequences.
unordered_map<string, string> colors = {
    // Foreground colors
    {"fg_black", "\033[30m"},
    {"fg_red", "\033[31m"},
    {"fg_green", "\033[32m"},
    {"fg_yellow", "\033[33m"},
    {"fg_blue", "\033[34m"},
    {"fg_magenta", "\033[35m"},
    {"fg_cyan", "\033[36m"},
    {"fg_white", "\033[37m"},

    // Bold Foreground colors
    {"fg_black_bold", "\033[1;30m"},
    {"fg_red_bold", "\033[1;31m"},
    {"fg_green_bold", "\033[1;32m"},
    {"fg_yellow_bold", "\033[1;33m"},
    {"fg_blue_bold", "\033[1;34m"},
    {"fg_magenta_bold", "\033[1;35m"},
    {"fg_cyan_bold", "\033[1;36m"},
    {"fg_white_bold", "\033[1;37m"},

    // Background colors
    {"bg_black", "\033[40m"},
    {"bg_red", "\033[41m"},
    {"bg_green", "\033[42m"},
    {"bg_yellow", "\033[43m"},
    {"bg_blue", "\033[44m"},
    {"bg_magenta", "\033[45m"},
    {"bg_cyan", "\033[46m"},
    {"bg_white", "\033[47m"}};

unordered_map<string, string> suitSymbols = {
    {"hearts", colors["fg_red_bold"] + "\u2665" + RESET}, // ♥ in red
    {"diamonds", "\033[31m\u2666\033[0m"},                // ♦ in red
    {"clubs", "\033[32m\u2663\033[0m"},                   // ♣ in green
    {"spades", "\033[35m\u2660\033[0m"}                   // ♠ in blue (or default if preferred)
};

unordered_map<string, string> suitSymbols2 = {
    {"hearts", "\033[31m\u2665\033[0m"},   // ♥ in red
    {"diamonds", "\033[31m\u2666\033[0m"}, // ♦ in red
    {"clubs", "\033[32m\u2663\033[0m"},    // ♣ in green
    {"spades", "\033[35m\u2660\033[0m"}    // ♠ in blue (or default if preferred)
};

unordered_map<std::string, std::string> faceCards = {
    // Or, using chess pieces / letters as alternatives:
    {"K", "K"}, // King "♔"
    {"Q", "Q"}, // Queen "♕"
    {"J", "J"}, // Jack (or even "♘" if you want to be creative)
    {"A", "A"}};

// Define a struct to represent a card
struct Card {
    string rank;
    string suit;
};

// Function that takes an integer n (0-51) and returns the corresponding card
Card getCard(int n) {
    // Lookup arrays for ranks and suits
    array<string, 13> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    array<string, 4> suits = {"clubs", "diamonds", "hearts", "spades"};

    // Calculate rank and suit indices using mod and div
    int rankIndex = n % 13; // Gives a value between 0 and 12
    int suitIndex = n / 13; // Gives a value between 0 and 3

    return Card{ranks[rankIndex], suitSymbols[suits[suitIndex]]};
}

string getSuitSymbol(const string &suit) {
    auto it = suitSymbols.find(suit);
    return (it != suitSymbols.end()) ? it->second : suit;
}

string getFaceSymbol(const string &face) {
    auto it = faceCards.find(face);
    return (it != faceCards.end()) ? it->second : face;
}

// Draws a card with a Unicode border, rank, and colored suit symbol.
string drawCard(const string &rank, const string &suit) {
    string top_border = "┌─────────┐";
    string bottom_border = "└─────────┘";
    string suitSymbol = getSuitSymbol(suit);

    // Adjust spacing for rank "10" (which uses 2 characters)
    string left_rank, right_rank;
    if (rank == "10") {
        left_rank = rank;
        right_rank = rank;
    } else if (rank == "J" || rank == "Q" || rank == "K" || rank == "A") {
        left_rank = getFaceSymbol(rank) + " ";
        right_rank = " " + getFaceSymbol(rank);
    } else {
        left_rank = rank + " ";
        right_rank = " " + rank;
    }

    string line1 = "│" + left_rank + "       │";
    string line2 = "│   " + suitSymbol + suitSymbol + suitSymbol + "   │";
    string line3 = "│   " + suitSymbol + suitSymbol + suitSymbol + "   │";
    string line4 = "│   " + suitSymbol + suitSymbol + suitSymbol + "   │";
    string line5 = "│       " + right_rank + "│";

    return top_border + "\n" + line1 + "\n" + line2 + "\n" + line3 + "\n" + line4 + "\n" + line5 + "\n" + bottom_border;
}

string drawCardBack(string color = BACK) {
    string top_border = "┌─────────┐";
    string bottom_border = "└─────────┘";
    string line1 = "│" + color + " ▓▓▓░▓▓▓ " + RESET + "│"; // ▒▓░▒▓░▒
    string line2 = "│" + color + " ▓▓▓░▓▓▓ " + RESET + "│";
    string line3 = "│" + color + " ▓░░░░░▓ " + RESET + "│";
    string line4 = "│" + color + " ▓▓▓░▓▓▓ " + RESET + "│";
    string line5 = "│" + color + " ▓▓▓░▓▓▓ " + RESET + "│";

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
        if (n < 0) {
            cardLines.push_back(splitLines(drawCardBack(colors["fg_green_bold"])));
            continue;
        }
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
    // Use conditional compilation to handle platform-specific setup.
#ifndef _WIN32
    // Linux and other Unix-like systems: directly print the cards.
    for (int i = 0; i < 52; i++) {
        Card card = getCard(i);
        cout << drawCard(card.rank, card.suit) << "\n";
    }

    vector<int> clubs;
    for (int i = 0; i < 13; i++) {
        clubs.push_back(i);
    }
    printCardsHorizontally(clubs);

    vector<int> diamonds;
    for (int i = 13; i < 26; i++) {
        diamonds.push_back(i);
    }
    printCardsHorizontally(diamonds);
    vector<int> hearts;
    for (int i = 26; i < 39; i++) {
        hearts.push_back(i);
    }
    printCardsHorizontally(hearts);
    vector<int> spades;
    for (int i = 39; i < 52; i++) {
        spades.push_back(i);
    }
    printCardsHorizontally(spades);

    printCardsHorizontally({0, -1, 26, -1});

    // cout << drawCard("2", "hearts") << "\n\n";
    // cout << drawCard("A", "spades") << "\n";
    // cout << drawCard("10", "diamonds") << "\n";
    // cout << drawCard("J", "hearts") << "\n";
    // cout << drawCard("Q", "clubs") << "\n";
    // cout << drawCard("K", "spades") << "\n";
    // cout << drawCard("A", "diamonds") << "\n";
#else
    // Windows: Enable ANSI escape sequences before printing.
    enableAnsiEscapeSequences();
    cout << drawCard("2", "hearts") << "\n\n";
    cout << drawCard("A", "spades") << "\n";
#endif

    return 0;
}