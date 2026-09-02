#include <iostream>

using namespace std;

class Fraction {
private:
  int num;
  int den;

  int LCM(int n1, int n2) {
    int max = (n1 > n2) ? n1 : n2;

    do {
      if (max % n1 == 0 && max % n2 == 0) {

        break;
      } else
        ++max;
    } while (true);
    return max;
  }

public:
  Fraction() {
    num = 1;
    den = 1;
  }
  Fraction(int n, int d) {
    num = n;
    den = d;
  }
  Fraction(const Fraction &other) {
    this->num = other.num;
    this->den = other.den;
  }
  void print() { cout << "[" << num << "/" << den << "]"; }

  Fraction operator+(const Fraction &rhs) {
    int lcm = LCM(this->den, rhs.den);
    Fraction f;
    f.den = lcm;

    int tempNum1 = lcm / this->den * this->num;
    int tempNum2 = lcm / rhs.den * rhs.num;
    f.num = tempNum1 + tempNum2;
    return f;
  }

  friend ostream &operator<<(ostream &, const Fraction &);
};

inline ostream &operator<<(ostream &os, const Fraction &other) {
  return os << "[" << other.num << "/" << other.den << "]";
}

int main(int argc, char **argv) {

  if (argc < 5) {
    cout << "You need to pass in 4 numbers.";
    exit(1);
  }
  Fraction f1(stoi(argv[1]), stoi(argv[2]));
  Fraction f2(stoi(argv[3]), stoi(argv[4]));
  f1.print();
  cout << endl;
  f2.print();
  cout << endl;
  Fraction f3 = f1 + f2;
  cout << f3 << endl;
  cout << endl;
  return 0;
}