#include <iostream>

using namespace std;

class Point {
  int x;
  int y;

public:
  Point(int _x, int _y) {
    x = _x;
    y = _y;
  }
  Point(const Point &p) {
    x = p.x;
    y = p.y;
  }
  void Print() { cout << x << "," << y << endl; }
};

/**
 *
 *__   _____ ___ _____ ___  ___    ___ _      _   ___ ___
 *\ \ / / __/ __|_   _/ _ \| _ \  / __| |    /_\ / __/ __|
 * \ V /| _| (__  | || (_) |   / | (__| |__ / _ \\__ \__ \
 *  \_/ |___\___| |_| \___/|_|_\  \___|____/_/ \_\___/___/
 *
 * @methods:
 *     // I would normally give brief descript of each method, but I'm not going to now.
 *     Vector()
 *     Vector()
 *     Push(int)
 *     Pop()
 *     Print()
 *     PushAt()
 */
class Vector {
private:
  int *array;
  int index;
  int size;

  bool Full();              // array has all slots filled
  bool Empty();             // array is empty
  void Resize();            // grow array

public:
  Vector();                 // default constructor
  Vector(int);              // specify vector size
  Vector(const Vector &);   // copy constructor
  Vector(int *, int);       // create vector given array of items

  void Push(int);           // add item to vector
  int Pop();                // remove item from vector
  void Print();             // print the vector
  void PushAt(int, int);    // push value at specific location

  friend ostream &operator<<(ostream &, const Vector &);
  Vector operator+(const Vector &);
  int& operator[](int i);
};

/*
    ___ ___  _  _ ___ _____ ___ _   _  ___ _____ ___  ___  ___
   / __/ _ \| \| / __|_   _| _ \ | | |/ __|_   _/ _ \| _ \/ __|
  | (_| (_) | .` \__ \ | | |   / |_| | (__  | || (_) |   /\__ \
   \___\___/|_|\_|___/ |_| |_|_\\___/ \___| |_| \___/|_|_\|___/
   =============================================================
*/

Vector::Vector() {
  index = 0;
  size = 10;
  array = new int[size];
}

Vector::Vector(int s) {
  index = 0;
  size = s;
  array = new int[size];
}

Vector::Vector(const Vector &v) {
  index = v.index;
  size = v.size;
  array = new int[size];
  for (int i = 0; i < index; i++) {
    array[i] = v.array[i];
  }
}

Vector::Vector(int *_array,int _size) {
  size = _size+1;
  index = size-1;
  
  array = new int[size];
  for (int i = 0; i <= index; i++) {
    array[i] = _array[i];
  }
}

/*
    _____   _____ ___ _    ___   _   ___  ___ ___     ___  ___ ___ ___    _ _____ ___  ___  ___
   / _ \ \ / / __| _ \ |  / _ \ /_\ |   \| __|   \   / _ \| _ \ __| _ \  /_\_   _/ _ \| _ \/ __|
  | (_) \ V /| _||   / |_| (_) / _ \| |) | _|| |) | | (_) |  _/ _||   / / _ \| || (_) |   /\__ \
   \___/ \_/ |___|_|_\____\___/_/ \_\___/|___|___/   \___/|_| |___|_|_\/_/ \_\_| \___/|_|_\|___/
   ==============================================================================================
*/

Vector Vector::operator+(const Vector &rhs) {
  // newSize adds together number of items in both vectors
  int newSize = index + rhs.index;

  // new array of bigger size
  int *temp = new int[newSize];

  // copy local values into our new array
  int i;
  for (i = 0; i < index; i++) {
    temp[i] = array[i];
  }

  // we continue with i as a counter to get the proper
  // number of items, but we also use j to access the
  // rhs array starting at its beginning.
  for (int j=0; i < newSize; i++,j++) {
    temp[i] = rhs.array[j];
  }

  // Return a new vector that uses one of our overloaded 
  // constructors to create it using our new bigger array.
  return Vector(temp,newSize);
}

ostream &operator<<(ostream &os, const Vector &v) {
  for (int i = 0; i < v.index; i++) {
    os << v.array[i] << " ";
  }
  return os;
}

// We return the "address" of the location pointed to by [i]
// This works for both assignment, and accessing the vector
int& Vector::operator[](int i){
  return array[i];
}


/*
   __  __ ___ _____ _  _  ___  ___  ___
  |  \/  | __|_   _| || |/ _ \|   \/ __|
  | |\/| | _|  | | | __ | (_) | |) \__ \
  |_|  |_|___| |_| |_||_|\___/|___/|___/
  ======================================
*/

bool Vector::Full() { return index == (size - 1); }


int Vector::Pop(){
  index--;
  return array[index];
}

void Vector::Push(int item) {
  if (Full()) {
    Resize();
  }

  array[index] = item;
  index++;
}

void Vector::PushAt(int index, int val) { array[index] = val; }


void Vector::Print() {
  for (int i = 0; i < index; i++) {
    cout << array[i] << " ";
  }
}

void Vector::Resize() {
  int *tempArray = new int[size * 2];
  for (int i = 0; i < index; i++) {
    tempArray[i] = array[i];
  }
  delete[] array;
  array = tempArray;
}




int main() {
  Vector V1;
  V1.Push(4);
  V1.Push(6);
  V1.Push(10);
  V1.Push(12);

  Vector V2;
  V2.Push(18);
  V2.Push(26);
  V2.Push(30);
  V2.Push(42);
  // cout << V1 << endl;

  // Vector V2 = V1;
  // cout << V2 << endl;

  // V1.PushAt(2, 99);
  // cout << V1 << endl;
  // cout << V2 << endl;

  // V2.PushAt(2, 88);

  // cout << V1 << endl;
  // cout << V2 << endl;

  V1 = V1 + V2;

  cout<<V1<<endl;

  V1.Push(88);

  cout<<V1<<endl;

  cout<<"Popped: "<<V1.Pop()<<endl;

  cout<<V1<<endl;

  V1[5] = 25;

  cout<<V1[5]<<endl;

  // Point P1(4,5);
  // Point P2 = P1;
  // P1.Print();
  // P2.Print();
}