#include <iostream>
#include <vector>
#include <string>

#include "dice.hpp"

using namespace std;

void PrintDiceRange(Dice &d,int rounds=1000) {
    int min = 999999;
    int max = 0;
    for (int i = 0; i < rounds; i++) {
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
    Dice d12_4("4.d.12");
    Dice d20_5("5.d.20");


    PrintDiceRange(d10_3,1000000);

    cout<<d10_3<<endl;

    PrintDiceRange(d12_4,1000000);
    cout<<d12_4<<endl;

    PrintDiceRange(d20_5,1000000);
    cout<<d20_5<<endl;

    return 0;
}