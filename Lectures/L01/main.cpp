#include <iostream>

using namespace std;

struct Node{
  int data;
  Node* next;
  Node* prev;
  Node(){
    data = 0;
    next = prev = NULL;
  }
  Node(int d){
    data = d;
    next = prev = NULL;
  }
};

class MyVector{
private:
  Node* Head;
  Node* Tail;

public:
  MyVector(){
    Head = Tail = NULL;
  }

  void pushBack(int d){
    Node* temp = new Node(d);

    if(Head == NULL){
      Head = temp;
      Tail = temp;
    }else{
      Tail->next = temp;
      temp->prev = Tail;
      Tail = temp;
    }
  }

  void pushFront(int d){
    Node* temp = new Node(d);

    if(Head == NULL){
      Head = temp;
      Tail = temp;
    }else{
      temp->next = Head;
      Head->prev = temp;
      Head = temp;
    }
  }

  int popBack(){
    if(Tail){
      int d = Tail->data;
      Node* temp = Tail;
      Tail = Tail->prev;
      if(Tail){
        Tail->next = NULL;
      }else{
        Head = NULL;
      }
      
      delete temp;

      return d;
    }
    
    return -1;
  }

  int popFront(){
    if(Head){
      int d = Head->data;
      Node* temp = Head;
      Head = Head->next;
      if(Head){
        Head->prev = NULL;
      }else{
        Tail = NULL;
      }
      
      delete temp;

      return d;
    }
    return -1;
  }


  void print(){
    Node* temp = Head;

    while(temp){
      cout<<temp->data;
      if(temp->next){
        cout<<"->";
      }
      temp = temp->next;
    }
    cout<<endl;
  }

  void Sort(bool asc=true){
    Node* Start = Head;

    while(Start){
      Node* minp = Start;
      int   minv = Start->data;
      Node* mint = Start;
      bool doSwap=0;

      while(mint){
        if(asc){
          doSwap = (mint->data < minv);
        }else{
          doSwap = (mint->data > minv);
        }
        
        if(doSwap){
          minp = mint;
          minv = mint->data;
        }
        mint = mint->next;
      }

      //swap
      minp->data = Start->data;
      Start->data = minv;

      Start = Start->next;
    }

  }

};

int main() {
  MyVector V;

  for(int i=0;i<10;i++){
    V.pushFront(rand()%100);
  }

  V.print();

  int d = V.popBack();

  V.print();
  V.Sort(false);
  V.print();
    
}
