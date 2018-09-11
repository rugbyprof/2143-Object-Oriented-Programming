#include <iostream>
#include "myVector.h"

using namespace std;

template <typename T>
myVector<T>::myVector(int size){
  vSize = size;
  theVector = new T[vSize];
}

template <typename T>
void myVector<T>::print(){
  for(int i=0;i<vSize;i++){
    cout<<theVector[i]<<" ";
  }
}