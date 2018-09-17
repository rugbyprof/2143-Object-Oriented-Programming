#include <iostream>
#include <string>
#include "myVector.h"

using namespace std;

int main() {
  myVector<string> V(10);

  V.print();
}