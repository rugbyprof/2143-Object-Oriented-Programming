```cpp

//https://en.cppreference.com/w/cpp/language/constructor

struct Point{
  int x;
  int y;
  Point():x{0},y{0}{};
  Point(int x,int y):x{x},y{y}{};
  friend ostream& operator<<(ostream &os, const Point &p){
    return os << "["<<p.x<<","<<p.y<<"]";
  }
};

template <class T> 
struct TNode {
  T  x;
  TNode *next;
  TNode() {
    x = T();
    next = NULL;
  }
  TNode(T n) {
    x = n;
    next = NULL;
  }
  string print() { return ""; }

  friend ostream &operator<<(ostream &os, const TNode &node) {
    os << node.x;
    return os;
  }
};

Point P1;
Point P2(3,4);

cout<<P1<<" , "<<P2<<endl;

TNode<int> N1(5);

cout<<N1<<endl;

TNode<Point> N2(Point(3,4));

cout<<N2<<endl;
return 0;

```