#include <iostream>

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