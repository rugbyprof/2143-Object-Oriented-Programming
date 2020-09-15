#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void randomGame(int rows,int cols,string filename){
    ofstream fout;

    fout.open(filename);

    fout<<rows<<" "<<cols<<endl;

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            fout<<rand()%2<<" ";
        }
        fout<<endl;
    }

}

class GOL{
private:
    int **A;
    int rows;
    int cols;
    void _buildTwoDArray();
public:
    GOL();                  // default constructor
    GOL(int ,int );         // pass in width and height
    GOL(int);               // use value for width and height 
    GOL(string);            // filename to load game board
    void loadFile(string);  
    void randomWorld();
    void printTwoDArray();
};


void GOL::_buildTwoDArray(){

    A = new int*[rows];

    for(int i=0;i<rows;i++){
        A[i] = new int[cols];
        for(int j=0;j<cols;j++){
            A[i][j] = 0;
        }
    }
}

GOL::GOL(){
    rows = 10;
    cols = 10;
    
    _buildTwoDArray();
    randomWorld();
}

GOL::GOL(int r,int c){
    rows = r;
    cols = c;
    
    _buildTwoDArray();
    randomWorld();
}

GOL::GOL(int size){
    rows = size;
    cols = size;
    
    _buildTwoDArray();
    randomWorld();
}

GOL::GOL(string filename){
    loadFile(filename);
}

void GOL::loadFile(string filename){
    ifstream fin;
    fin.open(filename);

    fin>>rows>>cols;

    _buildTwoDArray();

    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            fin>>A[i][j];
        }
    }

}

void GOL::randomWorld(){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            A[i][j] = rand()%2;
        }
    } 
}

void GOL::printTwoDArray(){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    } 
}

