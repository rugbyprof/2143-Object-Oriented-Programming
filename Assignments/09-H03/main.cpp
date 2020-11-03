#include "blackjack.hpp"
#include <time.h>

using namespace std;

int main() {
    srand(time(0));

    Hand H;

    H.Add(new Card(rand()%52 + 1));
    H.Add(new Card(rand()%52 + 1));
    H.Add(new Card(rand()%52 + 1));
    H.Add(new Card(rand()%52 + 1));
    H.Add(new Card(rand()%52 + 1));
    
    cout<<H<<endl;

    H.Sort();

    cout<<H<<endl;
}