## Program 02 - Blackjack Part 2 
#### Due: TBD

<a href="PokerGame1.png"><img src="PokerGame1.png" width="300"></a>

- Implement the deck as a dynamic array inside the Deck class.  Create a constructor for the Deck class that accepts the number of 52-card decks to load. Cards are drawn from the high end of the array.
- The deck must be sufficiently shuffled at the beginning of the game.
- To aid in testing, you must give the option of printing the cards in the current playing deck in order.  Print 20 cards per line, separated by spaces.  Instead of printing "10" for a ten, print "0" so everything gets aligned nicely.  Use "J", "Q", "K", and "A" for jack, queen, king, and ace, respectively.
- You can choose your own algorithm to shuffle the deck, or just swap two random elements 10000 times.  You can use the function rand() to generate pseudo-random numbers.  
- Input must be 'H' (hit), 'S' (stand), 'D' (double down; see above), '?' (show deck), or 'Q' (quit).
- The player starts with $1000.  The initial bet placed before each hand is always $100.
- Do not clear the screen after each hand.  Just let it scroll.
- At a minimum, you should have one file for the Card, Deck, and Hand classes, one file for the Blackjack class, and a main.cpp.  A generalized Deck will also have two files for a Card class.  Note that none of the logic for the Blackjack game itself should reside in project2.cpp.



It is good programming practice to use a constructor for the Blackjack class to set the initial bank roll, number of decks, etc.

### Sample Run

```
██████  ██       █████   ██████ ██   ██      ██  █████   ██████ ██   ██ 
██   ██ ██      ██   ██ ██      ██  ██       ██ ██   ██ ██      ██  ██  
██████  ██      ███████ ██      █████        ██ ███████ ██      █████   
██   ██ ██      ██   ██ ██      ██  ██  ██   ██ ██   ██ ██      ██  ██  
██████  ███████ ██   ██  ██████ ██   ██  █████  ██   ██  ██████ ██   ██ 

  ___  ___   _   _    ___ ___ 
 |   \| __| /_\ | |  | __| _ \
 | |) | _| / _ \| |__| _||   /
 |___/|___/_/ \_\____|___|_|_\
                              
      .------..------.
      |8.--. || .--. |
      | :/\: ||  //  |
      | (__) ||  //  |
      | '--'8|| '--' |
      `------'`------'

  ___ _      ___   _____ ___ 
 | _ \ |    /_\ \ / / __| _ \
 |  _/ |__ / _ \ V /| _||   /
 |_| |____/_/ \_\_| |___|_|_\
                             

      .------..------.
      |4.--. ||Q.--. |
      | :/\: || :/\: |
      | (__) || (__) |
      | '--'4|| '--'Q|
      `------'`------'

Sum: 14


H : Hit | S : Stand
```
**Player Hits**

```
  ___  ___   _   _    ___ ___ 
 |   \| __| /_\ | |  | __| _ \
 | |) | _| / _ \| |__| _||   /
 |___/|___/_/ \_\____|___|_|_\

      .------..------.
      |8.--. || .--. |
      | :/\: ||  //  |
      | (__) ||  //  |
      | '--'8|| '--' |
      `------'`------'

  ___ _      ___   _____ ___ 
 | _ \ |    /_\ \ / / __| _ \
 |  _/ |__ / _ \ V /| _||   /
 |_| |____/_/ \_\_| |___|_|_\

    .------..------..------.
    |4.--. ||Q.--. ||6.--. |
    | :/\: || :/\: || :/\: |
    | (__) || (__) || :\/: |
    | '--'4|| '--'Q|| '--'6|
    `------'`------'`------'

Sum: 20


H : Hit | S : Stand
```
**Player Stands**