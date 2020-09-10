///////////////////////////////////////////////////////////////////////////////
// This is a helper program for the resize stack assignment. This code opens an 
// input file of pushes and pops. The file should be formatted like this:
// 
//     push X
//     pop
//
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    ifstream fin;
    string command;
    int value;

    fin.open("input.txt");
    while(!fin.eof()){
        fin>>command;           // read push or pop  
        cout<<command<<" ";


        if(command == "push"){  // if command is a push we need
            fin>>value;         // to read a value in as well
            cout<<value;    
        }
        
        cout<<endl;

    }
}
