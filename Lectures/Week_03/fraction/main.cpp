#include <iostream>
#include <fstream>
#include <numeric> // Required for std::gcd
#include "Fraction.hpp"

using namespace std;

int main(int argc, char** argv){
    Fraction F0(1,4);
    Fraction F1;

    int x = 1;
    int y = 8;

    F1.setNumDen(x,y);


    Fraction F2 = F1;

    Fraction F3(3,4);
    
    //cout<<F3.add(F1)<<endl;

    cout<<(F3+F1+F0)<<endl;

}