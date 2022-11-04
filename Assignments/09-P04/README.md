## Program 4 - Rock Paper Scissors Lizard Spock
#### Due: 11-09-2022 (Friday @ 11:00 a.m.)


### Overview

This is the first part of at least two others for a total of 3. The ultimate goal is to have two characters battle with one or both sides having the ability to choose which character to battle. This will let us implement some `runtime polymorphism` in the final component. However we need to start a little smaller. Since I could not think of a simple way for two characters to battle, we are going to use a version of Rock Paper Scissors Lizard Spock! 

### Background + Helper Code

Included in this folder are two files:

- [rockPaper.cpp](rockPaper.cpp)
- [emojis.h](emojis.h) (source: https://github.com/99x/emojicpp)

The [rockPaper.cpp](rockPaper.cpp) file contains a few different things, including a couple of ways to implement dice rolling, and also how to print out emojis to the console.

```
Rock: 🗻
Paper: 📃
Scissors: 🔪
Lizard: 🐸
Spock: 🖖
```
Below is an example of some constants being defined as unicode characters and then a class that has static methods and data members to help provide some functionality in printing out the  specific emojis for each of the five types. I made it all static to show how we can use static methods without declaring an instance of the `Hands` class. If I want to print out the emoji for the `lizard` I simply use `Hands::Rock()` 

```cpp
#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"

struct Hands {
    const string rock = ROCK2;
    const string paper = PAPER2;
    const string scissors = SCISSORS2;
    const string lizard = LIZARD2;
    const string spock = SPOCK2;

    static map< string, string > Emojis;  // stl map
    //         name  , emoji

    static map< string, string > Names;  // stl map
    //         emoji  , name

    static string RandHand() {
        auto it = Emojis.begin();  // iterator to front of map

        std::advance(it, rand() % Emojis.size());  // advance some random amnt
                                                   //   of steps

        string random_hand = it->second;  // grab emoji from map

        return random_hand;  // return rand emoji
    }

    static string Rock() {
        return Emojis["rock"];
    }
    static string Paper() {
        return Emojis["paper"];
    }
    static string Scissors() {
        return Emojis["scissors"];
    }
    static string Lizard() {
        return Emojis["lizard"];
    }
    static string Spock() {
        return Emojis["spock"];
    }
};
```

This class also shows an example of using `STL::Maps`, which we can talk about more in class. In fact, the [emojis.h](emojis.h) file is really one big STL::Map with `string` names as the `key` to find each unicode value that prints out the corresponding emoji. The colon before and after each key (value on the left) is just a naming convention since some editors use that convention to identify emojis. In slack type `:th` and it will start giving you emoji choices that start with those letters.

Example:

```cpp
    static std::map<std::string, std::string> EMOJIS = {
        {":admission_tickets:" , u8"\U0001F39F"},
        {":aerial_tramway:" , u8"\U0001F6A1"},
        {":airplane:" , u8"\U00002708"}
        ...
    };
```

### RPSLS

What does any of this previous stuff have to do with RockPaperScissors.... ?!? I wanted you to have lots of new code to learn from (for one reason), and the other is that I need to implement most of the program to look for downfalls as well as good ways to solve components of the program. 

What I need from you is a way to determine a winner (if possible) when a character has been assigned two unique "emojis" from the RPSLS game. For example here are the emojis for this game:

|   Name   | Emoji |
| :------: | :---: |
|   Rock   |   🗻   |
|  Paper   |   📃   |
| Scissors |   🔪   |
|  Lizard  |   🐸   |
|  Spock   |   🖖   |


Each player (character) will get assigned two of them:


|   #   | Player 1 | Player 2 |
| :---: | :------: | :------: |
|   1   |    📃     |    🔪     |
|   2   |    🐸     |    🗻     |


Using the following rules can we determine a winner?

| Text Rule                   | Visual Version  |
| :-------------------------- | :-------------- |
| Scissors cuts Paper         | 🔪 cuts 📃        |
| Paper covers Rock           | 📃 covers 🗻      |
| Rock crushes Lizard         | 🗻 crushes 🐸     |
| Lizard poisons Spock        | 🐸  poisons 🖖    |
| Spock smashes Scissors      | 🖖 smashes 🔪     |
| Scissors decapitates Lizard | 🔪 decapitates 🐸 |
| Lizard eats Paper           | 🐸  eats 📃       |
| Paper disproves Spock       | 📃 disproves 🖖   |
| Spock vaporizes Rock        | 🖖 vaporizes 🗻   |
| Rock crushes Scissors       | 🗻 crushes 🔪     |

- If the emojis are assigned at random, can we guarantee a winner?
- If we cannot, how do we implement a tie breaker?

### Requirements

- I want you to determine what needs to be implemented to solve this problem. 
  - Do we one or more classes? 
  - Do we only need a function? 
- Assume (for now) that a player (character) has this basic simple structure. You don't need to add anything to the player for this assignment:

``` cpp
struct Player{
    string weapon1;
    string weapon2;
    // other possible stuff

    /**
     * Constructor guarantees a player has two different "weapons"
     */
    Player(){
        weapon1 = Hands::RandHand();
        weapon2 = Hands::RandHand();

        // if both weapons are the same
        // choose another.
        while(weapon2==weapon1){
            weapon2 = Hands::RandHand();
        }
    }
    // other possible methods
};
```

- Write some construct (class, function, struct ...) that would allow you to do the following:

```cpp
Player p1; // gets two random weapons when constructed
Player p2; // same

// Hmmm. Look familiar? (operator overloading)
if(p1 > p2){
    cout<<"Player 1's 🐸 beat Player 2's 🖖!"<<endl;
}else if(p2 > p1){
    cout<<"Player 2's 🔪 beat Player 1's 🐸!"<<endl;
}else{
    cout<<"It's a tie!"<<endl;
    // print all 4 weapons here...
}

```
- I'm not sure what would result in a tie right now. We only assign 2 weapons per player, so a battle includes 4 possibly distinct weapons leaving a possible 5th out. Or it could include 2 distinct weapons if both players have the same two. Ultimately, we don't want a tie, and my intuition says we should be good. In fact, the only time we may need the second weapon is if the first weapon is the same.

- Make sure you run through at least 25+ instances either resetting each players weapons, or creating two new players every time and visually display the results of a "battle". 

### Deliverables

- Create a folder in your assignments folder called `P03`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Look at [this](../../Resources/02-Readmees/README.md) to help with your `README.md` file
- Create a banner for your program **(see [HERE](../../Resources/03-Banner/README.md))**.
  - Make sure your banner is readable and does NOT have blank lines between every other row.

```
2143 
P03A
Name
```

- Print out your source code. Make sure it's **[commented](../../Resources/01-Comments/README.md)**.
- Print out your output file.
- Put your assignment on the lecture podium at the beginning of class.
- Staple everything in this order:
  - **1)** Banner (on top)
  - **2)** Source code (middle)
  - **3)** Output (bottom)
- Any hand writing on your assignment is reduction in 1 letter grade.
- Failure to follow instructions is a reduction in 1 letter grade.
- Unreadable banner is a reduction in 1 letter grade.
