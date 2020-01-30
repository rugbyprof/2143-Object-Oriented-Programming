#include <iostream>

using namespace std;

template <class T>
struct Node {
  T data;
  Node* next;
  Node* prev;

  Node() {
    next = prev = NULL;
  }

  Node(T d) {
    data = d;
    next = prev = NULL;
  }

  friend ostream& operator<<(ostream& os, const Node& obj) {
    return os << "[" << obj.data << "]";
  }

  void operator=(const Node& obj) { this->data = obj.data; }
};

template <class T>
class MyVector {
 private:
  Node<T>* Head;
  Node<T>* Tail;
  int size;

 public:
  MyVector() {
    Head = Tail = NULL;
    size = 0;
  }

  MyVector(const MyVector& obj) {
    Head = Tail = NULL;
    size = 0;
    cout<<"Copy Constructor\n";
    Node<T>* Temp = obj.Head;
    while (Temp) {
      this->pushBack(Temp->data);
      Temp = Temp->next;
    }
    //size = obj.size;
    //Tail = obj.Tail;
  }

  int Size(){
    return size;
  }

  void pushBack(T d) {
    Node<T>* temp = new Node<T>(d);

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

  void pushFront(T d) {
    Node<T>* temp = new Node<T>(d);

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

  T popBack() {
    if (Tail) {
      int d = Tail->data;
      Node<T>* temp = Tail;
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

  T popFront() {
    if (Head) {
      T d = Head->data;
      Node<T>* temp = Head;
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
    Node<T>* temp = Head;

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
    Node<T>* temp = obj.Head;

    while (temp) {
 
      os << "[";
      os << temp->data;
      os << "]";
      if (temp->next) {
        os << "->";
      }
      temp = temp->next;
    }

    return os;
  }

  //   int operator[](int index)
  //   {
  //       if (index >= size)
  //       {
  //           cout << "Array index out of bound, exiting";
  //           exit(0);
  //       }
  //       Node* temp = Head;
  //       for(int i=0;i<index;i++){
  //         temp = temp->next;
  //       }
  //       return temp->data;
  //   }

  T& operator[](int index) {
    if (index >= size) {
      cout << "Array index out of bound, exiting";
      exit(0);
    }
    Node<T>* temp = Head;
    for (int i = 0; i < index; i++) {
      temp = temp->next;
    }
    return temp->data;
  }

  MyVector operator+(const MyVector& lhs) {
    Node<T>* temp1 = Head;
    Node<T>* temp2 = lhs.Head;

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
    Node<T>* Start = Head;

    while (Start) {
      Node<T>* minp = Start;
      int minv = Start->data;
      Node<T>* mint = Start;
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

string randString(int len){
  string s;
  for(int i=0;i<len;i++){
    s += char((rand()%26)+65);
  }
  return s;
}

int main() {
  MyVector<int> V1;
  MyVector<int> V2;

  for (int i = 0; i < 10; i++) {
    V1.pushFront(rand() % 100);
  }

  for (int i = 0; i < 5; i++) {
    V2.pushFront(rand() % 100);
  }

  MyVector<int> V3(V2);

  cout<<V3.Size()<<endl;

  cout << V2 << endl;
  cout << V3 << endl;

  V2[4] = 0;

  cout << V2 << endl;
  cout << V3 << endl;

  MyVector<string> V4;
  MyVector<string> V5;

  for (int i = 0; i < 10; i++) {
    V4.pushFront(randString(8));
  }

  for (int i = 0; i < 5; i++) {
    V5.pushFront(randString(8));
  }

  cout << V4 << endl;
  cout<<endl;
  cout << V5 << endl;


}