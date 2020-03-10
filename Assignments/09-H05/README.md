## Playing Cards - Not Just Poker
#### Due:  03-13-2020 (Friday @ 12:30 p.m.)

If you look [HERE](../../Lectures/L05/README.md) you will see our start at a poker game implementation. We need to re-design the [poker_game.hpp](../../Lectures/L05/poker_game.hpp) classes into a more generic "Playing Card" set of classes. The term ***Playing Card*** is ubiquitous enough to imply: **Rank** and **Suit**, and we can implement many other games besides "poker" with a set of playing cards. 

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/playing_cards_2143_2020.jpg" width="400">

Using the existing code in [poker_game.hpp](../../Lectures/L05/poker_game.hpp) create a `PlayingCard.hpp` file with all of the card based data (see below):

```cpp
const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4] = {"♠", "♦", "♣", "♥"};

// Black background        blue ,  red , blue , red
const string colors2[4] = {"&60", "&20", "&60", "&20"};

// Colored background      blue  , red  , blue , red
const string colors[4] = {"&16", "&12", "&16", "&12"};

// Card labels (could be "Iron Man" or "Charmander" or "Elf" ... anything)
const string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
```

Each of the above items either needs to be added to the `PlayingCard` class, or removed if it is not needed. One idea is to create a `Color` class (or struct thats all public) which will return the proper colors based on method calls rather than array locations like `color = colors[suitNum];`. Rather that might look like: `color = ForeColor.red;`


Color Values:

- DEFAULT = 0;
- BLACK = 1;
- RED = 2;
- YELLOW = 3;
- GREEN = 4;
- BLUE = 5;
- CYAN = 6;
- MAGENTA = 7;
- WHITE = 8;

- To set a foreground color you print `&1X` where `X` = your color from above.
- To set a background color you print `&X0` where `X` = your color from above.
- To reset the color (back to white) you can add `&00` to your printed string.
- All of this depends on using TermIO to print (and I'm not doing it as Jeremy the author wants me to), but if you look at his code, you may want to change. 


Color Struct Example:

```cpp
struct BackColor{
    string red;
    ...

    Color(){
        red = "&20";
    }
};

struct ForeColor{

    string red;
    ...

    Color(){
        red = "&12";
        ...
    }
};

```
 
Your new card class definition should look similar to the following:
```cpp
class Card {
private:
    int suitNum;     // value 0-3 : num index of suit
    int rank;        // 0-13      : num value of rank
    int number;      // 1-52      : unique value determines card
    int value;       // 1-14      : numeric value used for comparison
    string suitChar; // "♠", "♦", "♣", "♥"
    string rankChar; // Ace, 1 ,2 ,3 ... Q, K
    string color;    // Spade=blue, Diamond=red, etc.

public:
    friend ostream;

    Card(int);
    string Repr();
    bool operator<(const Card &);
    bool operator>(const Card &);
    bool operator==(const Card &);
    bool operator!=(const Card &);
    bool operator()(const Card &);
    void setForegroundColor(string color);       // set foreground color of card
    void setBackgroundColor(string color);      // set background color of card
    void setColors(string fore,string back);      // set fore and back
    void setCharacterColor(string color);        // set symbol color 
    void setNumberColor(string color);          // set number color
    void setColors(string fore, string back, string symbol, string number);
    // and any other overloaded convenience methods you want to add. 

};
```

Your methods should control what the card looks like when it prints. If you see below there
is a color variable embedded in the string. Your methods should adjust those values.

```cpp
string Card::Repr() {
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
```


