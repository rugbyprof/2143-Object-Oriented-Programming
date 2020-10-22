#include <iostream>
using namespace std;

class A{
  protected:
  int id;
  public:
  A(){
    id = 1;
  }
  int getId(){
    return id;
  }
};

class B : public A{
  protected:
  int id;
  public:
  B(){
    id =2;
  }

};

class C : public B{
  protected:

  public:
  C(){
    id =3;
  }
  // int getId(){
  //   return id;
  // }

};

  
int main () {
  C c;
  cout<<c.getId()<<endl;
  return 0;
}
