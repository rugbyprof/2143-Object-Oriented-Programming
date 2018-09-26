#include <iostream>

using namespace std;

class myVector{
private:
  int *theVector;
  int vSize;
public:
  myVector(int size);
  void print();
};