// Created Jan 14th for CMPS 2143
#include <iostream>

using namespace std;

// Stack is data structure that uses
// LIFO 
// Typical Operations are:
//    Push 
//    Pop


/**
 * Class intStack
 * 
 * Description:
 *      Array based implementation of a stack.
 * 
 * Public Methods:
 *      - intStack()  
 *      - intStack(int)
 *      - void Push(int value)
 *      - int Pop()
 *      - void Print()
 *      - ~intStack()
 * 
 * Private Methods:
 *      - bool Empty()
 *      - bool Full()
 * 
 */
class intStack{
private:
    //data members
    int *Array;     // our container
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
    intStack(){
        cout<<"Initializing Stack"<<endl;
        Size = 10;
        Array = new int[Size];        // init array to 10
        Top = -1;                     // init top of stack
    }

    // overloaded constructor
    intStack(int size){
        cout<<"Initializing Stack"<<endl;
        Size = size;
        Array = new int[Size];        // init array to size
        Top = -1;                     // init top of stack
    }

    // push int onto the stack
    void Push(int value){
        if(!Full()){                // can't push onto full array!
            Top++;                  // increment top first 
            Array[Top] = value;     // place value in empty slot above
                                    //    previous value
        }else{
            // One problem with arrays, the get full!
            cout<<"Error: Stack Full!!"<<endl;
        }
    }

    // remove item from our stack
    int Pop(){
        
        if(!Empty()){               // cannot remove from empty stack!
            int temp = Array[Top];  // make copy of value at top
            Top--;                  // move index down one slot
            return temp;            // return our copied value
        }else{
            // cannot remove item from empty container
            // list or array!
            cout<<"Error: Stack Empty!!"<<endl;
        }
        return -999999; // some sentinel value so we know there was a problem
                        // not best solution, but easy for now
    }

    // print the stack
    void Print(){
        // standard for loop. arrays love for loops
        for(int i=0;i<=Top;i++){
            cout<<Array[i]<<" ";    // write out element at
                                    // location i
        }
        cout<<endl;
    }

    // give our memory back to system
    ~intStack(){
        cout<<"Destructing Class"<<endl;
        delete [] Array;
    }
};

int main() {
    // "object" == "instance" (terminology)
    intStack S1;        // now an object of type intStack
    intStack S2(50);    // another object of type intStack

    S1.Push(1);         // do i need to comment these lines??
    S1.Push(23);        
    S1.Push(45);             
    S1.Pop();

    // push 10 random values between 0-99 onto stack
    for(int i=0;i<10;i++){
        S1.Push(rand()%100);
    }

    // print our stack
    S1.Print();

}