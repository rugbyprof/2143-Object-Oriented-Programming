#include <iostream>
#include <fstream>
#include <numeric> // Required for std::gcd
#include "fraction.hpp"

using namespace std;

int main(int argc, char** argv){
    Fraction F1;

    int x = 9;
    int y = 11;

    F1.setNumDen(x,y);

    Fraction F2 = F1;

    Fraction F3(3,4);
    
    cout<<F3.add(Fraction(4,5))<<endl;

}