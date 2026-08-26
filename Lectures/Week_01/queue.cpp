#include <iostream>
#include <fstream>

using namespace std;


struct Node{
    int data;
    Node* next;
    Node(int data):data(data),next(nullptr){}

};


class Queue{
    Node* front;
    Node* rear;
public:
    Queue(){
        front = rear = nullptr;
    }
    void push(int x){
        Node *temp = new Node(x);
        if (!front){
            front = rear = temp;
        }

    }
    int pop(){return 0;}
    void print(){
        cout<<"==========================================================\n";
        Node* travel = front;
        while(travel){
            
            cout<<travel->data;
            if(travel->next){
                cout<<"->";
            }
            travel = travel->next;
        }
        cout<<"==========================================================\n";
    }

};

int main(int argc,char** argv){

   Queue queue;
   queue.push(5);
   queue.push(3);
   queue.push(2);
   queue.print();

}