#include <iostream>
#include <string>

using namespace std;

template <typename T>
class myVector{
private:
  T *theVector;
  int vSize;
  int index;
public:
  myVector(int size);
  void print();
  void push(T);
};

template <typename T>
myVector<T>::myVector(int size){
  vSize = size;
  index = 0;
  theVector = new T[vSize];
}

template <typename T>
void myVector<T>::push(T item){

    theVector[index++] = item;
}

template <typename T>
void myVector<T>::print(){
  for(int i=0;i<vSize;i++){
    cout<<theVector[i]<<" ";
  }
}

int main() {
  myVector<string> V1(10);
  myVector<int> V2(10);

  char c;


  for(int i=0;i<10;i++){
    c = char((i%26)+65);
    V1.push(string (1,c));
  }
  

  for(int i=0;i<10;i++){
    V2.push(i);
  }

  V1.print();
  cout<<endl;
  V2.print();
}