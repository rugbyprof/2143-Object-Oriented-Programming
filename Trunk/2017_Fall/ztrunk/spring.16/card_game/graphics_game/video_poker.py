from graphics import *
import os
import random
import time


"""
This website gave me the asii idea. 
http://codereview.stackexchange.com/questions/82103/ascii-fication-of-playing-cards
"""

"""
@Class AsciiCard 
@Description:
    This class reads 53 (52 cards, and 1 back) ascii representations of a deck of cards from the given file.
@method get_ascii(string,int)
"""
class GameCardImage(object):

    suits = ['spades','hearts','diamonds','clubs']
    
    sizes = {'large':(500,726),
             'medium':(250,363),
             'small':(150,218),
             'xsmall':(100,145),
             'xxsmall':(75,109),
             'tiny':(),
             }
    
    def __init__(self,cards_dir="./card_images",back='back_black.gif',size='xsmall'):
        self.path = cards_dir
        self.card_back = back
        self.size = size
       

    """
    @Description:
        This method takes a card suit, and an integer between 2,14 inclusive and 
        returns the correpsoning ascii representation of that card. 
    @Example:
    """
    def get_card_face(self,suit=None,rank=None):
        if suit == None or rank == None:
            return self.path + self.card_back
            
        if type(suit) is str:
            suit = self.suits.index(suit)
            
        value = ((suit * 13) + rank) 
        
        if value < 10:
            value = '0'+ str(value)
        
        image = self.path+'/'+self.size+'/'+str(value)+'.gif'
        
        return image
        
    def get_card_back(self):
        return self.path+'/'+self.size+'/'+self.card_back  
         
    def set_card_back(self,path):
        self.card_back = path
        
    def set_card_size(self,size):
        self.card_size = size
        
        
    def set_card_dir(self,dir):
        self.path = dir
        
  
"""
@Class Card 
@Description:
    
"""
class Card(GameCardImage):
    def __init__(self, suit='', rank=0):
        super().__init__()
        
        # If user passes in an int between 0-3, then convert it to string
        # otherwise keep the string 
        if type(suit) is int:
            self.suit = self.suits[suit]
        else:
            self.suit = suit
            
        self.rank = rank
        self.card_image = self.get_card_face(self.suit,self.rank)

    def __str__(self):
        return ("(suit:%s , rank:%s , card_image:%s)") % (self.suit, self.rank, self.card_image)
           
    def __cmp__(self,other):
        t1 = self.suit,self.rank
        t2 = other.suit,other.rank
        return int(t1[1])<int(t2[1])
   
    # Python3 wasn't liking the __cmp__ to sort the cards, so 
    # documentation told me to use the __lt__ (less than) 
    # method.
    def __lt__(self,other):
        return self.__cmp__(other)
        
"""
@Class Deck 
@Description:
    This class represents a deck of cards. 
@Methods:
    pop_cards() - removes a card from top of deck
    add_card(card) - adds a card to bottom of deck
    shuffle() - shuffles deck
    sort() - sorts the deck based on value, not suit (could probaly be improved based on need)
"""       
class Deck(object):
    def __init__(self):
        #assume top of deck = 0th element
        self.cards = []
        for suit in range(4):
            for rank in range(2,15):
                self.cards.append(Card(suit,rank))
                
    def __str__(self):
        res = []
        for card in self.cards:
            res.append(str(card))
        return " ".join(res)
    
    def pop_card(self):
        return self.cards.pop(0)
        
    def add_card(self,card):
        self.cards.append(card)
        
    def shuffle(self):
        random.shuffle(self.cards)
    
    def sort(self):
        self.cards = sorted(self.cards)
        
        
       
"""
@Class: Hand 
@Extends: Deck
@Description:
    This class represents a hand of cards 
@Methods:
""" 
class Hand(object):
    def __init__(self,label=''):
        self.cards = []
        self.label = label
        self.rankCount = {}     # Used to calculate pairs, three of a kind, etc.
        self.suitCount = {}     # Used to calculate flush
        
    def addCard(self,card):
        
        if not card.suit in self.suitCount:
            self.suitCount[card.suit] = 1
        else:
            self.suitCount[card.suit] += 1
            
        if not card.rank in self.rankCount:
            self.rankCount[card.rank] = 1
        else:
            self.rankCount[card.rank] += 1  
            
        self.cards.append(card)
        
    def getCards(self):

        return self.cards
   
    def sortHand(self):
        self.cards = sorted(self.cards)
        
    def replaceCard(self,id,card):
        print(self.rankCount)
        print(self.suitCount)
        print(id)
        self.cards[id] = card
        
    def getPosition(self,card):
        return self.cards.index(card)
        
        
    def trashHand(self):
        self.cards = []
        self.rankCount = {}     # Used to calculate pairs, three of a kind, etc.
        self.suitCount = {}     # Used to calculate flush        
       
"""
@Class Video Poker 
@Description:
    This class handles all things video poker 
@Methods:
    deal() - deals a set number of cards 
    checkHand() - processes hand to see what hand possibilities there are
    pairs() - returns index of pairs if true
    twoPair() - uses pairs to determine 
    etc....
""" 
class VideoPoker(object):
    def __init__(self):
        self.deck = Deck()

    def deal(self,number=5):
        hand = Hand()
        self.deck.shuffle()

        for i in range(0,number):
            hand.addCard(self.deck.pop_card())
            
        return hand
        
    def getCard(self):
        return self.deck.pop_card()
            
    def checkHand(self,hand):
        for c in hand.getCards():
            pass

    def pair(self):
        pass
        
    def twoPair(self):
        pass
    
    def threeOfAKind(self):
        pass
    
    def flush(self):
        pass
    
"""
@Class ClickHandler
@Description:
    This class is extended by video poker to handle all of the image interaction.  
@Methods:
    addImage(x,y,w,h,path) - stores an images location, size and path  
    checkClicked(x,y) - returns the ID of an image that was clicked
    drawImage() - displays an image on the graphics window
    pushImage() - cheesy animation to "push" an image  
"""    
class clickHandler(object):
    def __init__(self,win):
        self.win = win
        self.clickages ={}
        self.id = 0
        
    def addImage(self,x,y,w,h,path):
        self.id += 1
        image = Image(Point(x,y),path)
        self.clickages[self.id] = {'path':path,'image':image,'x':x,'y':y,'w':w,'h':h}
        return self.id
        
    def checkClicked(self,x,y):
        print(x,y)
        for k, v in self.clickages.items():
            left = v['x'] - (v['w'] / 2)
            right = v['x'] + (v['w'] / 2)
            top = v['y'] - (v['h'] / 2)
            bottom = v['y'] + (v['h'] / 2)
            print(v)

            #print(left,right,top,bottom)
            #print("%4.0f >= %4.0f and %4.0f <= %4.0f and %4.0f <= %4.0f and %4.0f >= %4.0f" %(x,left,x,right,y,top,y,bottom))
            if x >= left and x <= right and y >= top and y <= bottom:
                return k
                
        return None
        
    def drawImage(self,id):
        self.clickages[id]['image'].draw(self.win)
        
    def pushImage(self,id):
        x = self.clickages[id]['x']
        y = self.clickages[id]['y']    
        img_down = Image(Point(x,y+3),self.clickages[id]['path'])

        #self.clickages[id]['image'].undraw()
        img_down.draw(self.win)
        time.sleep(.1)
        img_down.undraw()
        #self.clickages[id]['image'].draw(self.win)
        time.sleep(.1)
        
    def __str__(self):
        return ("(%s)") % (str(self.clickages))

"""
@Class Game
@Description:
    This is where I will put my game logic.  
@Methods:
    addImage(x,y,w,h,path) - stores an images location, size and path  
    checkClicked(x,y) - returns the ID of an image that was clicked
    drawImage() - displays an image on the graphics window
    pushImage() - cheesy animation to "push" an image  
"""  
class Game(clickHandler):
    
    def __init__(self,width,height):
        self.win = GraphWin("Video Poker", 800, 300)
        super().__init__(self.win)
        
        self.cardIDs = []
        
        self.vp = VideoPoker()
        self.hand = self.vp.deal()
        self.vp.checkHand(self.hand)
                
        exit_button = self.addImage(800-(24/2),12,24,24,'./images/exit_up.gif')
        
        self.drawImage(exit_button)
       
        self.draw_hand()
        
            
        loop = True
        while loop:
    
            click = self.win.getMouse()  # Pause to view result
            print(click.x,click.y)
            
            
            clicked = self.checkClicked(click.x,click.y)
            
            if clicked:
                
                try:
                    index = self.cardIDs.index(clicked)
                except ValueError:
                    "Card Not In List"
                else:
                    self.hand.replaceCard(self.cardIDs.index(clicked),self.vp.getCard())
                
                self.draw_hand()

                if clicked == exit_button:
                    self.pushImage(clicked)
                    loop = False
                    time.sleep(.3)
            
        self.win.close()     # Close window when done  
        
    def game_loop(self):
        pass
        
    def draw_hand(self):

        x = 100     # Starting x coord for first card
        y = 100     # Starting y coord for first card
        
        # Take our cards, and turn them into a list of graphics image type.
        cards = self.hand.getCards()
                
        for c in cards:
            print(c)
            #Add an image (graphics kind) to our list
            id = self.addImage(x,y,100,145,c.card_image)
            self.drawImage(id)
            self.cardIDs.append(id)
            
            #Move card right by 150 pixels
            x+= 150     
        
            
    def card_clicked(self,x,y):
        pass
        

        
if __name__=='__main__':

    g = Game(800, 300)