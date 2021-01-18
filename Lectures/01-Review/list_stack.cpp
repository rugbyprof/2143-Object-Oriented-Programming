// Created Jan 14th @ 0930 for 2143
#include <iostream>

using namespace std;

// Structs are good as containers of data.
//    since everything is public.
// Just like a class though, they can have
//    methods and constructors! 
struct Node{
    int data;           // data in our node (super simple right now)
    Node* next;         // pointer to next node

    // needs a default constructor

    Node(int d){        // constructor for node
        data = d;
        next = NULL;
    }
};

/**
 * Class ListStack
 * 
 * Description:
 *      Linked list implementation of a Stack.
 * 
 * Public Methods:
 *      - ListStack()
 *      - int Pop()
 *      - bool Empty()
 *      - void Print()
 *      - void Push(int)
 * 
 * Private Methods:
 *      - None
 */
class ListStack{
private:
    Node* Top;          // pointer to front of list
public:
    // constructor
    ListStack(){
        Top = NULL;    // list is empty
    }

    void Push(int data){
        Node* Temp = new Node(data);    // allocate new memory

        // Adding to empty list 
        if(Top == NULL){
            Top = Temp;
        }else{
        // Adding to non empty list
            Temp->next = Top;
            Top = Temp;
        }
        
    }

    //LIFO
    int Pop(){
        // get value from Top
        // delete the first node
        // adjusting some pointers
        // return the value
        if(!Empty()){               // cant remove from empty stack!
            int Temp = Top->data;   // make a copy of top value
            Node* OldTop = Top;     // pointer to the top 
            Top = Top->next;        // move Top to next node.
            delete OldTop;          // delete node pointed to by OldTop
            return Temp;            // Now you can return popped value
        }
        return -999999;             // If there was a problem we return
                                    // a sentinel value. Better solution
                                    // later.
    }                               

    // is the stack empty?
    bool Empty(){
        return Top==NULL;
    }

    // Why don't we have a Full method?

    void Print(){
        Node* Current = Top;            // temp pointer to top of stack
        cout<<"Top->";                  
        while(Current){                 // while there are still nodes 
                                        //    in the list
            cout<<Current->data;        // print the data from node 

            if(Current->next){          // if we were at last node   
                cout<<"->";             //    current->next would be NULL!
            }                         

            Current = Current->next;    // move our pointer down the list
        }
        cout<<"->NULL"<<endl;
    }
};

int main() {
  ListStack L;    //now an object ( or instance )

  L.Push(45);      // comments??
  L.Push(33);
  L.Push(56);
  L.Push(2);
  L.Push(31);
  L.Push(88);

  L.Print();
  L.Pop();
  L.Print();
  L.Push(55);
  L.Print();
  L.Pop();
  L.Pop();
  L.Print();

  // if there are still items on the list
  // pop them off and print them
  while(!L.Empty()){
      int x = L.Pop();
      cout<<x<<endl;
  }

}