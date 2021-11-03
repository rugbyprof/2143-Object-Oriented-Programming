#include <iostream>
#include <string>

#include "weapon.hpp"

using namespace std;

int main() {
    srand(time(0));

    Weapon w1;                      // create base booring weapon
    Weapon w2({"1.d.4","1.d.6"});   // same but with chance of better die roll

    cout<<w1<<endl;                 // show us the weapon
    cout<<w1.use()<<endl;           // "use" the weapon (roll the dice)

    cout<<w2<<endl;                 // same as above
    cout<<w2.use()<<endl;

    return 0;
}