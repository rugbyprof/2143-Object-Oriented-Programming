#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << "Argument " << i << " is: " << argv[i] << endl;
    }
    cout << "Hello, World!" << endl;
    string f1, op, f2;
    int d1, d2, n1, n2;
    while (cin >> f1 >> op >> f2) {
        // 1/2 * 3/4
        cout << f1 << op << f2 << endl;
        n1 = f1[0] - '0';
        d1 = f1[2] - '0';
        n2 = f2[0] - '0';
        d2 = f2[2] - '0';
        cout << n1 << " " << d1 << " " << n2 << " " << d2 << endl;
    }
    return 0;
}