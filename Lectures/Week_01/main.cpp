#include <iostream>

using namespace std;

// private
class Stack{
private:
    int top;
    int size;
    int *stack;
public: 
    Stack(){
        top = -1;
        size = 10;
        stack = new int[size];

    }
    Stack(int size):top(-1),size(size),stack(new int[size]){}
    
};


int main(int argc, char** argv){
    cout<<"Stack it bab!"<<endl;
    Stack stack1;
    Stack stack2(100);
}