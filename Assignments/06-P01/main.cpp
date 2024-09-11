// 12:00 class lecture code
#include <iostream>

using namespace std;

/*
  ___  ___ ___ ___ _  _ ___ _____ ___ ___  _  _
 |   \| __| __|_ _| \| |_ _|_   _|_ _/ _ \| \| |
 | |) | _|| _| | || .` || |  | |  | | (_) | .` |
 |___/|___|_| |___|_|\_|___| |_| |___\___/|_|\_|
*/
class Fraction {
private: // redundant statement but added for readability
  int num;
  int den;

public:
  // Griffin forgot to mention setters and getters.
  Fraction();
  Fraction(int, int);
  Fraction(string);
  void print() { cout << num << "/" << den << endl; }
  friend ostream &operator<<(ostream &os, const Fraction &rhs);
  Fraction operator+(const Fraction &rhs);
};

/*
  ___ __  __ ___ _    ___ __  __ ___ _  _ _____ _ _____ ___ ___  _  _
 |_ _|  \/  | _ \ |  | __|  \/  | __| \| |_   _/_\_   _|_ _/ _ \| \| |
  | || |\/| |  _/ |__| _|| |\/| | _|| .` | | |/ _ \| |  | | (_) | .` |
 |___|_|  |_|_| |____|___|_|  |_|___|_|\_| |_/_/ \_\_| |___\___/|_|\_|
*/

// Constructors

// Operators
ostream &operator<<(ostream &os, const Fraction &rhs) {
  return os << rhs.num << "/" << rhs.den << endl;
}

Fraction Fraction::operator+(const Fraction &rhs) {
  int num = this->num + rhs.num;
  int den = this->den + rhs.den;
  return Fraction(num, den);
}

void Fraction::print() { cout << num << "/" << den << endl; }

int main(int argc, char const *argv[]) {

  Fraction F1(3, 8);
  Fraction F2(3, 4);

  // discuss in class
  while (1) {
    break;
  }

  return 0;
}