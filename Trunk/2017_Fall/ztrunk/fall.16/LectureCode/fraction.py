def gcd(n, d):
    while n != d:
        if n > d:
            n = n - d
        else:
            d = d - n
    return n
class Fraction:
    def __init__(self, n, d):
        self.num = int(n / gcd(abs(n), abs(d)))
        self.denom = int(d / gcd(abs(n), abs(d)))
        if self.denom < 0:
            self.denom = abs(self.denom)
            self.num = -1*self.num
        elif self.denom == 0:
            raise ZeroDivisionError

    def Add(self, other):
        return self.num*other.denom + self.denom*other.num, self.denom*other.denom
    def Sub(self, other):
        return self.num*other.denom - self.denom*other.num, self.denom*other.denom
    def Mul(self, other):
        return self.num*other.num, self.denom*other.denom
    def Div(self, other):
        return self.num*other.denom, self.denom*other.num
    def __str__(self):
        if type(self) is tuple:
            if self[1] < 0:
                return '%s/%s' %(self[0], -1*self[1])
            else:
                return '%s/%s' %(self[0], self[1])
        elif self.denom == 1:
            return str(self.num)
        else:
            return '%s/%s' %(self.num, self.denom)
    def __cmp__(self, arg):
        if self > arg:
            return -1
        elif self == arg:
            return 0
        else:
            return 1
    def __nonzero__(self):
        if self != 0:
            return True
        else:
            return False
def main():
    f1 = Fraction(2,-2)
    f2 = Fraction(3,-4)
    f3 = Fraction.Add(f1,f2)
    f4 = Fraction.Sub(f1,f2)
    f5 = Fraction.Mul(f1,f2)
    f6 = Fraction.Div(f1,f2)
    f8 = 0
    print(Fraction.__cmp__(f4,f4),Fraction.__str__(f3),Fraction.__str__(f4),Fraction.__str__(f5),Fraction.__str__(f6), Fraction.__str__(f1), Fraction.__str__(f2))
    if Fraction.__nonzero__(f8):
        print("It is a fraction")
    else:
        print("It is not a fraction")
    return 0
if __name__ == '__main__':
    main()