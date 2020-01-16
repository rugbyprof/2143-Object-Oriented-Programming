Program 1
=========
Due: February 14<sup>th</sup> by classtime

![](https://d3vv6lp55qjaqc.cloudfront.net/items/1c0c2u113x262e2k2R0C/war.png?X-CloudApp-Visitor-Id=1094421)

## Game Rules

***Goal***

The goal is to be the first player to win all 52 cards

***The Deal***

The deck is divided evenly, with each player receiving 26 cards, dealt one at a time, face down. Anyone may deal first. Each player places his stack of cards face down, in front of him.

***The Play***

Each player turns up a card at the same time and the player with the higher card takes both cards and puts them, face down, on the bottom of his stack. Remember `list.pop(0)` removes from the front of a list, and `list.append()` adds to end of a list. This coincides nicely with players removing and adding cards to thier hand.

If the cards are the same rank, it is War. Each player turns up one card face down and one card face up. The player with the higher cards takes both piles (six cards). If the turned-up cards are again the same rank, each player places another card face down and turns another card face up. The player with the higher card takes all 10 cards, and so on. (This is the toughest piece to implement, so get most everything else working first!)

***How to Keep Score***

The game ends when one player has won all the cards.

## Program Overview

- There is plenty of code examples in this folder. I tried to organize what I thought was a good approach into [starter.py](./starter.py).
- The [starter.py](./starter.py) doesn't need an ascii file to print cards, but then again, the cards aren't that amazing. However, the point is to implement a game! So you can print cards whichever way you like, as long as it's not totally text based. (BTW: Text based is something like: KS = King of spades. 9H = Nine of hearts, etc.)
- The classes provided are:
    - ***`Card`***
    - ***`Deck`***
    - ***`Hand`***
- Feel free to change these around to fit your solution. 
- You are required to create an additional ***`Player`*** class that will represent a single player in the game along with a ***`Game`*** class that will manage the game. 
- I don't see any place where inheritance will be needed. Composition seems to be the best approach:
    - A ***`Player`*** has an instance of a ***`Hand`*** (where a ***`Hand`*** starts with 26 cards).
    - A ***`Game`*** has two ***`Player`*** instances (possibly more depending on how we implement the game).
- I've been implementing the game, and I think that a player extending a hand may be a better approach. More in class.
- You should think about what a player will do when playing the game, and what the game needs to provide each player, nad let those thoughts help you create your methods. Here are some thoughts:
    - A Player plays a card: `play_a_card` (pop 1 card from a players hand)
    - The game will compare two cards and assign a winner.
    - A player that wins needs to put cards into thier hand (`add_won_cards`). 
- Remember, a game ends when one players hand contains (wins) all the cards.
- I have some more thoughts that I want to pass on, but I will discuss them in class. 
- I expect some questions next week, so look over the problem, and starter code !!
