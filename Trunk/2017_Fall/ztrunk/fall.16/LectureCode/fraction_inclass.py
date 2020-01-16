
def gcd(a, b):
    """Return greatest common divisor using Euclid's Algorithm."""
    while b:      
        a, b = b, a % b
    return a

def lcm(a, b):
    """Return lowest common multiple."""
    return a * b // gcd(a, b)

class Fraction(object):

    def __init__(self,n=1,d=1):
        self.num = n
        self.den = d
        self.reduce()

    def __str__(self):
        return "%d / %d" % (self.num,self.den)

    def reduce(self):
        thegcd = gcd(self.num,self.den)
        self.num /= thegcd
        self.den /= thegcd
        

    def __mul__(self,rhs):
        return Fraction(self.num * rhs.num,self.den*rhs.den)

    def __add__(self,rhs):
        den = self.den * rhs.den
        num = (self.num * rhs.den) + (rhs.num * self.den)
        if(num == den):
            return 1
        else:
            return Fraction(num,den)



if __name__=="__main__":

    f1 = Fraction(12,36)
    f2 = Fraction(5,8)
    f3 = f1 + f2

    print(f3)