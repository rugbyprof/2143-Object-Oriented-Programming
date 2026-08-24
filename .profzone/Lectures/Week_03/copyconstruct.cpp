#include <iostream>
#include <string>

using namespace std;

struct Node{
    string val;
    Node* next;
    Node(string v):val(v),next(nullptr){}
};


class Queue{
private:
    Node* front;
    Node* rear;
public:
    Queue(){
        front = rear = nullptr;
    }
    Queue(const Queue& other){
        cout<<"hello"<<endl;
        Node* travel = other.front;
        while(travel){
            this->push(travel->val);
            travel = travel->next;
        }
    }
    void push(string v){
        Node* temp = new Node(v); // allocate new memory
        // is list empty?
        if(!front){
            front = rear = temp; //copy address of temp into head
        }else{
            rear->next = temp;
            rear = temp;
        }
        return;
    }

    string pop(){
        string hold = front->val;
        Node* temp = front;
        front = front->next;
        delete temp;
        return hold;
    }

    void print(){
        Node* travel = front;
        while(travel){
            cout<<travel->val;
            if(travel->next){
                cout<<"->";
            }
            travel = travel->next;
        }
        cout<<endl;
    }

};

int main(int argc, char** argv){
    Queue q1;
    
    q1.push("hello");
    q1.push("frog");
    q1.push("ant");

    q1.push("dirt");
    q1.push("chair");
    q1.print();
    cout<<endl<<q1.pop()<<endl;
    cout<<endl<<q1.pop()<<endl;
    cout<<endl<<q1.pop()<<endl;
    Queue q2 = q1;
    q1.print();
    q2.print();
    q1.push("anteater");
    q1.print();
    q2.print();
    q2.pop();
    q1.print();
    q2.print();
    return 0;
}