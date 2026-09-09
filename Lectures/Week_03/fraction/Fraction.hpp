#include <iostream>

using namespace std;

// Fraction Definition
class Fraction {
  int num;
  int den;

  // Find GCD using Euclid's algorithm
  int gcd(int a, int b) {
    while (b != 0) {
      int temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }

  // Find LCM using GCD
  int lcm(int a, int b) { return (a / gcd(a, b)) * b; }

public:
  Fraction() : num(1), den(1) {} // default const
  Fraction(int, int);            // overloaded
  void setNum(int);
  void setDen(int);
  int getNum(void);
  int getDen(void);
  void setNumDen(int, int);
  friend ostream &operator<<(ostream &, const Fraction &);
  Fraction add(const Fraction &);
};

// Fraction Implementation

Fraction Fraction::add(const Fraction &other) {
  // void addFractions(int a, int b, int c, int d) {
  int commonDenominator = lcm(den, other.den);

  int numerator = num * (commonDenominator / den) +
                  other.num * (commonDenominator / other.den);

  // Simplify the result
  int divisor = gcd(numerator, commonDenominator);

  numerator /= divisor;
  commonDenominator /= divisor;

  return Fraction(numerator, commonDenominator);
}

ostream &operator<<(ostream &banana, const Fraction &f) {
  return banana << "[" << f.num << "/" << f.den << "]";
}

Fraction::Fraction(int n, int d) {
  num = n;
  den = d;
}
x

    void
    Fraction::setNumDen(int n, int d) {
  num = n;
  den = d;
}

void Fraction::setNum(int n) { num = n; }

void Fraction::setDen(int d) { den = d; }

int Fraction::getNum() { return num; }

int Fraction::getDen() { return den; }