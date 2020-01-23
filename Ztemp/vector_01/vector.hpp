#include <iostream>

using namespace std;

class MyVector{
private:
    int* container;     // container of values
    int max_size;       // size of container
    int i;              // index location
public:
    MyVector(){
        container = new int[25];
        max_size = 25;
        i = 0;
    }

    bool pushBack(int value){
        container[i] = value;
        i++;
        if(i >= max_size){
            resize();
        }
        
        return true;
    }

    //problems with this implementation. Doesn't leave room for exception handleing.
    int popBack(){
        return container[--i];
    }

    void resize(){
        int new_size = max_size * 1.5;
        int* newContainer = new int[new_size];

        for(int j=0;j<i;j++){
            newContainer[j] = container[j];
        }

        delete [] container;

        container = newContainer;

        max_size = new_size;

    }

    void print(){
        for(int j=0;j<i;j++){
            cout<<container[j]<<" ";
        }
    }

    int currentSize(){
        return max_size;
    }

};

