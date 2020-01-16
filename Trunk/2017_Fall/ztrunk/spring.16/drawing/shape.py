from line import *

class shape(object):
    def __init__(self,o,w,h):
        self.sides = []         # a list of lines  
        self.origin = o
        self.width = w
        self.height = h      
    
    def area(self):
        raise Exception ("You need to implement this")
        
    def perimeter(self):
        total = 0
        for line in self.sides:
            total += line.length()
        return total
        
    def __str__():
        pass
        
class rectangle(shape):
    def __init__(self,o,w,h):
        super().__init__(o,w,h)
        left = line(o,(o.x,o.y+h))
        bottom = line(o,(o.x+w,o.y))
        right = line((o.x+w,o.y),(o.x+w,o.y+h))
        top = line((o.x,o.y+h),(o.x+w,o.y+h))

        self.sides.append(left) #left sides
        self.sides.append(bottom)#bottome sides
        self.sides.append(right) #left sides
        self.sides.append(top)#bottome sides       


    def area(self):
        return self.width * self.height
       

    def __str__(self):
        return "%s %s %s %s" % (self.origin,self.width,self.height,self.sides)
        
        
class right_triangle(shape):
    def __init__(self,o,w,h):
        super().__init__(o,w,h)
        left = line(o,(o.x,o.y+h))
        bottom = line(o,(o.x+w,o.y))
        hypotenuse = line((o.x,o.y+h),(o.x+w,o.y))   
        
        self.sides.append(left) #left sides
        self.sides.append(bottom)#bottome sides
        self.sides.append(hypotenuse) #left sides 
        
    def area(self):
        return self.width * self.height / 2


class square(rectangle):
    def __init__(self,o,s):
        super().__init__(o,s,s)
         
       
    

if __name__=='__main__':
    p = point(2,2)
    w = 6
    h = 4
    r = rectangle(p,w,h)
    s = square(p,5)
    t = right_triangle(p,5,6)
    
    print(r.area())
    print(s.area())
    print(t.area())
    