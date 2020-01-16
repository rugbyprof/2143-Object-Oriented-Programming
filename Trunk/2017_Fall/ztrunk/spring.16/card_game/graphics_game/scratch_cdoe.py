
class card(object):
    def __init__(self,suit,rank):
        self.rank = rank
        self.suit = suit
        
    def __cmp__(self,rhs):
        return self.rank < rhs.rank 
        
    def __lt__(self,rhs):
        return self.__cmp__(rhs)
        
    def __str__(self):
        return "(%s,%s)" % (self.rank,self.suit)


hand = []

hand.append(card(1,11))
hand.append(card(1,11))
hand.append(card(1,12))
hand.append(card(1,13))
hand.append(card(1,14))

hand = sorted(hand)

for h in hand:
    print(h)

suitDict = {}
rankDict = {}


for card in hand:
    if not card.rank in rankDict:
        rankDict[card.rank] = 1
    else:
        rankDict[card.rank] += 1 
        
    if not card.suit in suitDict:
        suitDict[card.suit] = 1
    else:
        suitDict[card.suit] += 1 
        
print(suitDict)
print(rankDict)

print(len(rankDict.keys()))



def straight(hand):
    return (hand[4].rank - hand[0].rank) == 4 and len(hand) == 5 
    
def flush(suitDict):
    return len(suitDict.keys()) == 1
    
def straightFlush(hand,suitDict):
    return flush(suitDict) and straight(hand)
    
def royalFlush(hand,suitDict):
    return straightFlush(hand,suitDict) and hand[4].rank == 14

        
print(straight(hand))
print(flush(suitDict))
print(straightFlush(hand,suitDict))
print(royalFlush(hand,suitDict))