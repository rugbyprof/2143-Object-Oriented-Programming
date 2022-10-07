#include <iostream>
#include <string>

#include "blackjack.hpp"
#include <vector>
#include <time.h>

//stdio.h, sys/ioctl.h, unistd.h 

using namespace std;


// colors
// xy location
// terminal size

int main() {
    srand(time(0));

    Card C1(rand()%52);
    cout<<C1<<endl;

    Card C2(rand()%52);
    cout<<C2<<endl;

    cout<<(C2<C1)<<endl;
}