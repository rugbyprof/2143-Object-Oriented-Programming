## Video Poker

The assignment is complete, but check back to see if I've added any helper code. I most likely will.

### Overview

We are going to implement a video poker game. Video poker is an electronic version of the card game with the same name (minus the video). The basic rules are:

- Deal a player 5 cards
- If the player is happy with the hand because it has a high enough rank, the player can keep the cards.
- If the player feels they could make a hand with a higher rank, the player is allowed to exchange 1 or all of their cards (this rule can change based on the house rules).
- The rank of the hand after the second deal is the result of that game.
- There are variations of poker, Texas Hold'em being one of them. We will stick to the variation I just described.
- So how are the hands ranked? See below:

### Poker Hand Ranks

![](http://www.freevideopoker4u.com/images/gamelogos/poker-hands.gif)

| Rank | Name              | Cards                                          | Payout |
|:----:|:------------------|:-----------------------------------------------|:------:|
|1.   |Royal flush         | A, K, Q, J, 10, all the same suit.             | 800 |
|2.   |Four Aces or Eights | Categorized as four of a kind.                 | 80 |
|3.   |Straight flush      | Five cards in a sequence, all in the same suit.| 50 |
|4.   |Four Sevens         | Categorized as four of a kind.       | 50 |
|5.   |Four of a kind      | All four cards of the same rank.     | 25 |
|6.   |Full house          | Three of a kind with a pair.         | 8 |
|7.   |Flush               | Any five cards of the same suit, but not in a sequence.| 5|
|8.   |Straight            | Five cards in a sequence, but not of the same suit. | 4 |
|9.   |Three of a kind     | Three cards of the same rank.        | 3 |
|10.  |Two pair            | Two different pairs.                 | 2 |
|11.  |Pair                | Two cards of the same rank. Must be Jacks or better. | 1 |
|12.  |High Card           | When you haven't made any of the hands above, the highest card plays. This is a loser in video poker. | 0 |

The table above has an additional column called "payout", this is the number of points a player can earn in the video poker version for the corresponding hand. Another question you might be having is: "How do I calculate a given hand?". Lets talk a little card arithmetic:

```python

	# Suits are stored in each card as strings
	suits = ['spades','hearts','diamonds','clubs'] 
	
	# Ranks are stored as integers. So the deck is represented as cards from 2 ... 53.
	ranks = [i for i in range(2,54)]
	
	# To get the integer value of a suit we do (in this case a 1):
	suit_val = suits.index("hearts")
	
	# The first 13 cards (integers 2 - 14) represent all the 'spades'
	# The next 13 cards (integers 15 - 28) represent all the 'hearts'
	# And so on ...
	
	# So even though we store the suit for a card in the object, we only 
	# need it's integer value. 
	
	card1 = Card('diamonds',11) # This is the jack of diamonds and becomes card (2,11) or (37).
	
	# We calculate the integer value:
	card_value = ((suits.index("diamonds") * 13) + rank)
	
	# How do we leverage this knowledge to start to calculate hands?
	
	def get_suit(card_value):
		return card_value % 4
		
	def get_rank(card_value):
		return card_value % 13
		
	
```


## General Requirements (100000% of your score)

Using the starter code at [here](https://github.com/rugbyprof/2143-ObjectOrientedProgramming/tree/master/card_game/graphics_game) fulfill the following requirements without using the graphics module. Use the 'video_poker.py` file as your starting point for this part as well as the next.

- This is an oop course, so you will be expected to create at least two classes:
    - A `game_driver` class that runs the game:
        - print menus
        - prompts user
        - game score
        - etc

    - A `video_poker` class that deals with:
        - dealing cards 
        - determining winning hands
        - getting images for cards
        - etc.
        
Simple example:

```python

game = game_driver()

game.print_menu()
# Prints:
# 1: New Game
# 2: Play Again
# 3: Quit

# Player chooses 1:

game.deal(5)
# Prints:
# (3,11) (3,12) (2,12) (1,13) (1,13)

```

Well how can game deal cards? Probably because we `extended` class `video_poker`.

I would start with your video_poker class first:
   
- First get some of your "winning hand functions" working. Start with the easier ones:
    - Flush 
    - Pair
    - Three of a Kind
    - Four of a Kind
    - etc. 

- Test your functions by dealing random hands, and seeing if you identify the methods you have implemented.
- Once you have most of your winning methods finished, add them to a game system. 
- Do text based first.
	- Using  a menu driven system:
	- Deal 5 cards
		- (1,3)(1,11)(2,5)(3,5)(1,8)
	- Let the user "hold" cards by entering 2,3 or something similar
	- Deal the second hand
		- (1,13)(3,5)(2,5)(3,5)(1,9)
	- Calculate the score
	    - Three of a kind = 3pts
	- Re-deal if desired

## Graphics Requirements (BONUS)
- A user will start the game with 0 points displayed somewhere in the upper right corner of the screen.
- The opening screen should have the "back" of five cards showing.
- Show the user a "Deal" button that when pressed will display 5 cards. This can already be present when the game is started. 
- After a hand is dealt, provide the user some way to "hold" some or all of the cards displayed on the deal (usually a checkbox, but doesn't have to be). 
- After the first deal, and the user holds some cards (or none of the cards), let the user re-deal replacing the non-held cards with new cards from he deck. 
- At this point, you should calculate thier score, show what they won (0 - 800) and update the total at the top right. 
- Documentation: http://mcsp.wartburg.edu/zelle/python/graphics/graphics.pdf


