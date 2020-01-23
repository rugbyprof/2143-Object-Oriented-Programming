#include <iostream>
#include "vector.hpp"

using namespace std;


int main(int argc, char** argv){
    MyVector<double> V;

    V.pushBack(11);
    V.pushBack(33);
    V.pushBack(27);
    V.print();

    for(int i=0;i<50;i++){
        double v = double(rand()%9000) / double(rand()%9000);
        
        cout<<v<<endl;
        V.pushBack(v);
    }
    V.print();
    cout<<endl<<V.currentSize()<<endl;
    return 0;
}