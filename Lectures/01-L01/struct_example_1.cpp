///////////////////////////////////////////////////////////////////////////////
//
// Struct example 1
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

using namespace std;

/**
 * Example "struct" or package of data variables to represent a "person".
 * It could easily hold many more data members.
 */
struct person{
    string fname;
    string lname;
    int age;
};


int main() {

    person P1;              // create an instance of simple_person

    P1.fname = "sue";       // load each data member with values
    P1.lname = "smith";
    P1.age = 20;

    cout<<"First: "<<P1.fname<<endl;    // print out values
    cout<<"Last: "<<P1.lname<<endl;
    cout<<"Age: "<<P1.age<<endl;

}