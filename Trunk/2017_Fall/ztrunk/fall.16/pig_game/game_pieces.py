import random
import threading

class Card(object):
    """
    Represents a card in a standard deck of cards.
    A card has 2 properties: a suit and a rank.
    Instances of this class may be compared for equality using the == operator.
    """

    SPADE = "spade"
    HEART = "heart"
    CLUB = "club"
    DIAMOND = "diamond"

    RANK_NAMES = {
        1: "ace",
        11: "jack",
        12: "queen",
        13: "king",
    }

    SUIT_NAMES = {
        SPADE: "spades",
        HEART: "hearts",
        CLUB: "clubs",
        DIAMOND: "diamonds",
    }

    def __init__(self, suit, rank):
        """
        Initializes a new instance of this class.
        *suit* is the suit of the card, and must be equal to one of the
        following constants defined in this class: SPADE, HEART, CLUB, DIAMOND.
        *rank* must be an integer whose value is the rank of the card; the
        valid range is 1 to 13, inclusive, where 1 is the ace, 11 is the Jack,
        12 is the Queen, and 13 is the king.
        """
        self.suit = suit
        self.rank = rank


    def __eq__(self, other):
        """
        Compares another object to this object for equality.
        The object is considered to be "equal" if it has both a "suit" and a
        "rank" attribute with values that compare equal using the == operator
        to the corresponding attributes of this object.
        """
        try:
            other_suit = other.suit
            other_rank = other.rank
        except AttributeError:
            return False
        else:
            return self.suit == other_suit and self.rank == other_rank


    def __str__(self):
        """
        Creates a human-friendly string representation of this object, and
        returns it.  For example, if rank==1 and suit==CLUBS then "ace of clubs"
        is returned.
        """
        if self.rank in self.RANK_NAMES:
            rank_name = self.RANK_NAMES[self.rank]
        else:
            rank_name = self.rank

        if self.suit in self.SUIT_NAMES:
            suit_name = self.SUIT_NAMES[self.suit]
        else:
            suit_name = self.suit

        return "{} of {}".format(rank_name, suit_name)


    def __repr__(self):
        """
        Creates a Python-friendly string representation of this object, and
        returns it.  For example, if rank==1 and suit==CLUBS then Card(clubs, 1)
        is returned.
        """
        return "Card({!r}, {!r})".format(self.suit, self.rank)

################################################################################

class Deck(list):
    """
    A deck of cards.  This class is a specialization of the built-in list type
    for holding the cards in a deck of cards.  Each element of the list must be
    a Card object.  The "bottom" of the deck is index 0.  Instances of this
    class are *not* thread-safe; however, this class has a "lock" attribute that
    can be acquired by multiple threads to safely perform concurrent access.
    This class also implements the context manager protocol to better implement
    acquiring the lock with the "with" statement.
    """

    def __init__(self, *args, **kwargs):
        """
        Initializes a new instance of this class.
        All positional and keyword arguments are passed verbatim to the
        constructor of the superclass.
        If no positional or keyword arguments are given, then the list is
        initialized by reset().
        """
        super(Deck, self).__init__(*args, **kwargs)
        if not args and not kwargs:
            self.reset()
        self.lock = threading.RLock()


    def reset(self):
        """
        Resets the deck back to the "factory" state.
        All cards in this deck will be discarded and the deck will be
        re-populated with the 13 different-ranked cards of each suit in
        ascending order.
        """
        self[:] = self.iter_cards()


    def draw(self):
        """
        Draws a card from this deck.
        The Card object at the highest index of this list is removed and
        returned.  IndexError is raised if this list is empty.
        """
        return self.pop()


    def shuffle(self):
        """
        Shuffles the cards in this deck using complete randomness.
        """
        random.shuffle(self)


    def shuffle_3waycut(self, split_index_1=None, split_index_2=None):
        """
        Shuffles the cards in this deck using a "3-way cut" style.
        This is done by dividing the deck into 3 piles of random size and then
        recombining them in a random order.  If there are fewer than 3 cards in
        the deck then this method simply calls shuffle(), as there is no way to
        do a 3-way-split with less than 3 cards.
        *split_index_1* and *split_index_2* must be integers whose values are
        the indices within the array at which the splits take place.  They may
        both be None (the default) to choose a random value.  split_index_1
        must be less than or equal to split_index_2.  Note that these two values
        are normally not specified; they are included in the parameter list to
        facilitate unit testing.
        """
        if len(self) < 3:
            self.shuffle()
            return

        if split_index_1 is None:
            split_index_1 = random.randint(1, len(self) - 2)
        if split_index_2 is None:
            split_index_2 = random.randint(split_index_1 + 1, len(self) - 1)
        chunk1 = self[:split_index_1]
        chunk2 = self[split_index_1:split_index_2]
        chunk3 = self[split_index_2:]
        chunks = [chunk1, chunk2, chunk3]
        random.shuffle(chunks)
        del self[:]
        for chunk in chunks:
            self.extend(chunk)


    def shuffle_riffle(self):
        """
        Shuffles the cards in the deck using the "riffle" technique.
        According to Wikipedia, riffle is a shuffling technique "in which half
        of the deck is held in each hand with the thumbs inward, then cards are
        released by the thumbs so that they fall to the table interleaved.
        """
        num_cards = len(self)

        # nothing to do if deck is empty or only has 1 card
        if num_cards <= 1:
            return

        # find a uniform interval about the center of the deck;
        # the "leeway" simulates how closely a human will find the true center,
        # with increasing accuracy as the deck gets smaller
        mid = num_cards / 2
        leeway = num_cards / 10
        mid_left = mid - leeway
        if mid_left < 1:
            mid_left = 1
        mid_right = mid + leeway
        if mid_right > num_cards - 1:
            mid_right = num_cards - 1

        # split the deck into two halves, choosing the split point randomly
        # within the "leeway" of the true center, as calculated above
        split_index = random.randint(mid_left, mid_right)
        left = self[:split_index]
        right = self[split_index:]

        # remove all cards from the deck;
        # they will be added back in the loop below as they are "fanned"
        del self[:]

        # continue contributing cards from the left and right piles until both
        # are empty
        while left or right:

            # size_difference is used to simulate how a human will tend to
            # "even out" the left and right piles should one start getting
            # noticeably smaller than the other
            size_difference = len(right) - len(left)

            # contribute a few cards from the right hand, if the pile isn't too
            # much bigger than the one in the left hand
            if size_difference > -5:
                n = random.randint(1, 3)
                while right and n > 0:
                    self.append(right.pop(0))
                    n -= 1

            # contribute a few cards from the left hand, if the pile isn't too
            # much bigger than the one in the right hand
            if size_difference < 5:
                n = random.randint(1, 3)
                while left and n > 0:
                    self.append(left.pop(0))
                    n -= 1


    @staticmethod
    def iter_cards():
        """
        A generator function that yields each of the unique cards in a 52-card
        deck as Card objects, grouped by suit and in decreasing order of rank,
        from King down to Ace.
        """
        for suit in (Card.CLUB, Card.DIAMOND, Card.HEART, Card.SPADE):
            for rank in (13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1):
                yield Card(suit, rank)


    def __enter__(self):
        """
        Acquire the lock when we are "entered" with the "with" statement.
        """
        self.lock.acquire()
        return self


    def __exit__(self, exc_type, exc_value, traceback):
        """
        Release the lock when the "with" statement exits.
        """
        self.lock.release()

class Dice(object):
	def __init__(self,num_sides=6):
		self.NumSides = num_sides
		
	def Roll(self):
		return random.randint(1,self.NumSides)

class GenerateTurnValue(object):
    def __init__(self):
        self.Dice = Dice()
        self.Deck = Deck()
        self.Deck.shuffle()

    def Roll(self):
        return self.Dice.Roll()

    def Draw(self):
        return self.Deck.draw()

def main():
    T = GenerateTurnValue()
    print(T.Roll())
    print(T.Draw())

if __name__=='__main__':
    main()