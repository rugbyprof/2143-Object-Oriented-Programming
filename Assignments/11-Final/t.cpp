#include <iostream>
using namespace std;

class C1 {
public:
    int i;

    C1() { cout << "C1 ()" << endl; }

    C1(int ival) : i(ival) { cout << "C1 (" << i << ")" << endl; }
};

class C2 : public C1 {
public:
    int j;

    C2() { cout << "C2 ()" << endl; }

    C2(int jval) : j(jval) { cout << "C2 (" << j << ")" << endl; }

    C2(int jval, int ival) : j(jval), C1(ival) { cout << "C2 (" << j << ")" << endl; }
};

int main() {
    C1 c11, c12(1);
    C2 c21, c22(2), c23(3, 4);
}