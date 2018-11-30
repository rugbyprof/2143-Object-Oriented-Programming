#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////
//Question 1 answer

// #	  Word	        
// 1	  Constructor	  I	  A member function of which initializes objects of a class
// 2	  Friend	      G	  Can access private and protected members of other class in which it is declared
// 3	  Inheritance	  B	  The capability of a class to derive properties and characteristics from another class
// 4	  Overloading	  F	  It provides multiple definitions of the function by changing signature (parameters)
// 5	  Override	    AH	A member function which is declared within base class and is re-defined by derived class
// 6	  Polymorphism	E	  Overriding an operator for a class is an example of ….
// 7	  Protected	    C	  Supports an important feature of Object Oriented Programming known as Data Hiding
// 8	  Static	      D	  Preserves their value even after they are out of their scope
// 9	  This	        J	  A constant pointer that holds the memory address of the current object
// 10	  Virtual	      HA	The redefinition of base class function in its derived class with same signature

// Note: I missed a key word in the definition of "H". It should have read:
// A member function which is declared within base class and must be re-defined by derived class

// Since I did that A and H are arguably interchangeable 

///////////////////////////////////////////////////////////
//Question 5 answer

// A) ostream needs to be a "friend" so it can access private data members in the class it's being used by
// B) False : Friendship is not mutual. Class A friends B, does not mean B gives a the same access.
// C) Fasle : Friendship cannot be inherited, it must be explicitly stated

///////////////////////////////////////////////////////////
//Question 2 required answer

class Point3D{
    int x;
    int y;
    int z;
public:
    Point3D();
    Point3D(int , int , int );
    Point3D(const Point3D &);
// end question 2 required

///////////////////////////////////////////////////////////
// Question 3 necessary step so it can access private data members
    //friend Point3D operator + (const Point3D &,const Point3D &); 

  Point3D operator + (const Point3D &rhs){
    Point3D temp;

    return Point3D(x + rhs.x,y + rhs.y,z + rhs.z);
  }

///////////////////////////////////////////////////////////
// Question 4
    friend ostream& operator << (ostream &os, const Point3D &rhs){
      os<<"["<<rhs.x<<" , "<<rhs.y<<" , "<<rhs.z<<"]";
      return os;
    }


};

//Question 2 Implementation to demonstrate usage
Point3D::Point3D(){x=y=z=0;}
Point3D::Point3D(int x, int y, int z){
  this->x = x;
  this->y = y;
  this->z = z;
}
Point3D::Point3D(const Point3D &r){
  this->x = r.x;
  this->y = r.y;
  this->z = r.z;
}

///////////////////////////////////////////////////////////
// Question 3 
// Point3D operator + (const Point3D &lhs,const Point3D &rhs){
//   return Point3D(lhs.x+rhs.x,lhs.x+rhs.y,lhs.x+rhs.z);
// }


///////////////////////////////////////////////////////////
//Question 2a
// The system will create a temporary copy constructor for you.
// However, it does not always work correctly
///////////////////////////////////////////////////////////
class noCopyConstructor{
public:
  int a;
  int b;
  int c;

  noCopyConstructor(){
    a=rand() %100;
    b=rand() %100;
    c=rand() %100;
  }

};
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//Question 6 Required Answer
class Line3D{

  Point3D P1;
  Point3D P2;
public:
  Line3D();
  Line3D(Point3D , Point3D );
  Line3D(int ,int ,int ,int ,int , int );
};

//Question 6 Implementation to demonstrate usage
Line3D::Line3D(){
  cout<<"\nQuestion 6 default constructor output:\n";
  cout<<P1<<P2<<endl;
}
Line3D::Line3D(Point3D p1, Point3D p2){
  P1 = p1;
  P2 = p2;
  cout<<"\nQuestion 6 2nd constructor output:\n";
  cout<<P1<<P2<<endl;
}
Line3D::Line3D(int a,int b,int c,int d,int e, int f){
  P1 = Point3D(a,b,c);
  P2 = Point3D(d,e,f);
  cout<<"\nQuestion 6 3rd constructor output:\n";
  cout<<P1<<P2<<endl;
}
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//Question 7 : extended answer
class Animal {
protected:  // had to make protected otherwise child classes cannot access

	int Speed;
	int Legs;

public:
    int speed() { 		// get the animals speed
        return Speed; 
    }
    virtual int legs() = 0; 		// set the number of legs
    virtual void legs(int) = 0;		// get the number of legs
};

class Cheetah : public Animal {
public:
    Cheetah(){
      Speed = 60;
      Legs = 4;
    }

    // Overloading the speed method by changing the signature
    void speed(int val){
      Speed = val;
    }

    // Overriding the legs method because its virtual and I have to
    int legs(){
      return Legs;
    }

    // Overriding the other legs method because its virtual and I have to
    void legs(int val){
      Legs = val;
    }
};

///////////////////////////////////////////////////////////
//Question 8 :

int countMe(){
  static int count = 0;
  return ++count;
}

///////////////////////////////////////////////////////////
int main() {
  
    Point3D P1(3,-1,12);
    Point3D P2 = P1;
    Point3D P3 = P1 + P2;

///////////////////////////////////////////////////////////
// Question 2a proof of correctness :)
    cout<<"\nQuestion 2A showing a copy constructor will be created for you:\n";
    noCopyConstructor C1;
    cout<<C1.a<<","<<C1.b<<","<<C1.c<<endl;
    cout<<endl;

// Invoke a copy constructor that doesnt exist
    noCopyConstructor C2 = C1;
    cout<<"copy 2"<<endl;
    cout<<C2.a<<","<<C2.b<<","<<C2.c<<endl;
    cout<<endl;

    //Change C1 to see if it changes C2
    C1.a = 999;
    cout<<C1.a<<","<<C1.b<<","<<C1.c<<endl;
    cout<<C2.a<<","<<C2.b<<","<<C2.c<<endl;
    cout<<endl;
    //Change C2 to see if it changes C1
    C2.c = 999;
    cout<<C1.a<<","<<C1.b<<","<<C1.c<<endl;
    cout<<C2.a<<","<<C2.b<<","<<C2.c<<endl;
    cout<<endl;
    //See if addresses of each object are the same
    cout<<"Addresses of C1 and C2 non pointer classes:\n";
    cout<<&C1<<","<<&C2<<endl;

// Now lets try a pointer to a noCopyConstructor class;

    noCopyConstructor *pC1 = new noCopyConstructor;
    noCopyConstructor *pC2 = pC1;

    cout<<"Address of:\n";
    cout<<pC2<<","<<pC1<<endl;

    //Change C1 to see if it changes C2
    pC1->a = 3;
    pC1->b = 2;
    pC1->c = 1;
    cout<<pC1->a<<","<<pC1->b<<","<<pC1->c<<endl;
    cout<<pC2->a<<","<<pC2->b<<","<<pC2->c<<endl;
    cout<<endl;

    //Change C2 to see if it changes C1
    pC2->a = 1;
    pC2->b = 2;
    pC2->c = 3;
    cout<<pC1->a<<","<<pC1->b<<","<<pC1->c<<endl;
    cout<<pC2->a<<","<<pC2->b<<","<<pC2->c<<endl;
    cout<<endl;
    cout<<"Addresses of C1 and C2  pointer classes:\n";
    cout<<pC1<<","<<pC2<<endl;


///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Question 3 output
    cout<<"\nQuestion 3 output (overloading + operator):\n";
    cout<<P3<<endl;
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Question 4 output
    cout<<"\nQuestion 4 output (overloading cout):\n";
    cout<<P2<<endl;
    ///////////////////////////////////////////////////////////

    Line3D L1;
    Line3D(P1,P3);
    Line3D(1,2,3,4,5,6);

    Cheetah C;


///////////////////////////////////////////////////////////
// Question 8 output
    cout<<"\nQuestion 8 output (static keyword):\n";

    for(int i=0;i<rand()%100;i++){
      countMe();
    }

    
    cout<<"countMe() was called: "<<countMe()<<" times."<<endl;
}
