#include <iostream>
#include <string>

using namespace std;

// deep copy vs shallow copy
// copy constructor

struct Node {
  string val;
  Node *next;
  Node(string v) : val(v), next(nullptr) {}
};

class Queue {
private:
  Node *front;
  Node *rear;

public:
  Queue() { front = rear = nullptr; }
  void push(string v) {
    Node *temp = new Node(v); // allocate new memory
    // is list empty?
    if (!front) {
      front = rear = temp; // copy address of temp into head
    } else {
      rear->next = temp;
      rear = temp;
    }
    return;
  }

  void jackit() { front->next->val = "tim"; }

  string pop() {
    string hold = front->val;
    Node *temp = front;
    front = front->next;
    delete temp;
    return hold;
  }

  void print() {
    Node *travel = front;
    while (travel) {
      cout << travel->val;
      if (travel->next) {
        cout << "->";
      }
      travel = travel->next;
    }
    cout << endl;
  }
};

// private
class Stack {

  int top;
  int size;
  int *stack;

public:
  // default constructor
  Stack() {
    top = -1;
    size = 10;
    stack = new int[size];
  }
  // overloaded constructor
  Stack(int size) : top(-1), size(size), stack(new int[size]) {}
  // destructor
  ~Stack() { delete[] stack; }
};

class Basic {
  int a;
  int b;
  int c;

public:
  Basic() : a(3), b(4), c(5) {}
  void print() { cout << a << " " << b << " " << c << endl; }
  int get_a() { return a; }
  void set_a(int x) { a = x; }

  friend ostream &operator<<(ostream &os, const Basic &bas) {
    return os << "[" << bas.a << " " << bas.b << " " << bas.c << "]" << endl;

  }
};

int main(int argc, char **argv) {
  cout << "Stack example ...!" << endl;
  Stack stack1;
  Stack stack2(1000);

  Queue q1;

  q1.push("bob");
  q1.push("sue");
  q1.push("pat");

  Queue q2 = q1;

  q1.print();

  q2.print();

  q1.jackit();

  q1.print();

  q2.print();

  Basic b1;

  Basic b2 = b1;

  b1.print();

  b2.print();

  cout << b1 << " " << b2 << endl;
}
