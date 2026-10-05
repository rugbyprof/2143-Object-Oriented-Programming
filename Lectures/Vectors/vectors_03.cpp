#include <iostream>
#include <vector>
#include <time.h>
#include <string>

using namespace std;

// Vector data types
typedef vector<int> vint;           // vector of ints
typedef vector< vector<int> > twoD; // vector of vector of ints
typedef vector<vint> twoDagain;     // another way to typedef 2D vector

// Purpose: 
//    One way to loop through a 1D vector and print.
// PARAMS:
//    twoD - A 2D vector
// RETURNS: void
void PrintVector(vint A){
  for(auto i = A.begin();i != A.end(); i++){
    cout<<*i<<" ";
  }
}

// Purpose: 
//    Another way to loop through a 1D vector and print.
// PARAMS:
//    twoD - A 2D vector
// RETURNS: void
void PrintVector2(vint A){
  for(auto val : A){
    cout<<val<<" ";
  }
}

// Purpose: 
//    Loop through a 2D vector and print it.
//    We do NOT need to pass size in to print it!!
// PARAMS:
//    twoD - A 2D vector
// RETURNS: void
void Print2DVector(twoD vv){
  for(auto row = vv.begin();row != vv.end(); row++){
    for(auto col = row->begin(); col != row->end(); col++){
      if(*col < 10){
        cout<<"00";
      }else if(*col < 100){
        cout<<"0";
      }
      cout<<*col<<" ";
    }
    cout<<endl;
  }
}

// Purpose: 
//    Loop through a 2D vector the fast way and print it.
//    We still do NOT need to pass size in to print it!!
// PARAMS:
//    twoD - A 2D vector
// RETURNS: void
void Print2DVector2(twoD vv){
  for(auto row: vv ){
    for(auto col: row){
      if(col < 10){
        cout<<"00";
      }else if(col < 100){
        cout<<"0";
      }
      // NO dereferencing!!
      cout<<col<<" ";
    }
    cout<<endl;
  }
}

// Purpose: 
//    Creates and loads a 2D vector with random vals using
//    array like syntax.
// PARAMS:
//    int - num rows
//    int - num cols
// RETURNS: a 2D vector filled 
twoD load2Dvector(int rows,int cols){
  twoD A;

  A.resize(rows); // reserve space to give us something loop
                  // over. I picture this as building the 
                  // first column.

  // Loop over first column resizing each vector
  // to create proper number of columns.
  for(auto row = A.begin();row != A.end(); row++){
    row->resize(cols);  
    for(auto col = row->begin();col != row->end(); col++){
      *col = rand() % 1000;
    }
  }

  return A;
}

// Purpose: 
//    Creates and loads a 2D vector with random vals using
//    iterators
// PARAMS:
//    int - num rows
//    int - num cols
// RETURNS: a 2D vector filled 
twoD load2Dvector2(int rows,int cols){
  twoD A;

  A.resize(rows); // reserve space to give us something loop
                  // over. I picture this as building the 
                  // first column.

  // Loop over first column resizing each vector
  // to create proper number of columns.
  for(int i=0;i<rows;i++){
    A[i].resize(cols);  
    for(int j=0;j<cols;j++){
      // Reference vector just like 2D array!
      A[i][j] = rand() % 1000;
    }
  }

  return A;
}

int main() {
  srand(time(0)); // Seed with time so it changes

  vint A;  // 1D vector

  for(int i =0;i<rand()% 30;i++){
    A.push_back(rand()% 30);
  }

  // Print it one way
  PrintVector(A);
  cout<<endl<<endl;
  // Print a different way
  PrintVector2(A);
  cout<<endl<<endl;

  // create and load a twoDvector of random size.
  twoD vv = load2Dvector(rand()%30,rand()%30);
  twoD vv2 = load2Dvector2(rand()%30,rand()%30);

  Print2DVector(vv);
  cout<<endl;
  Print2DVector2(vv);
  cout<<endl;
  Print2DVector2(vv2);

}