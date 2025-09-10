#include <iostream>

using namespace std;

class Person{
    int id;
    string first;
    string last;
public:
    Person():id(-1),first(""),last(""){}
    Person(int i,string f, string l):id(i),first(f),last(l){}

    friend ostream& operator<<(ostream& banana, Person &p){
        return banana<<"["<<p.id<<" "<<p.first<<" "<<p.last<<"]";
    }

    bool operator<(const Person& other){
        return this->last < other.last;
    }
    bool operator>(const Person& other){
        return this->last > other.last;
    }
    bool operator==(const Person& other){
        return this->last== other.last;
    }
};

struct Node{
    Person p;
    Node* next;
    Node(Person p):p(p),next(nullptr){}
};

class LL{

};


int main() {
    int id;
    string fname;
    string lname;


    cin>>id>>fname>>lname;
    Person P1(id,fname,lname);

    cin>>id>>fname>>lname;
    Person P2(id,fname,lname);

    string res;
    if(P1 < P2)
        res = "true";
    else
        res = "false";
    cout<<res<<endl;
    
  
    // while(cin>>id>>fname>>lname){
    //     Person p(id,fname,lname);
    //     cout<<p<<endl;
    // }

    return 0;
}
