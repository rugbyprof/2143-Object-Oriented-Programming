import random


class Dice(object):
    """
    @Class: Dice
    @Description: 
        Represents a single "die" with X number of sides.
    @Methods:
        Roll - Rolls the dice and returns a value between 1 and "number of sides" 
    """
    def __init__(self,num_sides=6):
        self.NumSides = num_sides

    def Roll(self):
        return random.randint(1,self.NumSides)  

##############################################################################
##############################################################################


class Pig(object):
    """
    @Class: Pig
    @Description: 
        Represents the game of pig (dice game)
    @Methods:
        Roll - Rolls the "die" or "dice" and returns a list of rolled values
    """
    def __init__(self,num_dice=1,dice_sides=6,skunk_value=1):
        self.NumDice = num_dice
        self.DiceSides = dice_sides
        self.DiceList = []
        self.SkunkValue = skunk_value
        for i in range(self.NumDice):
            self.DiceList.append(Dice(self.DiceSides))

    def Roll(self):
        """
        @Method: Roll
        @Description: 
            One roll in a pig game, with 1 to NumDice per roll
        @Returns: int: [0=skunk value occured, total of all dice otherwise]
        """ 
        scores = []
        for d in self.DiceList:
            scores.append(d.Roll())
            if self.SkunkValue in scores:
                return 0 
        return sum(scores)

##############################################################################
##############################################################################

class Player(object):
    def __init__(self,name,num_dice=1,strategy=('Random',7)):
        self.Name = name        # My name
        self.TotalScore = 0     # Total score
        self.LastScore = 0      # Score on last turn
        self.LastNumRolls = 0   # Last number of rolls
        self.Opponents = {}     # Dict of opponents
        self.NumDice = num_dice
        self.Strategy = strategy[0]
        self.pig = Pig(num_dice)# init pig game 
        self.Strategies = {
                'Target_Score':0,
                'Target_Rolls':0,
                'Sprint_To_Finish':0,
                'Mimic_Opponent':0,
                'Situational':0,
                'Random':0
            }
        self.Strategies[strategy[0]] = strategy[1]


    def AddOpponents(self,opponent):
        """
        @Method: AddOpponents
        @Description: Adds an opponent, or list of opponents (as long as it's not me) to a dictionary with name and score.
            Example: {
                       'bob':0.
                       'sue':0
                     }

        @Params: [] - Opponents
        @Returns: None
        """
        # if not type(opponent) == list and not opponent.Name == self.Name:
        #     self.Opponents[opponent.Name] = opponent
        # else:
        for op in opponent:
            if not op.Name == self.Name:
                self.Opponents[op.Name] = op


    def __str__(self):
        """
        @Method: __str__
        @Description: Prints out a nice version of self
        @Returns: string representation
        """
        tmp = " "
        for k,v in self.Opponents.items():
            tmp = tmp + "[" + k + " " + str(v.TotalScore) + "," + str(v.LastScore) + "," + str(v.LastNumRolls) + "] "
        return "Name: %s, TotScore: %s, LastScore: %s, LastNumRolls: %s, Opponents: %s" % (self.Name,self.TotalScore,self.LastScore,self.LastNumRolls,tmp)
        

    def __repr__(self):
        """
        @Method: __repr__
        @Description: Calls __str__
        @Returns: a call to __str__
        """
        return self.__str__()
        


    def SetStrategy(self,strategy,value):
        """
        @Method: SetStrategy
        @Description: Sets the current strategy for the player
        @Params:
            strategy: string 
            value: int    
        @Returns: None
        @Usage:
                SetStrategy('Target_Score',20)
                SetStrategy('Target_Rolls',5)     
                SetStrategy('Sprint_To_Finish',72)    
        """
        if strategy in self.Strategies:
            self.Strategies[strategy] = value
        else:
            raise ValueError('The strategy does not exist!')


    def Roll(self):
        """
        @Method: PlayerRoll
        @Description: Implements a turn for a player. If the player rolls a 1 at any time zero is returned, 
                      otherwise the total of the rolls is returned.
        @Params:
            string: player
            int: max rolls 
        @Returns: int: total
        """
        if self.Strategy == 'Random':
            Score,NumRolls = self.RandomRoll()
        elif self.Strategy == 'Aggressive':
            pass
        elif self.Strategy == 'Cautious':
            pass
        elif self.Strategy == 'Robust':
            pass
        elif self.Strategy == 'CopyCat':
            pass
        
        self.TotalScore += Score
        self.LastScore = Score
        self.LastNumRolls = NumRolls
        
        
    def RandomRoll(self):
        Score = 0
        NumRolls = 0
        for i in range(random.randint(1,self.Strategies['Random'])):
            NumRolls += 1
            roll = self.pig.Roll()
            if roll == 0:
                break
            Score += roll
        
        return (Score,NumRolls)

            
    def Aggressive(self):
        pass
        
    def Cautious(self):
        pass

    def Robust(self):
        pass
        
    def CopyCat(self):
        pass



##############################################################################
##############################################################################

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
        self.WinnerName = None                      # no winner yet
        
        # initialize all players
        self.AddPlayers(kwargs['players'])
            
        self.StartGame()
        
    def __str__(self):
        string = ""
        for name,obj in self.Players.items():
            string += obj.__str__() + "\n"
        return string
        

    def AddPlayers(self,players):
        """
        @Method: AddPlayers
        @Description: Adds a new player or players to the game
            Example: {
                       'bob':<player_object>
                       'sue':<player_object>
                     }

        @Params: [] - players
        @Returns: None
        """
        if not type(players) == list:
            self.Players[players.Name] = players
        else:
            for p in players:
                self.Players[p.Name] = p
                    
     
    def StartGame(self):
        """
        @Method: WinnerExists
        @Description: Checks to see if a player has acheived the target score.
        @Params:None
        @Returns: bool
        """    
        self.UpdatePlayerOpponents()
        
        # Main game loop
        while not self.WinnerExists():
            print(self)
            for name,PlayerObj in self.Players.items():
                PlayerObj.Roll()
       

    def WinnerExists(self):
        """
        @Method: WinnerExists
        @Description: Checks to see if a player has acheived the target score.
        @Params:None
        @Returns: bool
        """
        for name,PlayerObj in self.Players.items():
            if PlayerObj.TotalScore >= self.TargetScore:
                self.WinnerName = PlayerObj.Name
                return True
        self.WinnerName = None
        return False


    def Winner(self):
        """
        @Method: Winner
        @Description: Returns the winner, if there is one.
        @Params:None
        @Returns: [string,None]: Players name or None
        """        
        return self.WinnerName
        

    def UpdatePlayerOpponents(self):
        """
        @Method: UpdatePlayerOpponents
        @Description: Gives a copy of each player in the game, to every other player in the game. 
        @Params:None
        @Returns: None
        """   
        for name,PlayerObj in self.Players.items():
            PlayerObj.AddOpponents(self.Players.values())

##############################################################################
##############################################################################



def main():

    p1 = Player('ann')
    p2 = Player('bob')
    p3 = Player('sue')
    p4 = Player('dax')
    
    AllPlayers = [p1,p2,p3,p4]
    
    # Param values to initialize a pig game instance
    kwargs = {'num_dice':1,'random_roles':9,'target_score':100,'players':AllPlayers}

    g = Game(**kwargs)
    
    print(g)
    
    
main()
