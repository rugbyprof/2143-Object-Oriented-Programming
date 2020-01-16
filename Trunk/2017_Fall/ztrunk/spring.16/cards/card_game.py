import random

#http://codereview.stackexchange.com/questions/82103/ascii-fication-of-playing-cards

class Card(object):
    """represents a standard playing card."""
    
    suit_names = ['Clubs', 'Diamonds', 'Hearts', 'Spades']
    suits_symbols = ['♠', '♦', '♥', '♣']
    rank_names = [None, 'Ace', '2', '3', '4', '5', '6', '7','8', '9', '10', 'Jack', 'Queen', 'King']

    def __init__(self, suit=0, rank=2):
        self.suit = suit
        self.rank = rank
        
    def __str__(self):
        return '%s of %s' % (Card.rank_names[self.rank],
                             Card.suit_names[self.suit])        
                             
    def __cmp__(self, other):
        # check the suits
        if self.suit > other.suit: return 1
        if self.suit < other.suit: return -1

        # suits are the same... check ranks
        if self.rank > other.rank: return 1
        if self.rank < other.rank: return -1

        # ranks are the same... it's a tie
        return 0 
        
    def __cmp__(self, other):
        t1 = self.suit, self.rank
        t2 = other.suit, other.rank
        return cmp(t1, t2)  
                            
class Deck(object):

    def __init__(self):
        self.cards = []
        for suit in range(4):
            for rank in range(1, 14):
                card = Card(suit, rank)
                self.cards.append(card)
                
    def __str__(self):
        res = []
        for card in self.cards:
            res.append(str(card))
        return '\n'.join(res)

    def pop_card(self):
        return self.cards.pop()
        
    def add_card(self, card):
        self.cards.append(card)

    def shuffle(self):
        random.shuffle(self.cards)
        
    def sort(self):
        self.cards = sorted(self.cards)
        
    def move_cards(self, hand, num):
        for i in range(num):
            hand.add_card(self.pop_card())
            
    """
    Write a Deck method called deal_hands that takes two parameters, the number of hands and the number of cards 
    per hand, and that creates new Hand objects, deals the appropriate number of cards per hand, and returns a 
    list of Hand objects.
    """        
    def deal_hands(self,num_hands,num_cards):
        pass

class Hand(Deck):
    def __init__(self, label=''):
        self.cards = []
        self.label = label
   
    def is_sequence(self):
        pass
        
    def is_flush(self):
        pass

        
if __name__=='__main__':
    card1 = Card(2, 11)
    print(card1)
    deck = Deck()
    #print(deck)
    deck.shuffle()
    #print(deck)
    deck.sort()
    deck.shuffle()
    hand = Hand('new hand')
    print(hand)
    hand.add_card(deck.pop_card())
    print(hand)
    deck.move_cards(hand,5)
    print(hand)
    print(len(deck.cards))
    club = u"\u2663"
    print(club)
    