//Helpful ref: https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm

#include <iostream>
#include <string>

using namespace std;

// Simple yet limited fraction type.
// This is an ADT: or a user defined type.
// Remember:
//     A unique set of param types makes a one function
//     with the same name, different from another
struct frac{
  int numerator;      // top of fractions :)
  int denominator;    // bottom of fraction :)
  
  // Default constructor
  // 0 params: sets num/den == 1/1
  frac(){
    numerator = 1;
    denominator = 1;
  }
  
  // Overloaded constructor
  // 2 params: different from default because we have 2 ints
  //           being passed in.
  frac(int n,int d){  
    numerator = n;
    denominator = d;
  }

  // This is considered overloading because the addition operator has definitions
  // for all the primitive data types, however it does not understand what a `frac` 
  // type is. By defining this method, when a `+` sign is used between 2 `frac` types
  // this method will be called (even though it is sooo wrong arithmetically).
  frac operator+(const frac rhs){
    int num = numerator + rhs.numerator;
    int den = denominator + rhs.denominator;
    return frac(num,den);
  }
  
  // If we want to print out a fraction we need to overload cout, otherwise it doesn't know 
  // what to do. WHY? Because c++ cannot read the future. Anytime we make a new class / struct / etc.
  // C++ cannot read our mind, so we need to assist it into understanding what we want it to do
  // in specific situations (like printing out a fraction).
  ostream& operator<<(ostream& os,frac f){
    os<<f.numerator<<"/"<<f.denominator;
    return os;
  }

};

// Also an ADT (abstract data type)
// defined by us. If we wanted to print this out
// we would need to one of two things:
// Print every element seperate everytime we wanted to print the values,
// or, overload cout to know what to do with this data type.
struct person{
  string fname;
  string lname;
  double payrate;
  string ssn;
};

/**
* Basic (very basic) overloading example
* We have 3 sum functions each has a differing param list.
* This is OK. 
* If we were to add a fourth method: double sum(int a, int b); it would 
* error. Different return types is NOT ok when overloading methods.
*/
int sum(int a,int b){
  return a + b;
}

int sum(double a,int b){
  return a + b;
}

int sum(int a,int b, int c){
  return a + b;
}

/**
* Basic driver. May not thoroughly call each example.
*/
int main() {
  cout << "Hello World!\n";
  int c = sum(3,4);
  int d = sum(3,4,5);
  int e = sum(2.0,3);

  frac f1(3,8);
  frac f2(3,4);
  frac f3 = f1 + f2;

  person p;

  cout<<f2.numerator<<"/"<<f2.denominator<<endl;

  cout<<f1<<endl;

  cout<<f3<<endl;

  
}
