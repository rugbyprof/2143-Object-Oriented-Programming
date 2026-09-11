#include <iostream>

using namespace std;

namespace MathUtils {
  
}

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
  Fraction(int, int);            // overloaded const, sets num/den directly (not simplified)
  void setNum(int);
  void setDen(int);
  int getNum(void);
  int getDen(void);
  void setNumDen(int, int);
  friend ostream &operator<<(ostream &, const Fraction &); // lets Fraction be printed with cout <<
  Fraction add(const Fraction &);                          // returns *this + other, simplified
};

// Fraction Implementation

Fraction Fraction::add(const Fraction &other) {
  // Convert both fractions to a common denominator before adding
  int commonDenominator = lcm(den, other.den);

  // Scale each numerator by the same factor its denominator needed
  // to reach the common denominator, then add
  int numerator = num * (commonDenominator / den) +
                  other.num * (commonDenominator / other.den);

  // Simplify the result down to lowest terms
  int divisor = gcd(numerator, commonDenominator);

  numerator /= divisor;
  commonDenominator /= divisor;

  return Fraction(numerator, commonDenominator);
}

// Overloaded << so a Fraction prints as [num/den]
ostream &operator<<(ostream &banana, const Fraction &f) {
  return banana << "[" << f.num << "/" << f.den << "]";
}

Fraction::Fraction(int n, int d) {
  num = n;
  den = d;
}

void Fraction::setNumDen(int n, int d) {
  num = n;
  den = d;
}

void Fraction::setNum(int n) { num = n; }

void Fraction::setDen(int d) { den = d; }

int Fraction::getNum() { return num; }

int Fraction::getDen() { return den; }