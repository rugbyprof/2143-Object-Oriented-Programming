import time
import os
import random
import platform         # Used to determine if running on windows linux or osx


class golBoard(object):
    """
    An introduction to python using the game of life as a problem to solve in class.
    Not the most pythonic or succinct solution, but it's not meant to be.

    Any live cell with fewer than two live neighbours dies, as if caused by under-population.
    Any live cell with two or three live neighbours lives on to the next generation.
    Any live cell with more than three live neighbours dies, as if by over-population.
    Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
    """
    def __init__(self,rows=20,cols=20,populate=False,Density=.25):
        random.seed()
        self.width = cols
        self.height = rows

        if populate:
            self.currentGen = self.initRandGen(Density)
        else:
            self.currentGen = self.initGen()
            
        self.nextGen = self.initGen()

    def __str__(self):
        return "width:%d height:%d" % (self.width,self.height)      

        
    def makeAlive(self,row,col):
        """
        @function: makeAlive
        @description: Adds a life to specified location 
        @param: int x - Column to add life
        @param: int y - Row to add life
        @returns: None
        """ 
        self.currentGen[row-1][col-1] = 1

        
       
    def computeNextGen(self):
        """
        @function: computeNextGen
        @description: Computes the next generation of our cellular automata 
        @param: None
        @returns: None
        """     
        for row in range(self.height):
            for col in range(self.width):
                self.nextGen[row][col] = self.liveOrDie(row,col)
    
    def copyNextGen(self):
        """
        @function: copyNextGen
        @description: Copies the next generation (after calculated) to our current generation  
        @param: None
        @returns: None
        """  
        for row in range(self.height):
            for col in range(self.width):
                self.currentGen[row][col] += self.nextGen[row][col] 
        

    def liveOrDie(self,r,c):
        """
        @function: liveOrDie
        @description: Calculates whether a cell lives or dies based on Game of Life rules
        @param: int x - Column to check
        @param: int y - Row to check
        @returns: Int : 0 = nothing changes , -1 = dies , 1 = birth
        """    

        alive = self.currentGen[r][c]

        neighbors = self.getNeighborWindow(r,c)
        
        count = 0
        
        for i,j in neighbors:
            count += self.currentGen[i][j]

        if(alive):
            if count < 2 or count > 3:
                return -1 
            else:
                return 0
        else:
            if count == 3:
                return 1
            else:
                return 0 
        
 
    def getNeighborWindow(self,r,c):
        """
        @function: getNeighborWindow
        @description: Gets the neighbors of a cell 
        @param: int r - Row to check
        @param: int c - Col to check
        @returns: List : List neighboring tuples (e.g. [(1,1),(1,2),(1,3)] ) 
        """     
        neighbors = []
        srow = r - 1
        scol = c - 1

        if srow  < 0:
            srow = 0

        if scol < 0:
            scol = 0

        erow = r + 1
        ecol = c + 1

        if erow >= self.height:
            erow = self.height - 1

        if ecol >= self.width:
            ecol = self.width-1

        for i in range(srow,erow+1):
            for j in range(scol,ecol+1):
                if i == r and j == c:
                    continue
                neighbors.append((i,j))

        return neighbors            
                      
                    
        
    def initGen(self):
        """
        @function: initGen
        @description: Initializes a single generation 
        @param: None
        @returns: list - 2D list containing zeros
        """     
        #return [[False] * self.width for row in range(self.height)]
        
        board = [i for i in range(self.height)]
        for i in range(self.height):
            board[i] = [0 for j in range(self.width)]
        return board      
    
    
       
    def initRandGen(self,density):
        """
        @function: initRandGen
        @description: Initializes a random generation 
        @param: float - density (how many lives to create)
        @returns: list - 2D list containing zeros and ones
        """     
        gen = self.initGen()
        
        numberOfLives = int(self.width * self.height * density)
        
        for i in range(numberOfLives):
                row = random.randint(0, self.height-1)
                col = random.randint(0, self.width-1)
                gen[row][col] = self.randomLife()
        return gen
        

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


    def stringifyWorld(self,current=True):
        """
        @function: stringifyWorld
        @description: Creates a string version of the 2D list representing our world with colors!
        @param: none
        @returns: string - a string version of our world
        """
        
        """ Unicode characters makes it Sloooooooow"""
        chars = {
            -1:u' \u2689',
            0:"  ",
            1:u' \u2689'
        }
        
        """ not really used either, used colored backgrounds instead """
        chars = {
            -1:" X",
            0:" .",
            1:" X"
        }
        
        
        colors = {
            "dead": ';'.join([str(0), str(31), str(41)]),
            "nada": ';'.join([str(3), str(37), str(47)]),
            "live": ';'.join([str(0), str(30), str(40)]),
            "new" : ';'.join([str(0), str(32), str(42)])
        }
        
        string = "\n"

        
        if current == True:
            for row in self.currentGen:
                for cell in row:
                    if cell == 0:
                        format = colors["nada"]
                        string += '\x1b[%sm%s\x1b[0m' % (format,chars[0])
                    else:
                        format = colors["live"]
                        string += '\x1b[%sm%s\x1b[0m' % (format,chars[1])
                string += "\n"
            return string 
        else:
            for r in range(self.height):
                for c in range(self.width):
                    nval = self.nextGen[r][c]
                    cval = self.currentGen[r][c]
                    
                    if nval == -1:
                        format = colors["dead"]
                        string += '\x1b[%sm%s\x1b[0m' % (format,' X')
                    elif nval == 1:
                        format = colors["new"]
                        string += '\x1b[%sm%s\x1b[0m' % (format,' X')
                    else:
                        format = colors["nada"]
                        string += '\x1b[%sm%s\x1b[0m' % (format,chars[cval])      
                                          
                string += "\n"
                
            return string 
     
              

def clearScreen():
    """
    @function: clearScreen
    @description: Clears the terminal screen
    @param: None
    @returns: None 
    """
    if platform.system() == 'Darwin':
        os.system('clear')
    else:
        os.system('cls')

def printList(mylist):
    string = ""
    for rows in range(len(mylist)):
        for cols in range(len(mylist)):
            string += "%d " % (mylist[rows][cols])
        string+= "\n"
    print string
    
def print_format_table():
    """
    prints table of formatted text format options
    """
    for style in xrange(8):
        for fg in xrange(30,38):
            s1 = ''
            for bg in xrange(40,48):
                format = ';'.join([str(style), str(fg), str(bg)])
                s1 += '\x1b[%sm %s \x1b[0m' % (format, format)
            print s1
        print '\n'
    
    def genericprint():
        for i in range(self.height):
            for j in range(self.width):
                print self.currentGen[i][j]
                
def getTerminalSize():
    import os
    env = os.environ
    def ioctl_GWINSZ(fd):
        try:
            import fcntl, termios, struct, os
            cr = struct.unpack('hh', fcntl.ioctl(fd, termios.TIOCGWINSZ,
        '1234'))
        except:
            return
        return cr
    cr = ioctl_GWINSZ(0) or ioctl_GWINSZ(1) or ioctl_GWINSZ(2)
    if not cr:
        try:
            fd = os.open(os.ctermid(), os.O_RDONLY)
            cr = ioctl_GWINSZ(fd)
            os.close(fd)
        except:
            pass
    if not cr:
        cr = (env.get('LINES', 25), env.get('COLUMNS', 80))

        ### Use get(key[, default]) instead of a try/catch
        #try:
        #    cr = (env['LINES'], env['COLUMNS'])
        #except:
        #    cr = (25, 80)
    return int(cr[1]), int(cr[0])


x,y = getTerminalSize()

rows = int(y * .95)
cols = int(x * .48)

generations = 30
density = .25
sleep = .05


b = golBoard(rows,cols,True,density)


for i in range(1000):
    clearScreen()
    print(b.stringifyWorld(True))
    b.computeNextGen()
   # time.sleep(1)
    #clearScreen()
    #print(b.stringifyWorld(False))
    b.copyNextGen()
    time.sleep(.01)
    
# print_format_table()