#include <iostream>

using namespace std;
// Array[0]
class Base {
public:
  Base() { cout << "B "; }
  ~Base() { cout << "~B "; }
};
class Mid : public Base {
public:
  Mid() { cout << "M "; }
  ~Mid() { cout << "~M "; }
};
class Top : public Mid {
public:
  Top() { cout << "T "; }
  ~Top() { cout << "~T "; }
};
int main() {
  Top t;
  cout << "| ";
} // t goes out of scope here
