#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

using namespace std;

#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

/**
 * Rock Paper Scissors Lizard Spock
 *      Scissors cuts Paper
 *      Paper covers Rock
 *      Rock crushes Lizard
 *      Lizard poisons Spock
 *      Spock smashes Scissors
 *      Scissors decapitates Lizard
 *      Lizard eats Paper
 *      Paper disproves Spock
 *      Spock vaporizes Rock
 *      Rock crushes Scissors
 */
class WeaponManager {
};



// Use a string name to lookup emoji
map< string, string > Emojis = {
    {"rock", ROCK2},
    {"paper", PAPER2},
    {"scissors", SCISSORS2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2}};

// Use an emoji to lookup the string name
map< string, string > Names = {
    {ROCK2, "rock"},
    {PAPER2, "paper"},
    {SCISSORS2, "scissors"},
    {LIZARD2, "lizard"},
    {SPOCK2, "spock"}};

// use a string emoji name to lookup who it beats
map< string, vector< string > > rules = {
    {"rock", {"lizard", "scissors"}},
    {"paper", {"rock", "spock"}},
    {"scissors", {"paper", "lizard"}},
    {"lizard", {"spock", "paper"}},
    {"spock", {"rock", "scissors"}}};


/**
 * @brief Returns a random emoji from the Emojis map
 * 
 * @return pair< string, string > 
 */
pair< string, string > RandomEmoji() {
    auto it = Emojis.begin();                  // iterator to front of map
    std::advance(it, rand() % Emojis.size());  // advance some random amnt of steps
    //string random_emoji = it->second;         // grab emoji from map
    return make_pair(it->first, it->second);  // return rand emoji
}


/**
 * @brief Determines if one emoji beats another based on the rules in the "Rules" map.
 * 
 * @param string hand1  : string emoji name
 * @param string hand2  : other emoji name
 * @return true / false : return true if hand1 beats hand2 (based on rules in 'Rules' map)
 */
bool beats(string hand1, string hand2) {
    if (find(rules[hand1].begin(), rules[hand1].end(), hand2) != rules[hand1].end()) {
        return 1;
    }
    return 0;
}

/**
 * @brief Same as "beats" function above
 * 
 */
bool beats(pair< string, string > hand1, pair< string, string > hand2) {
    return beats(hand1.first,hand2.first);
}

class Weapon {
    string name;
    string emoji;

public:
    Weapon() {
        pair< string, string > p = RandomEmoji();
        name = p.first;
        emoji = p.second;
    }
    Weapon(string n) {
        name = n;
        emoji = Emojis[n];
    }

    friend ostream &operator<<(ostream &os, const Weapon &w) {
        return os << Emojis[w.name];
    }
    bool operator<(const Weapon &rhs) {
        if (beats(rhs.name, this->name)) {
            return 1;
        }
        return 0;
    }
    bool operator>(const Weapon &rhs) {
        if (beats(this->name, rhs.name)) {
            return 1;
        }
        return 0;
    }
};

class Player {
    Weapon primary;
    Weapon secondary;

public:
    Player() {
        // random primary and secondary
    }
    Player(string w1, string w2) {
        // both weapons assigned
    }
};

int main() {
    srand(time(0));

    pair< string, string > r1 = RandomEmoji();
    pair< string, string > r2 = RandomEmoji();

    cout << r1.second << " vs " << r2.second << endl;
    cout << beats(r1, r2) << endl;

    Weapon w1;
    Weapon w2;

    cout << w1 << " v " << w2 << endl;
    cout << (w1 < w2) << endl;
    cout << (w1 > w2) << endl;

    Player p1;
    Player p2;

    //cout<<(p1>p2)<<endl;
    return 0;
}