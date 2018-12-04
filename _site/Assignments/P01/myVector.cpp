#include <iostream>
#include "myVector.h"

using namespace std;

myVector::myVector(int size){
  vSize = size;
  theVector = new int[vSize];
  //just so we have stuff to print!!!!!
  for(int i=0;i<vSize;i++){
    theVector[i] = i*2;
  }
}

void myVector::print(){
  for(int i=0;i<vSize;i++){
    cout<<theVector[i]<<" ";
  }
}