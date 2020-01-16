import random

class gol(object):

    def __init__(self,width=10,height=10):
    
        random.seed(345)
    
        self.height = height 
        self.width = width
        self.board = [i for i in range(self.height)]
        for i in range(self.height):
            self.board[i] = [0 for j in range(self.width)]
            
        self.loadRandomLives(.5)
      
        
    def __str__(self):
        string = ""
        
        for row in self.board:
            for col in row:
                string += str(col) + ' '
            string += "\n"
        return string
        
        
    def loadRandomLives(self,density):
        """
        @function: initRandGen
        @description: Initializes a random generation 
        @param: float - density (how many lives to create)
        @returns: list - 2D list containing zeros and ones
        """     
        
        numberOfLives = int(self.width * self.height * density)
        
        for i in range(numberOfLives):
                row = random.randint(0, self.height-1)
                col = random.randint(0, self.width-1)
                self.board[row][col] = self.randomLife()
        

    def randomLife(self):
        """
        @function: randomLife
        @description: Generates a random life (zero or one)
        @param: none
        @returns: int - zero or one (alive or dead)
        """    
        if random.random() > .5:
            x = 1
        else:
            x = 0
        return x    
        
        
    def liveOrDie(self,r,c):
        """
        @function: liveOrDie
        @description: Calculates whether a cell lives or dies based on Game of Life rules
        @param: int x - Column to check
        @param: int y - Row to check
        @returns: Int : 0 = nothing changes , -1 = dies , 1 = birth
        """  
        neighbors = 0
                
        rows = [r-1,r,r+1]
        cols = [c-1,c,c+1]
        
        rows = rows[1:] if rows[0] < 0 else rows
        rows = rows[:-1] if rows[-1] >= self.height else rows
        cols = cols[1:] if cols[0] < 0 else cols
        cols = cols[:-1] if cols[-1] >= self.width else cols        
        
        for i in rows:
            for j in cols:
                neighbors += self.board[i][j]
                         
        alive = self.board[r][c]        

        if(alive):
            if neighbors == 2 or neighbors == 3:
                return 1 
        else:
            if neighbors == 3:
                return 1
                
        return 0 
        
        
if __name__=='__main__':
        
    g = gol(10,10)
    print(g)
    print((9,9),g.liveOrDie(9,9))
    print((0,0),g.liveOrDie(0,0))
    print((0,2),g.liveOrDie(0,2))
    print((5,6),g.liveOrDie(5,6))
    print((3,7),g.liveOrDie(3,7))
    print((7,5),g.liveOrDie(7,5))
    print((7,8),g.liveOrDie(7,8))