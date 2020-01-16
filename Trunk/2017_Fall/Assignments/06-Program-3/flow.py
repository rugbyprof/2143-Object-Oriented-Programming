
Colors = {
    'R':'Red',
    'G':'Green',
    'B':'Blue',
    'O':'Orange',
    'L':'Light Blue',
    'P':'Purple',
    'M':'Maroon',
    'K':'Pink'
}


def Force(m1=1,m2=1,d=1):
    G = 6.67 * pow(10,-11)
    F = (G*m1*m2) / (d * d)
    return F


class Cell(object):
    def __init__(self,row=None,col=None,color=None):
        self.occupied = False
        self.color = color
        self.location = [row,col]

    def __str__(self):
        return "[%s %s %s]" % (self.occupied,self.color,self.location)


class Grid(object):
    def __init__(self,data=None):
        data = data.strip()
        self.board = []
        row = 0
        for line in data.splitlines():
            self.board.append([])
            line = line.split()
            col = 0
            for val in line:
                self.board[-1].append(Cell(row,col,val))

    def __str__(self):
        string = ""
        for row in self.board:
            for cell in row:
                string += cell.__str__() + ' '
            string += "\n"
        return string
 
class FlowGame(object):
    pass


if __name__=='__main__':
    
    data ='''
    0 O B 0 0 G
    0 0 0 0 0 0
    0 0 Y R 0 0
    0 0 0 L 0 B
    0 R Y 0 L O
    0 0 0 0 0 0
    '''

    data ='''
    0 0 0 0 0 0 0
    B Y 0 0 0 L G
    O B 0 0 0 0 R
    0 0 Y 0 0 0 0
    0 0 0 0 0 L 0
    0 0 0 O 0 G 0
    R 0 0 0 0 0 0
    '''


    G = Grid(data)
    print(G)
