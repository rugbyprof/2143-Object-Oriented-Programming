class Point(object):
    def __init__(self,x=0,y=0):
        self.x = x
        self.y = y
        
    def __str__(self):
        return "(%d , %d)" % (self.x,self.y)
        
    def __add__(self,rhs):
        return Point(self.x + rhs.x,self.y + rhs.y )
    
    def __sub__(self,rhs):
        return Point(self.x - rhs.x,self.y - rhs.y )
        

if __name__=='__main__':
    p1 = Point(2,3)
    p2 = Point(3,4)
    p3 = p1 + p2
    
    print(p3)