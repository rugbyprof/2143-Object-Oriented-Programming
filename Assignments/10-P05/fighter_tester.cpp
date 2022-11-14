#include <iostream>
#include <vector>
#include <string>

#include "fighter.hpp"

using namespace std;

int main() {
    srand(time(0));

    BaseFighter *f1 = new BaseFigher;
    
    vector<BaseFighter*> fighters;
    
    
    # Optionally create a vector of 100 BaseFighters
    for(int i=0;i<100;i++){
        fighters.push_back(new BaseFighter);
    }
    
    
    cout<<*f1<<endl;

    cout<<f1->attack()<<endl;

    return 0;
}
