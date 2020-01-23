#include <iostream>
#include <string>
#include <random>
#include "vector.hpp"

using namespace std;

string RandomString(int len)
{
   srand(time(0));
   string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   string newstr = "";
   int pos;
   while(newstr.size() != len) {
    pos = ((rand() % (str.size() - 1)));
    newstr += str.substr(pos,1);
   }
   return newstr;
}

struct Person{
    string lname;
    string fname;
    double salary;
    Person(){
        lname = RandomString((rand()%14)+5);
        fname = RandomString((rand()%14)+5);
        salary = 0.0;
    }
    Person(string lname,string fname,double salary){
        lname = lname;
        fname = fname;
        salary = salary;
    }
};

int main(int argc, char** argv){
    MyVector<Person> V;

    V.pushBack(new Person("smith","terry",343343.99));
    V.pushBack(new Person("wilson","bubba",443343.99));
    V.pushBack(new Person("road","bob",43343.99));
    V.print();

    for(int i=0;i<50;i++){
        V.pushBack(new Person());
    }

    V.print();
    cout<<endl<<V.currentSize()<<endl;
    return 0;
}