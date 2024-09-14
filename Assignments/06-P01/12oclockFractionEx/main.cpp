#include <iostream>
#include <string>

using namespace std;

int main() {
    string f1, op, f2;

    int n1, n2, d1, d2;

    while (cin >> f1 >> op >> f2) {
        cout << f1 << " " << op << " " << f2 << endl;
        n1 = f1[0] - '0';
        d1 = f1[2] - '0';
        n2 = f2[0] - '0';
        d2 = f2[2] - '0';

        if (op == "+") {
            cout << n1 << "/" << d1 << " + " << n2 << "/" << d2 << " = "
                 << n1 * d2 + n2 * d1 << "/" << d1 * d2 << endl;
        } else if (op == "-") {
            cout << n1 << "/" << d1 << " - " << n2 << "/" << d2 << " = "
                 << n1 * d2 - n2 * d1 << "/" << d1 * d2 << endl;
        } else if (op == "*") {
            cout << n1 << "/" << d1 << " * " << n2 << "/" << d2 << " = "
                 << n1 * n2 << "/" << d1 * d2 << endl;
        } else if (op == "/") {
            cout << n1 << "/" << d1 << " / " << n2 << "/" << d2 << " = "
                 << n1 * d2 << "/" << d1 * n2 << endl;
        }
    }

    return 0;
}