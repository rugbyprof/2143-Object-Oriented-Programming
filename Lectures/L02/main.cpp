#include <iostream>

using namespace std;

struct Node {
  int data;
  Node* next;
  Node* prev;

  Node() {
    data = 0;
    next = prev = NULL;
  }

  Node(int d) {
    data = d;
    next = prev = NULL;
  }

  friend ostream& operator<<(ostream& os, const Node& obj) {
    return os << "[" << obj.data << "]";
  }

  void operator=(const Node& obj) { this->data = obj.data; }
};

struct MyVector {
 private:
  Node* Head;
  Node* Tail;
  int size;

 public:
  MyVector() {
    Head = Tail = NULL;
    size = 0;
  }

  MyVector(const MyVector& obj) {
    Node* Temp = obj.Head;
    while (Temp) {
      this->pushBack(Temp->data);
      Temp = Temp->next;
    }
    size = obj.size;
    Tail = obj.Tail;
  }

  void pushBack(int d) {
    Node* temp = new Node(d);

    if (Head == NULL) {
      Head = temp;
      Tail = temp;
    } else {
      Tail->next = temp;
      temp->prev = Tail;
      Tail = temp;
    }
    size++;
  }

  void pushFront(int d) {
    Node* temp = new Node(d);

    if (Head == NULL) {
      Head = temp;
      Tail = temp;
    } else {
      temp->next = Head;
      Head->prev = temp;
      Head = temp;
    }
    size++;
  }

  int popBack() {
    if (Tail) {
      int d = Tail->data;
      Node* temp = Tail;
      Tail = Tail->prev;
      if (Tail) {
        Tail->next = NULL;
      } else {
        Head = NULL;
      }

      delete temp;

      size--;

      return d;
    }

    return -1;
  }

  int popFront() {
    if (Head) {
      int d = Head->data;
      Node* temp = Head;
      Head = Head->next;
      if (Head) {
        Head->prev = NULL;
      } else {
        Tail = NULL;
      }

      delete temp;

      size--;

      return d;
    }
    return -1;
  }

  void print() {
    Node* temp = Head;

    while (temp) {
      cout << temp->data;
      if (temp->next) {
        cout << "->";
      }
      temp = temp->next;
    }
    cout << endl;
  }

  friend ostream& operator<<(ostream& os, const MyVector& obj) {
    Node* temp = obj.Head;
    string output = "";

    while (temp) {
      output += "[" + to_string(temp->data) + "]";
      if (temp->next) {
        output += "->";
      }
      temp = temp->next;
    }

    return os << output;
  }

  int& operator[](int index) {
    if (index >= size) {
      cout << "Array index out of bound, exiting";
      exit(0);
    }
    Node* temp = Head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  MyVector operator+(const MyVector& lhs) {
    Node* temp1 = Head;
    Node* temp2 = lhs.Head;

    MyVector V;

    while (temp1) {
      V.pushBack(temp1->data);
      temp1 = temp1->next;
    }

    while (temp2) {
      V.pushBack(temp2->data);
      temp2 = temp2->next;
    }

    return V;
  }

  void Sort(bool asc = true) {
    Node* Start = Head;

    while (Start) {
      Node* minp = Start;
      int minv = Start->data;
      Node* mint = Start;
      bool doSwap = 0;

      while (mint) {
        if (asc) {
          doSwap = (mint->data < minv);
        } else {
          doSwap = (mint->data > minv);
        }

        if (doSwap) {
          minp = mint;
          minv = mint->data;
        }
        mint = mint->next;
      }

      // swap
      minp->data = Start->data;
      Start->data = minv;

      Start = Start->next;
    }
  }
};

int main() {
  MyVector V1;
  MyVector V2;
  //   Node N;

  //   N.data = 5;

  //   cout<<N<<endl;

  for (int i = 0; i < 10; i++) {
    V1.pushFront(rand() % 100);
  }

  for (int i = 0; i < 5; i++) {
    V2.pushFront(rand() % 100);
  }

  MyVector V3 = V2;

  cout << V2 << endl;
  cout << V3 << endl;

  V2[4] = 0;

  cout << V2 << endl;
  cout << V3[2] << endl;

  //   int d = V1.popBack();

  //   cout<<V1<<endl;
  //   V1.Sort(false);
  //   cout<<V1<<endl;

  //   V1 = V1 + V2;

  //   cout<<V1<<endl;
  //   cout<<V1[3]<<endl;

  //   V1[3] = 88;

  //   cout<<V1[3]<<endl;

  //   V1[99] = 0;
}