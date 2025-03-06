---
title: "Cross-Platform Card Printer in C++"
description: "A C++ implementation that uses conditional compilation (#ifndef/#ifdef) to print card representations on both Linux and Windows terminals with ANSI escape sequences enabled on Windows."
---

## "Cross-Platform Card Printer in C++"

- Below is a C++ code snippet that uses conditional compilation to handle differences between Linux (and similar systems) and Windows.
- On Windows, it enables ANSI escape sequence processing (supported on Windows 10 and later) so that our Unicode cards display correctly with color.
- On Linux, it simply prints the cards because ANSI colors are generally supported out-of-the-box.

**C++ Code**

```cpp
#include <iostream>
#include <string>
#include <algorithm>

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

// Returns the colored Unicode suit symbol based on the suit name.
string getSuitSymbol(const string &suit) {
    string lowerSuit = suit;
    transform(lowerSuit.begin(), lowerSuit.end(), lowerSuit.begin(), ::tolower);
    if (lowerSuit == "hearts")
        return "\033[31m\u2665\033[0m"; // Red heart: ♥
    else if (lowerSuit == "diamonds")
        return "\033[31m\u2666\033[0m"; // Red diamond: ♦
    else if (lowerSuit == "clubs")
        return "\033[32m\u2663\033[0m"; // Green club: ♣
    else if (lowerSuit == "spades")
        return "\u2660";               // Spade: ♠ (default color)
    else
        return suit;
}

// Draws a card with a Unicode border, rank, and colored suit symbol.
string drawCard(const string &rank, const string &suit) {
    string top_border    = "┌─────────┐";
    string bottom_border = "└─────────┘";
    string suitSymbol    = getSuitSymbol(suit);

    // Adjust spacing for rank "10" (which uses 2 characters)
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

int main() {
  // Use conditional compilation to handle platform-specific setup.
#ifndef _WIN32
    // Linux and other Unix-like systems: directly print the cards.
    cout << drawCard("2", "hearts") << "\n\n";
    cout << drawCard("A", "spades") << "\n";
#else
    // Windows: Enable ANSI escape sequences before printing.
    enableAnsiEscapeSequences();
    cout << drawCard("2", "hearts") << "\n\n";
    cout << drawCard("A", "spades") << "\n";
#endif

    return 0;
}
```

- **How It Works**
  - **Conditional Compilation**:
    - The #ifndef \_WIN32 block is used for Linux and similar systems, where we assume ANSI escape sequences are supported by default.
    - The #ifdef \_WIN32 block is for Windows. It calls enableAnsiEscapeSequences() to set up the console for ANSI colors.
  - **ANSI Escape Sequences & Unicode**:
    - The suit symbols (♥, ♦, ♣, ♠) are rendered using Unicode, and colored with ANSI escape sequences.
  - **Card Layout**:
    - Unicode box drawing characters create a cleaner card border.
    - The card’s rank appears at the top left and bottom right, with special spacing for “10”.

Compile this code with a C++11 (or later) compiler, and it should work on both Linux and Windows terminals.

---

## "Broadening Card Representation for All Cards"

Description: "A summary of Unicode symbols and ANSI escape sequences for all card suits and how to extend your solution."

---

To broaden your card representation for all the cards, here’s a quick guide on the key Unicode symbols and ANSI escape sequences that you can plug into your C++ (or any other language) solution.

Unicode Suit Symbols

- Hearts: \u2665 → ♥
- Diamonds: \u2666 → ♦
- Clubs: \u2663 → ♣
- Spades: \u2660 → ♠

ANSI Escape Sequences for Colors

You can add color to your symbols using ANSI escape codes. Here are a few examples:

- Red (for hearts and diamonds):
  `\033[31m` sets the text color to red, and `\033[0m` resets it.

**Example:**

```cpp
"\033[31m\u2665\033[0m" // Red heart: ♥
"\033[31m\u2666\033[0m" // Red diamond: ♦
```

- Green (commonly used for clubs):

```cpp
"\033[32m\u2663\033[0m" // Green club: ♣
```

- Default or Blue (if you want to give spades a color):

For spades, you can either leave them uncolored or choose another color.

```cpp
"\033[34m\u2660\033[0m" // Blue spade: ♠
// or simply: "\u2660" for default color.
```

### Extending to the Rest of the Cards

For a full deck, you can set up a mapping for ranks (Ace, 2-10, Jack, Queen, King) and use these symbols for the suit. Here’s a conceptual snippet for handling the suits and their colors:

```cpp
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> suitSymbols = {
    {"hearts", "\033[31m\u2665\033[0m"}, // ♥ in red
    {"diamonds", "\033[31m\u2666\033[0m"}, // ♦ in red
    {"clubs", "\033[32m\u2663\033[0m"}, // ♣ in green
    {"spades", "\033[34m\u2660\033[0m"} // ♠ in blue (or default if preferred)
};

string getSuitSymbol(const string &suit) {
    auto it = suitSymbols.find(suit);
    return (it != suitSymbols.end()) ? it->second : suit;
}
```

### Additional Considerations

- **Unicode Box Drawing for Borders:**
  - Use characters like ┌, ─, ┐, │, and └ to form a neat border.
- **Rank Handling:**
  - Ranks like "10" need special spacing since they occupy two characters. For the rest (e.g., "A", "2", …, "K"), you might add a trailing space for alignment.
- **Conditional Compilation:**
  - As previously shown, use `#ifdef \_WIN32` to enable ANSI processing on Windows.

This should give you a solid foundation to expand the card drawing function for all cards in the deck. Feel free to adapt the code snippets as needed and mix in your personal styling.

Below is a C++ solution that defines a Card struct and a getCard function. The function uses modular arithmetic (n % 13 and n / 13) to compute the rank and suit from an integer n (0–51) and then returns the result using lookup arrays.

**C++ Code Example**

```cpp
#include <iostream>
#include <string>
#include <array>

using namespace std;

// Define a struct to represent a card
struct Card {
    string rank;
    string suit;
};

// Function that takes an integer n (0-51) and returns the corresponding card
Card getCard(int n) {
    // Lookup arrays for ranks and suits
    array<string, 13> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    array<string, 4> suits = {"Clubs", "Diamonds", "Hearts", "Spades"};

    // Calculate rank and suit indices using mod and div
    int rankIndex = n % 13;   // Gives a value between 0 and 12
    int suitIndex = n / 13;   // Gives a value between 0 and 3

    return Card{ranks[rankIndex], suits[suitIndex]};
}

int main() {
    // Test the getCard function for all cards in a deck
    for (int i = 0; i < 52; i++) {
        Card c = getCard(i);
        cout << "Card " << i << ": " << c.rank << " of " << c.suit << endl;
    }
    return 0;
}
```

- **How It Works**
  - Struct Definition:
  - The Card struct holds two strings: one for the rank (e.g., “A”, “2”, …, “K”) and one for the suit (e.g., “Clubs”,
- **Diamonds”, etc.).**
  - Lookup Arrays:
- The arrays ranks and suits provide a quick lookup for converting the computed indices to a human-readable string.
  - Mod and Div Operations:
  - $n % 13$ gives the index for the rank.
  - $n / 13$ gives the index for the suit.

This should give you a robust starting point to integrate card lookup into your project. Let me know if you need any more tweaks or additional features!
