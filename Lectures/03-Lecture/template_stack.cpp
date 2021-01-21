// Created Jan 21st for CMPS 2143
#include <iostream>
#include <string>

using namespace std;

/**
 * Used as an example to show sizeof function
 */
struct Person{
    string fname;
    string lname;
    string address;
    string bday;
    string nickname;
    string email;
    string momsmaidenname;
    string social;
    string whatever;
};

/**
 * Point3D
 * 
 * DataMembers:
 *      int x - coord
 *      int y - coord
 *      int z - coord
 * Methods:
 *      Point3D() - default constructor
 *      Point3D(int,int,int) - overloaded constructor
 */
struct Point3D{
    int x;
    int y;
    int z;
    Point3D(){
        x = y = z = 0;
    }
    Point3D(int _x,int _y,int _z){
        x = _x;
        y = _y;
        z = _z;
    }
};

/**
 * Ostream cout
 * 
 * Params:
 *      ostream&        - reference to cout
 *      const Point3D&  - point to be printed
 */
ostream& operator<<(ostream &os,const Point3D& rhs){
    return os << "["<<rhs.x<<","<<rhs.y<<","<<rhs.z<<"]";
}

/**
 * Ostream cout
 * 
 * Params:
 *      ostream&        - reference to cout
 *      const Point3D*  - pointer to point to be printed
 */
ostream& operator<<(ostream &os, const Point3D* rhs){
    return os << "["<<rhs->x<<","<<rhs->y<<","<<rhs->z<<"]";
}

/**
 * 
 * I'm not commenting this whole thing...
 */
template <class T>
class TStack{
private:
    //data members
    T **Array;      // our container
    int Top;        // inmdex of top value
    int Size;       // size of the array

    // Is the stack empty?
    bool Empty(){
        return Top < 0;
    }

    // is the stack full?
    bool Full(){
        return Top == Size - 1;
    }
public:
    // constructor
    TStack(){
        cout<<"Initializing Stack"<<endl;
        Size = 10;
        Array = new T*[Size];           // init array to 10
        Top = -1;                       // init top of stack
    }

    // overloaded constructor
    TStack(int size){
        cout<<"Initializing Stack"<<endl;
        Size = size;
        Array = new T*[Size];           // init array to size
        Top = -1;                       // init top of stack
    }

    // push int onto the stack
    void Push(T* value){
        if(!Full()){                    // can't push onto full array!
            Top++;                      // increment top first 
            Array[Top] = value;         // place value in empty slot above
                                        //    previous value
        }else{
            // One problem with arrays, the get full!
            cout<<"Error: Stack Full!!"<<endl;
        }
    }

    // remove item from our stack
    T* Pop(){
        
        if(!Empty()){                   // cannot remove from empty stack!
            T *temp = Array[Top];       // make copy of value at top
            Top--;                      // move index down one slot
            return temp;                // return our copied value
        }
        // No error message needed since we can return a nice
        // testable value!
        return NULL;
    }

    // print the stack
    void Print(){
        
        // standard for loop. arrays love for loops
        for(int i=0;i<=Top;i++){
            cout<<Array[i]<<" ";        // write out element at
                                        // location i
        }
        cout<<endl;
    }

    // give our memory back to system
    ~TStack(){
        cout<<"Destructing Class"<<endl;
        delete [] Array;
    }

    //friend ostream& operator<<(ostream& banana, const TStack<T>& rhs);
};

// template<typename T>
// ostream& operator<<(ostream& banana, const TStack<T>& rhs){
//     for(int i=0;i<rhs.Top;i++){
//         banana << rhs.Array[i] << endl;
//     }
//     return banana;
// }



int main() {

    cout<<"Little pointer overview "<<endl;
    int *x = new int;       // create a dynamic pointer
    *x = 9;                 // store 9 into the pointer
    cout<<*x<<endl;         // write out the value it points to
    cout<<x<<endl;          // write out the address it points to (address of 9)
    cout<<&x<<endl;         // write out the address of the pointer itself

    cout<<endl<<"Template stack output: "<<endl;


    // "object" == "instance" (terminology)
    TStack<Point3D> S1;                 // now an object of type TStack

    S1.Push(new Point3D(1,2,3));         // do i need to comment these lines??
    S1.Push(new Point3D(3,4,5));        
    S1.Push(new Point3D(6,7,8));             
    S1.Pop();

    // push 10 random values between 0-99 onto stack
    for(int i=0;i<10;i++){
        S1.Push(new Point3D(rand()%100,rand()%100,rand()%100));
    }

    // print our stack using method
    S1.Print();

    while(S1.Pop()){
        cout<<"Removing point from stack..."<<endl;
    }

    cout<<endl<<endl;

    cout<<"Sizeof different data types: "<<endl;
    cout<<sizeof(int)<<endl;
    cout<<sizeof(Point3D)<<endl;
    cout<<sizeof(Person)<<endl;
    cout<<sizeof(Person*)<<endl;

}