#include <iostream>
#include <string>

using namespace std;


template <typename T>
class myVector{
private:
  T *theVector;
  int vSize;
public:
  myVector(int size);
  void print();
};

template <typename T>
myVector<T>::myVector(int size){
  vSize = size;
  char c;
  theVector = new T[vSize];
  for(int i=0;i<size;i++){
    c = char((i%26)+65);
    theVector[i] = string (1,c);
  }
}


template <typename T>
void myVector<T>::print(){
  for(int i=0;i<vSize;i++){
    cout<<theVector[i]<<" ";
  }
}