import random

class Fraction(object):
  def __init__(self,num=None,den=None):
    if not num:
      num = random.randint(1,10)
    if not den:
      den = random.randint(1,10)
      while den == num:
        den = random.randint(1,10)
        
    if num > den:
      temp = num
      num = den
      den = temp
      
    gcd = self.__gcd(num,den)
      
    self.num = num / gcd
    self.den = den / gcd
    
  def __str__(self):
    return "(%d/%d)" % (self.num,self.den)
  
  def __mul__(self,rhs):
    num = self.num * rhs.num
    den = self.den * rhs.den
    gcd = self.__gcd(num,den)
    return Fraction(num/gcd,den/gcd)
  
  def __add__(self,rhs):
      pass
    
  def __gcd(self,x, y):
      while y != 0:
          (x, y) = (y, x % y)
      return x
  

flist = []

for i in range(100):
  flist.append(Fraction())
  
for f in flist:
  print(f)
  

for i in range(len(flist)-1):
  flist[i] = flist[i] * flist[i+1]
  
for f in flist:
  print(f) 



  
  
  
