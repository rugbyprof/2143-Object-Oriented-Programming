///////////////////////////////////////////////////////////////////////////////
//
// Author:           Terry Griffin
// Email:            terry.griffin@msutexas.edu
// Course:           CMPS 2143
// Semester:         Spring 2020
// Date:             Jan 28th
//
// Description:
//    This code adds some improvements to our vector class written in the
//    previous lesson. I won't comment this file like the previous one. I will
//    simply comment the additions to our class.
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;

// Our previous node was not templated it only
// held integers. By
template <typename T>
struct Node {
  T data;  // Now data will be whatever "T" is.
  Node* next;
  Node* prev;

  Node() { next = prev = NULL; }

  // d is whatever type "T" is.
  Node(T d) {
    data = d;
    next = prev = NULL;
  }

  // "friend" keyword gives one class access to the private and
  // protected components of another class

  // This overloads the "<<" operator allowing us to send
  // the node "data" straight to the output stream
  friend ostream& operator<<(ostream& os, const Node& obj) {
    return os << "[" << obj.data << "]";
  }

  // This overloads the assignment (=) operator allowing
  // us to assign the value of one Node to another
  void operator=(const Node& obj) { 
    this->data = obj.data; 
  }

};

// We need to also template the MyVector class because
// if the Node is templated, then the methods in this class
// need to be templated as well so the data types can
// change to match what we need our Node to store.
template <class T>
class MyVector {
 private:
  Node<T>* Head;  // Pointers need to know what type the node will
  Node<T>* Tail;  // be storing.
  int size;

 public:
  MyVector() {
    Head = Tail = NULL;
    size = 0;
  }

  // This is a copy constructor.
  // A copy constructor receives an object of the
  // same type, and then makes a copy of the incoming
  // object.
  // For simple objects, the system can create a copy
  // constructor on the fly, by when dealing with dynamic
  // memory we should handle it ourselves. Look at the
  // readme file to see deep copy vs shallow copy
  MyVector(const MyVector& obj) {
    Head = Tail = NULL;
    size = 0;
    cout << "Copy Constructor\n";
    Node<T>* Temp = obj.Head;
    while (Temp) {
      this->pushBack(Temp->data);
      Temp = Temp->next;
    }
  }

  int Size() { return size; }

  // we replace every "int" from previous version
  // with a "T".
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

  // Again we overload the "<<" operator letting us print a vector
  // straight to the output stream instead of using a "print" function.
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

  // Overload the "[]" square brackets so we can treat our list
  // similar to an array. This will let us obtain a value from
  // any existing node, or update that nodes value by assigning it
  // a new one.
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

  // This is the "+" plus sign being overloaded to
  // concatenate two lists end to end returning a
  // third new list.
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

  // The sort will still work??
  // It should as long as the "T" values are defined
  // to use comparison operators (we will discuss later).
  // For now types like float,string,int will all work.
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

// Griffins cheap random string function
// only does all caps. You should fix it
// to do both upper and lowercase!
string randString(int len) {
  string s;
  for (int i = 0; i < len; i++) {
    s += char((rand() % 26) + 65);
  }
  return s;
}

// main driver to test our new templated vector class
int main() {
  MyVector<int> V1;
  MyVector<int> V2;

  Node<int>* N1 = new Node<int>(33);
  Node<int>* N2 = new Node<int>(34);


  for (int i = 0; i < 10; i++) {
    V1.pushFront(rand() % 100);
  }

  for (int i = 0; i < 5; i++) {
    V2.pushFront(rand() % 100);
  }

  MyVector<int> V3(V2);

  cout << V3.Size() << endl;

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
  cout << endl;
  cout << V5 << endl;
}