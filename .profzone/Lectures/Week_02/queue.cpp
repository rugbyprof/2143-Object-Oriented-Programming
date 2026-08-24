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
    Queue q;
    q.push("hello");
    q.push("frog");
    q.push("ant");
    q.push("dirt");
    q.push("chair");
    q.print();
    cout<<endl<<q.pop()<<endl;
    cout<<endl<<q.pop()<<endl;
    cout<<endl<<q.pop()<<endl;
    q.print();
    return 0;
}