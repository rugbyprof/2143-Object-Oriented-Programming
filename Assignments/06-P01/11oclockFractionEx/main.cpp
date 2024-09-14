/**
 * The code below is a simple fraction calculator that takes in two fractions
 * and an operator and performs the operation on the two fractions. The
 * fractions are inputted as strings in the format "n/d" where n is the
 * numerator and d is the denominator. The operator is inputted as a string. The
 * program then parses the input strings to extract the numerator and
 * denominator of the left and right fractions (f1,f2) and performs the
 * operation based on the operator. The result is then printed in the format
 * "n/d". The program continues to take input until the end of the file is
 * reached.
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    int n1 = stoi(argv[1]);

    for (int i = 0; i < argc; i++) {
        cout << "Argument " << i << " is: " << argv[i] << endl;
    }
    cout << "Hello, World!" << endl;
    string f1, op, f2;
    int d1, d2, n1, n2;
    while (cin >> f1 >> op >> f2) {
        // 1/2 * 3/4
        cout << f1 << " " << op << " " << f2 << endl;

        n1 = f1[0] - '0';
        d1 = f1[2] - '0';
        n2 = f2[0] - '0';
        d2 = f2[2] - '0';

        cout << n1 << " " << d1 << " " << n2 << " " << d2 << endl;

        // if (op == "+") {
        //     cout << n1 * d2 + n2 * d1 << "/" << d1 * d2 << endl;
        // } else if (op == "-") {
        //     cout << n1 * d2 - n2 * d1 << "/" << d1 * d2 << endl;
        // } else if (op == "*") {
        //     cout << n1 * n2 << "/" << d1 * d2 << endl;
        // } else if (op == "/") {
        //     cout << n1 * d2 << "/" << d1 * n2 << endl;
        // }

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