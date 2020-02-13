#include <iostream>
using namespace std;

class Polygon {
 protected:
  int width, height;

 public:
  void set_values(int a, int b) {
    width = a;
    height = b;
  }
  virtual int area() {}
};

class Rectangle : public Polygon {
 public:
  int area() { return width * height; }
};

class Triangle : public Polygon {
 public:
  int area() { return width * height / 2; }
};

int main() {
  Rectangle rect;
  Triangle trgl;
  rect.set_values(4, 5);
  trgl.set_values(4, 5);
  cout << rect.area() << '\n';
  cout << trgl.area() << '\n';
  return 0;
}