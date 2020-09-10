#include <iostream>
#include <fstream>
#include <string>

int main(){
    ifstream fin;
    string command;
    int value;

    fin.open("input");
    while(!fin.eof()){
        fin>>command;  //pop
        cout<<command<<endl;

        if(command == "push"){
            fin>>value;
            cout<<value<<endl;
        }

    }
}
