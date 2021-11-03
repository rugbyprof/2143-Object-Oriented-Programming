#include <iostream>
#include <vector>
#include <string>

#include "dice.hpp"

using namespace std;

void PrintDiceRange(Dice &d) {
    int min = 999999;
    int max = 0;
    for (int i = 0; i < 10000; i++) {
        int t = d.roll();
        if (t < min) {
            min = t;
        }
        if (t > max) {
            max = t;
        }
    }
    cout << "Min Roll: " << min << " "
         << "Max Roll: " << max << endl;
}

int main() {
    srand(time(0));
    // Die d6(6);
    // Die d20(20);
    Dice d10_3(3, 10);
    Dice d10_1("4.d.12");

    PrintDiceRange(d10_3);

    cout<<d10_3<<endl;

    PrintDiceRange(d10_1);
    cout<<d10_1<<endl;

    return 0;
}