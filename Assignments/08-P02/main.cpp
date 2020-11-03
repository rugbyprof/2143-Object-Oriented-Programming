#include <iostream>
#include "cards.hpp"

using namespace std;


int main(){

    Deck D;
    Card *T;

    D.Print();

    T = D.Draw();

    cout<<T->Repr()<<endl;

    return 0;
}