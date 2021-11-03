#include <iostream>
#include <vector>
#include <string>

#include "fighter.hpp"

using namespace std;

int main() {
    srand(time(0));

    BaseFighter f1;

    cout<<f1<<endl;

    cout<<f1.attack()<<endl;

    return 0;
}