import collections.abc
class SomeApplicationClass( collections.abc.Callable ):
    pass


class Card:
    insure= False
    def __init__( self, rank, suit, hard, soft ):
        self.rank= rank
        self.suit= suit
        self.hard= hard
        self.soft= soft

    def __repr__( self ):
        return "{__class__.__name__}(suit={suit!r}, rank={rank!r})".format(__class__=self.__class__, **self.__dict__)
    def __str__( self ):
        return "{rank}{suit}".format(**self.__dict__)

class NumberCard( Card ):
    def __init__( self, rank, suit ):
        super().__init__( str(rank), suit, rank, rank )

class AceCard( Card ):
    def __init__( self, rank, suit ):
        super().__init__( "A", suit, 1, 11 )

class FaceCard( Card ):
    def __init__( self, rank, suit ):
        super().__init__( {11: 'J', 12: 'Q', 13: 'K' }[rank], suit,10, 10 )

class Hand:
    def __init__( self, dealer_card, *cards ):
        self.dealer_card= dealer_card
        self.cards= list(cards)
    def __str__( self ):
        return ", ".join( map(str, self.cards) )
    def __repr__( self ):
        return "{__class__.__name__}({dealer_card!r}, {_cards_str})".format(__class__=self.__class__,_cards_str=", ".join( map(repr, self.cards) ),**self.__dict__ )

x=NumberCard( '2', '♣')

h = Hand(NumberCard( '2', '♣'),NumberCard( '10', '♣'),NumberCard( '12', '♣'),NumberCard( '6', '♣'))

print(str(x))
print(repr(x))
print(x)
print(repr(h))