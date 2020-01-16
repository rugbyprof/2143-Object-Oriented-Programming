class point(object):
    def __init__(self,x=None,y=None):
        if type(x) is tuple:            
            self.x = x[0]
            self.y = x[1]
        else:
            self.x = x
            self.y = y
            
    def __str__(self):
        return "(%d , %d)" % (self.x,self.y)
        
        
    def shift(self,xshift,yshift=None):
        try:
            xshift = int(xshift)
            if not yshift == None: 
                yshift = int(yshift)
            else:
                yshift = xshift
        except ValueError:
            print("Not an int bud")
            return
                
        
        self.x += xshift
        self.y += yshift
          
         
if __name__=='__main__':
    p = point(4,5)
    print(p)
    
    r = point((6,7))
    print(r)
    
    print(p.x)
    
    p.shift(5)
    print(p)
    
    r.shift(4,5)
    print(r)
    
    print(type(p) is point)