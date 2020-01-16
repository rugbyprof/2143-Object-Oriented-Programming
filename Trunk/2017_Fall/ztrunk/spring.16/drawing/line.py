from point import point
import math

class line(object):
    def __init__(self,p1,p2):

        if type(p1) is point:
            self.p1 = p1
        elif type(p1) is tuple:
            self.p1 = point(p1)
        else:
            raise TypeError("oops")
            
        if type(p2) is point:
            self.p2 = p2
        elif type(p2) is tuple:
            self.p2 = point(p2)
        else:
            raise TypeError("oops")
            
    def __str__(self):
        return "<%s , %s>" % (self.p1,self.p2)
        
    def length(self):
        return math.sqrt((self.p1.x - self.p2.x)**2 + (self.p1.y - self.p2.y)**2)

           
if __name__=='__main__':

    L1 = line(point(3,4),point(6,7))
    L2 = line((8,4),(-1,-2))

    
    print(L1)
    print(L1.length())
    print(dir(L1))
