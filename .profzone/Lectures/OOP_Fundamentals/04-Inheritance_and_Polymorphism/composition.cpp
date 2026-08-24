/**
 * Class lecture discussing Inheritance Vs Composition. These two classes
 * fit much better using composition rather than inheritance. Why? Well
 * first some background.
 *
 * Base Class , Super Class, Parent Class are all synonyms for classes that
 * get inherited from.
 *
 * Sub Class , Derived Class, Child Class are all synonyms for classes that
 * do the inheriting.
 *
 *
 *
 */

#include <iostream>

using namespace std;

/**
 *
 *
 */
class Point {
protected:
  int x;
  int y;

public:
  void setX(int d) { x = d; }
  void setY(int d) { x = d; }
  void move(int dx, int dy) {
    x += dx;
    y += dy;
  }

  void jump(int dx, int dy) {
    x = dx;
    y = dy;
  }
};

/**
 *
 *
 */
class Line {
protected:
  Point start;
  Point end;

public:
  void move(int dx1, int dy1, int dx2, int dy2) {
    start.move(dx1, dy1);
    end.move(dx2, dy2);
  }
  float distance() { return 0.0; }
  float slope() { return 0.0; }
};

int main() {
  Line L;
  L.Move(2, 3, 4, 5);
}