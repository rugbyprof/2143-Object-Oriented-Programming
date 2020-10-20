## Program 02 - Blackjack Part 1 Overview
#### Due: 10-26-2020 (Monday @ 9:30 a.m.)

In this project, you will create a casino blackjack game.  A brief tutorial on the rules of blackjack is given below for those who don't know how to play.  Even if you know the rules of blackjack, make sure you read each bullet or you may miss a requirement.  

### How to Play Casino Blackjack

- The object of blackjack is to get a hand of cards as close to a sum of 21 as possible without going over.  If you go over 21, you bust and lose the hand automatically.
- Before cards are dealt, you must place your bet.  This money is immediately subtracted from your bank roll.  Bets are always **$100** in for this project.  The player starts with a bank of **$1000**.
- Two cards are dealt to both the player and the dealer, one face up and one face down.  You can look at both your cards, but can only see the dealer's face up card.  The dealer can see both his cards.  Number cards are worth their face value.  Jack, Queen, and King are worth 10.  Ace is worth either 1 or 11, whichever gives you the better hand.  An ace may change value during the game *(i.e. if you have an ace and an eight, a sum of nineteen, and then draw a five, the ace will change to be worth 1 so you don't bust).*
- If you are dealt a sum of 21 on your first two cards, you have a blackjack and you automatically win **2.5 times your initial bet**.  If both you and the dealer have a blackjack, the game is a push (tie).
- You may choose to hit (draw a card) or stand (do not draw any more cards).  If you hit, draw a card from the deck and add it to your hand.  You may continue to draw cards until you decide to stand or you bust.  Once you decide to stand, the dealer draws cards.  If you bust, you lose automatically and the dealer does not draw any cards.
- The dealer must continue to draw cards until he has a sum of at least 17.  Once he has a sum of at least 17, he stands.  If he goes over 21, he busts and you win.
- If neither player busts, whoever has the higher total wins.  If both totals are the same, the game is a push.
- In the case of a push, you get your initial bet back.
- If you win, you win double your initial bet.
- Continue to play until you are out of money or decide to quit.
- If your initial two cards have a sum of 10 or 11, you may decide to double down instead of choosing the normal hit/stand options.  If you double down, you must wager an additional 0.5 times your initial bet ($50) and you must immediately draw one more card.  You may not draw any more than one card.  The dealer then plays as normal.  If you win, you win 3 times your initial bet (twice your initial bet plus twice the additional 0.5).
- Don't worry about splitting. (Splitting allows a player to "split" into two separate hands with bets for both. We will not allow this.)

 
### Overview and Background

- You will have to design and implement a set of classes to represent all the necessary components of a simulated black jack game.  
- The game begins with 5 standard 52-card decks shuffled together to form the game deck.  
- Cards are drawn from the top without replacement and dealt as described above to 1-n players. We will focus on 1 player vs a dealer, however a good game design should take into account more than 1 player vs a dealer.
- Based on the last few bullet points, you should already be thinking of how you will organize your design for the game.
- I will tell you that you will need a minimum of these classes: Card, Deck, Hand, Player, Game. 
- When you design your classes you should think using the following guidelines: Nouns = Classes, Verbs = Methods. See the classes I listed? All nouns. So, let us think about what each of those things can do. Don't limit your thinking to blackjack. Think of each class in a more generic sense. Let us use "Hand" as an example. A hand can:
  - Add a card
    - Like hitting in blackjack
    - Or drawing a card in go-fish
  - Remove a card
    - We never remove a card in blackjack (maybe if you split which we are not implementing)
    - You play a card in war (so remove it from the hand)
  - Order cards (no need to )
    - No need in blackjack
    - Helps in different games like poker (not texas holdem) where ordering cards would visually help the player determine what thier hand is. 
  - Fold
    - Remove all cards.
    - Doesn't happen in blackjack.


https://www.youtube.com/watch?v=UI6lqHOVHic


- Implement the deck as a dynamic array inside the Deck class.  Create a constructor for the Deck class that accepts the number of 52-card decks to load. Cards are drawn from the high end of the array.
- The deck must be sufficiently shuffled at the beginning of the game.
- To aid in testing, you must give the option of printing the cards in the current playing deck in order.  Print 20 cards per line, separated by spaces.  Instead of printing "10" for a ten, print "0" so everything gets aligned nicely.  Use "J", "Q", "K", and "A" for jack, queen, king, and ace, respectively.
- You can choose your own algorithm to shuffle the deck, or just swap two random elements 10000 times.  You can use the function rand() to generate pseudo-random numbers.  See your text for more information.
- Input must be 'H' (hit), 'S' (stand), 'D' (double down; see above), '?' (show deck), or 'Q' (quit).
- The player starts with $1000.  The initial bet placed before each hand is always $100.
- Do not clear the screen after each hand.  Just let it scroll.
- At a minimum, you should have two files for the Deck class, two files for the Blackjack class, and project2.cpp.  A generalized Deck will also have two files for a Card class.  Note that none of the logic for the Blackjack game itself should reside in project2.cpp.



A main emphasis in this course is Object-Oriented Programming.  This particular assignment implements the blackjack game in C++.  Because C++ is a superset of C, it is possible for the C++ compiler to implement blackjack as an old-style C program.   Avoid the following pitfalls.

1.	Do not use global variables, use data members (class variables).
2.	Do not use global functions except for main(), use member functions.
3.	Do not use char * or char [] for strings, using the string class.
4.	Do not use structures, use classes.
5.	Do not use printf and scanf, use cout and cin.

It is good programming practice to use a constructor for the Blackjack class to set the initial bank roll, number of decks, etc.

### Sample Run
