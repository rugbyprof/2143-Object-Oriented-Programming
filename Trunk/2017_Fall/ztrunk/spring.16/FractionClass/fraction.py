class RationalNumber(object):
    """
    Rational Numbers with support for arthmetic operations.

        >>> a = RationalNumber(1, 2)
        >>> b = RationalNumber(1, 3)
        >>> a + b
        5/6
        >>> a - b
        1/6
        >>> a * b
        1/6
        >>> a/b
        3/2
    """
    def __init__(self, numerator, denominator=1):
        self.n = numerator
        self.d = denominator

    def __add__(self, other):
        if not isinstance(other, RationalNumber):
            other = RationalNumber(other)

        n = self.n * other.d + self.d * other.n
        d = self.d * other.d
        return RationalNumber(n, d)

    def __sub__(self, other):
        if not isinstance(other, RationalNumber):
            other = RationalNumber(other)

        n1, d1 = self.n, self.d
        n2, d2 = other.n, other.d
        return RationalNumber(n1*d2 - n2*d1, d1*d2)

    def __mul__(self, other):
        if not isinstance(other, RationalNumber):
            other = RationalNumber(other)

        n1, d1 = self.n, self.d
        n2, d2 = other.n, other.d
        return RationalNumber(n1*n2, d1*d2)

    def __div__(self, other):
        if not isinstance(other, RationalNumber):
            other = RationalNumber(other)

        n1, d1 = self.n, self.d
        n2, d2 = other.n, other.d
        return RationalNumber(n1*d2, d1*n2)

    def __str__(self):
        return "%s/%s" % (self.n, self.d)

    __repr__ = __str__
    
class conversion(RationalNumber):
    def __init__(self,val=0,type='mm'):
        self.value=val
        self.type=type
        self.precision = .0625
    
    def toInches(self,val):
        self.value = val
        return self.value * 0.039370
        
    
    
if __name__=='__main__':
    a = RationalNumber(1, 2)
    b = RationalNumber(1, 3)
    print(a*b)
    
    c = conversion()
    
    print(c.toInches(64))