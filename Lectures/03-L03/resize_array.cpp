#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

#define SIZE 10

/**
* Will write random 
*    push int
*    pop 
*    
*/
void PopulateFile(string filename,int items){
    //ofstream fout(filename,ofstream::out);

    ofstream fout;

    fout.open("input");

    for(int i=0;i<items;i++){
       
        if(random() % 2 == 0){
            fout<<"push "<<random() % 100;
        }else{
            fout<<"pop";
        }
        fout<<endl;
        
    }

    fout.close();

}

int main() {
    srand(time(0));

    ifstream infile;

    // Do One Time to put data into file.
    PopulateFile("input",10000);
    exit(0);

    int *S = new int[SIZE];

    // assigning
    for(int i = 0;i<SIZE;i++){
        S[i] = i * 3;
    }

    // Allocate new array twice as big
    int *S2 = new int[2*SIZE];

    // Copy data from S to S2
    for(int i = 0;i<SIZE;i++){
        S2[i] = S[i];
    }

    // Write out data in S
    for(int i = 0;i<SIZE;i++){
        cout<<S[i]<<" ";
    }  
    cout<<endl<<endl;

    // Write out data in S2
    for(int i = 0;i<2*SIZE;i++){
        cout<<S2[i]<<" ";
    }
    cout<<endl;

    // Delete old array 
    delete [] S;

    // Point S to new array
    S = S2;


}