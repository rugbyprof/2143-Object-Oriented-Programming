import random
import abc

"""
@Class: Dice
@Description: 
    Represents a single "die" with X number of sides.
@Methods:
    Roll - Rolls the dice and returns a value between 1 and "number of sides" 
"""
class Dice(object):
    def __init__(self,num_sides=6):
        self.NumSides = num_sides

    def Roll(self):
        return random.randint(1,self.NumSides)  

"""
@Class: Pig
@Description: 
    Represents the game of pig (dice game)
@Methods:
    Roll - Rolls the "die" or "dice" and returns a list of rolled values
"""
class Pig(object):
    def __init__(self,num_dice=1,dice_sides=6,skunk_value=1):
        self.NumDice = num_dice
        self.DiceSides = dice_sides
        self.DiceList = []
        self.SkunkValue = skunk_value
        for i in range(self.NumDice):
            self.DiceList.append(Dice(self.DiceSides))
    """
    @Method: Roll
    @Description: 
        One roll in a pig game, with 1 to NumDice per roll
    @Returns: int: [0=skunk value occured, total of all dice otherwise]
    """ 
    def Roll(self):
        scores = []
        for d in self.DiceList:
            scores.append(d.Roll())
            if self.SkunkValue in scores:
                return 0 
        return sum(scores)

"""
This Class represents one instance of a game with X players rolling X dice playing to a score of X.
"""
class Game(object):
    """
    @Method: Init
    @Description: Initializes a pig game instance
    @Params:
        list: Players - A list of player names
        int: NumDice - Number of dice per roll
        int: RandomRolls - Top value of random range for rolls
        int: TargetScore - Target score to trigger a winner
    @Returns: None
    """
    def __init__(self, **kwargs):
        self.Players = {}                           # player dictionary
        self.NumDice = kwargs['num_dice']           # number of dice per roll
        self.RandomRolls = kwargs['random_roles']   # max num random rolls
        self.TargetScore = kwargs['target_score']   # game winning score
        self.pig = Pig(self.NumDice)                  # init pig game 
        self.WinnerName = None                      # no winner yet
        
        # initialize all players score to zero
        for p in kwargs['players']:             
            self.Players[p] = 0
            
        # Main game loop
        while not self.WinnerExists():
            for p,s in self.Players.items():
                self.Players[p] +=  self.PlayerRoll(p,self.RandomRolls)

                if self.Winner():
                    self.WinnerName =  self.Winner()
                
    """
    @Method: PlayerRoll
    @Description: Implements a turn for a player. If the player rolls a 1 at any time zero is returned, 
                  otherwise the total of the rolls is returned.
    @Params:
        string: player
        int: max rolls 
    @Returns: int: total
    """
    def PlayerRoll(self,player,number_rolls):
        total = 0
        for i in range(random.randint(1,number_rolls)):
            roll_value = self.pig.Roll()
            if roll_value == 0:
                return 0
            total +=  roll_value

        return total
        
    """
    @Method: WinnerExists
    @Description: Checks to see if a player has acheived the target score.
    @Params:None
    @Returns: bool
    """
    def WinnerExists(self):
        for player_name,score in self.Players.items():
            if score >= self.TargetScore:
                self.WinnerName = player_name
                return True
        self.WinnerName = None
        return False

    """
    @Method: Winner
    @Description: Returns the winner, if there is one.
    @Params:None
    @Returns: [string,None]: Players name or None
    """
    def Winner(self):
        return self.WinnerName


class GenericPlayer(object):
    __metaclass__ = abc.ABCMeta
    def __init__(self,name):
        self.Name = name
        self.Score = 0
        self.LastTurn = 0
        self.Opponents = {}

    def AddOpponents(self,opponent):
        if not type(opponent) == list:
            self.Opponents[opponent.Name] = opponent
        else:
            for op in opponent:
                self.Opponents[op.Name] = op

    def __str__(self):
        tmp = " "
        for k,v in self.Opponents.items():
            tmp = tmp + "[" + k + " " + str(v.Score) + "," + str(v.LastTurn) + "] "
        return "Name: %s, Score: %s, LastTurn: %s, Opponents: %s" % (self.Name,self.Score,self.LastTurn,tmp)

    def __repr__(self):
        return self.__str__()

    @abc.abstractmethod
    def Roll(self):
        pass


class AggressivePlayer(GenericPlayer):
    def __init__(self,name):
        super().__init__(name)

    def Roll(self):
        pass

def simulation():

    num_players = 5
    possible = ['ann','bob','sue','bill','ace','dax','erl','fox','gob','hal']
    players = []

    # Add specified number of players to the list
    for i in range(num_players):
        players.append(possible[i])

    # Create an empty dictionary to keep track of player wins
    PlayerWins = {}

    # How many rounds to run our mini simulation
    total_rounds = 10000

    # Init each player number of wins to 0
    for p in players:
        PlayerWins[p] = 0

    # Param values to initialize a pig game instance
    kwargs = {'num_dice':2,'random_roles':7,'target_score':100,'players':players}

    # Play a game for how ever many rounds in "total_rounds"
    for i in range(total_rounds):
        g = Game(**kwargs)
        PlayerWins[g.Winner()] += 1 # Get winner for current game, and add 1 to the dictionary

    # Print the dictionary with number of wins per player
    print(PlayerWins)

    # Convert sum of wins to percentages
    for p in PlayerWins:
        PlayerWins[p] /= total_rounds

    print(PlayerWins)

if __name__=='__main__':
    #simulation()

    p1 = GenericPlayer('ann')
    p2 = GenericPlayer('bob')
    p3 = GenericPlayer('sue')

    p1.AddOpponents(p2)
    p2.AddOpponents(p1)
    p1.AddOpponents(p3)
    p2.AddOpponents(p3)
    p3.AddOpponents([p1,p2])

    p4 = AggressivePlayer('joey')

    p4.Roll()

    p1.Score=12

    print(p1)
    print(p2)
    print(p3)
    print(p4)








