/**
 * 01 - "is-a" vs "has-a"
 *
 * Before writing `class B : public A`, ask: is every B really an A?
 *
 *   - A Warrior IS A Character        -> inheritance
 *   - A Line HAS TWO Points           -> composition
 *
 * A Line is not a kind of Point. If we made Line inherit from Point, a Line
 * would get one x and one y (which point is that?), plus a move() that only
 * knows how to move a single point. Composition models it correctly: a Line
 * is built out of two Point objects.
 */

#include <cmath>
#include <iostream>

using namespace std;

class Point {
protected:
  int x;
  int y;

public:
  Point(int x = 0, int y = 0) : x(x), y(y) {}

  int getX() const { return x; }
  int getY() const { return y; }

  void move(int dx, int dy) {
    x += dx;
    y += dy;
  }

  void jump(int newX, int newY) {
    x = newX;
    y = newY;
  }

  void print() const { cout << "(" << x << ", " << y << ")"; }
};

/**
 * WRONG: inheritance. A Line "is a" Point? It only has one x and one y,
 * so it can't even store both ends.
 */
class BadLine : public Point {};

/**
 * RIGHT: composition. A Line "has a" start Point and an end Point.
 */
class Line {
protected:
  Point start;
  Point end;

public:
  Line(Point s, Point e) : start(s), end(e) {}

  // Line reuses Point's behavior by delegating to its members
  void move(int dx, int dy) {
    start.move(dx, dy);
    end.move(dx, dy);
  }

  double length() const {
    int dx = end.getX() - start.getX();
    int dy = end.getY() - start.getY();
    return sqrt(dx * dx + dy * dy);
  }

  void print() const {
    start.print();
    cout << " -> ";
    end.print();
    cout << "  length: " << length() << endl;
  }
};

int main() {
  Line L(Point(0, 0), Point(3, 4));
  L.print();

  L.move(2, 3);
  L.print(); // moved, but the length is still 5

  BadLine B;
  B.move(1, 1); // compiles... but where does this line start and end?
  B.print();
  cout << "  <- a 'line' with only one point" << endl;
}
