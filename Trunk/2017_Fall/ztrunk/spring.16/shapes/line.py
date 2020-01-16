from Point import Point
import math

class Line(object):
    def __init__(self,p1=None,p2=None):
        if p1 == None:
            self.p1 = Point(0,0)
        else:
            self.p1 = p1
            
        if p2 == None:
            self.p2 = Point(0,0)
        else:
            self.p2 = p2
    
    def __str__(self):
        return "[%s , %s]" % (self.p1,self.p2)
    
    def length(self):
        return math.sqrt((self.p1.x - self.p2.x)**2 + (self.p1.y - self.p2.y)**2)
        
  
if __name__=='__main__':
    p1 = Point(2,0)
    p2 = Point(4,0)
    l1 = Line(p1,p2)
    
    print(l1)
    
    print(l1.length())
    
    