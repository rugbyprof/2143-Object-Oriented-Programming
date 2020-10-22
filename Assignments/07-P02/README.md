## Program 02 - Blackjack Part 1 Overview
#### Due: 10-29-2020 (Thursday @ 9:30 a.m.)

In this project, you will create a casino blackjack game.  Part 1 (this assignment) discusses lots of things, but ultimately you will design a black jack game using UML. Now sit back and read ...

A brief tutorial on the rules of blackjack is given below for those who don't know how to play.  Even if you know the rules of blackjack, make sure you read each bullet or you may miss a requirement.  

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

### More on Game Play

- The game begins with **N** standard 52-card decks shuffled together to form the game deck. 
- The dealer will control the deck, and deal cards in a round robin fashion to every player in the game starting with the dealer. 
- Cards are drawn from the top of the deck without replacement and given to each player. 
- Typically it is one up and one down but in our game, only the dealer will keep one card hidden until everyone has stopped hitting. 
- Hitting also occurs in a round robin fashion, where while its their turn, a player will take `1-n` cards until they stay. 
- We will focus on 1 player vs a dealer, however a good game design should take into account more than 1 player vs a dealer.
- The player has a hand, that can hold **N** cards depending on how many times they "hit" (ask for another card to get their total closer to 21).
- A Player also has a bank that starts at 1000 dollars, and bets 100 dollars per hand (for simplicity).

### Game Design

- You will have to design and implement a set of classes to represent all the necessary components of a simulated black jack game. 
- Simply reading this overview up to now, you should start to get a feel for what needs to be a class and how this will help you organize your design.
- If you don't have an idea, I will tell you that you will need a minimum of these classes: Card, Deck, Hand, Player, Game. 
- Notice that the classes tend to be "nouns" ... or things.
- Well, then how do we decide what the methods are for my classes?
- Since classes are things, methods tend to be "actions".
- And there you have it:  Nouns = Classes, Verbs = Methods.
- It's not always that simple, but in the general case, its a great starting point.

### Starter Design

Lets look at a generic layout of a set of classes:
#### Class Card
  - Description:
    - Not a lot to do here since it really just represents "values" and doesn't have any actions. 
  - Data: 
    - Rank - (where it ranks in the deck)
    - Value - (how much its worth for game X)
  - Methods:
    - Set rank 
    - Set value 
    - Get rank
    - Get value
    - Print 
#### Class Deck
  - Description:
    - A container of cards. 
  - Data: 
    - Size - how many cards in deck
    - Remaining - how many cards left
  - Methods:
    - Deal - remove a card from the deck
    - Shuffle - re-arrange the cards in some random fashion
    - Reset - go back to initial state with all cards
    - Etc.
#### Class Hand
  - Description:
    - A container of cards (hmmmm... sound familiar to anyone?)
  - Data: 
    - Size - how many cards in deck
    - Remaining - how many cards left
  - Methods:
    - Shuffle - re-arrange the cards in some random fashion
    - Sort  - put cards in some order
    - Discard - remove a card (based on some choice, not randomly like deal a card)
    - Etc.
#### Class Player
  - Description:
    - Represents a single player as part of (in this case) a Black Jack game.
  - Data: 
    - Bank - how much money she has
    - Name - some identifier
    - Hand - instance of a card container class
    - Total - Total count of values of cards in hand ( WAIT!! ... does this belong here?)
    - Etc.
  - Methods:
    - Bet - remove money from bank.
    - Win - add money to bank.
    - Hit - add a card to hand.
    - Etc.
#### Class Game
  - Description:
    - In charge of the black jack game.
    - When the dealer deals.
    - When the dealer hits. 
    - When the dealer awards winnings ( WAIT!! ... is there a lot of dealer stuff going on that could justify a class?)
    - Who gets the next card.
  - Data:
    - Players - Vector of player classes?
    - Dealer - Dealer class? Or use player class?
    - Deck - Does this go here?
    - Etc.
  - Methods:
    - Print - prints current state to console 
    - AcceptBets - ??
    - Deal - start round off
    - Etc.

### More Design Talk

- There is room for different approaches. For example:
  - Is a Dealer an instance of a Player? Or is it something entirely different?  
  - Are a Deck and a Hand so different. Can we find enough overlap between the two to justify a base card container class?
  - Is "Bank" just a data member in a player? Or can we justify an entire class? Of course if we stored bank in a "player" class, we could add and subtract amounts to and from the "bank" value. But we would need methods for doing that right? Hmmm. Sounds like a good reason to package (encapsulate) those things together:

```cpp
class Bank{
  double amount;
  Bank(){
    amount = 1000;
  }
public:
  // or deposit
  void won(double x){ 
    amount += x;
  }
  // or withdraw
  void bet(int x){ 
    amount -= x;
  }
};
```

### UML 

Your actual assignment is to create a Class Diagram showing the relationships between your blackjack classes. Here is an example class diagram taken from one of the LucidChart tutorials.

<img src="https://d2slcw3kip6qmk.cloudfront.net/marketing/pages/chart/class-diagram-for-ATM-system-UML/Class-Diagram-ATM-system-750x660.png" width="400">

We won't talk about UML until you start to think about your game design and read / watch the following

#### Video Tutorial
[![Class Diagram Video](https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/uml_vid_250.png)](https://www.youtube.com/embed/UI6lqHOVHic) 

#### Web Tutorial 
LucidChart UML [Class Diagram Tutorial](https://www.lucidchart.com/pages/uml-class-diagram)

#### Software
- You can use [LucidCharts](https://www.lucidchart.com/pages/) to do your diagrams. It's free to some extent, but it makes you create an account
- You can also use [draw.io](https://draw.io) to make your diagrams. It is free, and doesn't require you to sign up.

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step1" width="250">

<img src="https://cs.msutexas.edu/~griffin/zcloud/zcloud-files/draw.io.step2" width="250">






### Deliverables:

- Create a folder in your assignments folder called `P02`
- In that folder create a file called README.md
- Help with markdown: https://guides.github.com/features/mastering-markdown/
- Show each class separately with a small description of each data member and method.
- Then show your diagram with the relationships between them and a description of each. 
- Images can be exported from DrawIO or LucidCharts.
- Create a banner with **P02.1** as part of the title (see [HERE](../../Resources/03-Banner/README.md))
- Banner is stapled with your UML Diagram so its the top and only visible page. Basically a cover sheet.
- Put your assignment on the front desk at the beginning of class. Example below:
  
```txt
Banner
UML
```