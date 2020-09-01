///////////////////////////////////////////////////////////////////////////////
//
// Struct example 2 : using a pointer to "point" to P1
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

    person *PP = &P1;                   // point PP to the "address of" P1

    cout<<"First: "<<PP->fname<<endl;   // print out values of P1 (again)
    cout<<"Last: "<<PP->lname<<endl;
    cout<<"Age: "<<PP->age<<endl;

    person *P2 = new person;            // allocate a "new" person

    P2->fname = "joe";                  // load each data member with values
    P2->lname = "brown";
    P2->age = 19;

    cout<<"First: "<<P2->fname<<endl;   // print out values of P2
    cout<<"Last: "<<P2->lname<<endl;
    cout<<"Age: "<<P2->age<<endl;


}