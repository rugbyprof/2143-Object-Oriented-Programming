#include <iostream>
#include <string>

using namespace std;

class Point {
  float x;
  float y;

public:
  void Move(float dx, float dy) {
    x += dx;
    y += dy;
  }
  void Jump(float dx, float dy) {
    x = dx;
    y = dy;
  }
};

class Line {
  Point A;
  Point B;

  void Move(float adx, float ady, float bdx, float bdy) {
    A.Move(adx, ady);
    B.Move(bdx, bdy);
  }

  void Jump() {}
};

class Character {
private:
  string fname;
  string lname;
  string email;
  string charName;
protected:
  int intelligence;
  // int strength;
  // int manna;
public:
  void setFname(string f) { fname = f; }
  string getFname() { return fname; }
  void setCharname(string c) { charName = c; }
  string getCharname() { return charName; }
  Character(string f,string l,string c){
    fname =f ;
    lname = l;
    charName = c;
  }
};

class Magician : public Character {
private:
  int manna;

public:
  Magician(string f,string l, string c) : Character(f,l,c){
    manna = (rand() % 90) + 10;
    intelligence = (rand() % 90) + 10;
  }
  void setManna(int m) { manna = m; }
  int getManna() { return manna; }
  void setIntelligence(int i) { intelligence = i; }
  int getIntelligence() { return intelligence; }
};

class Warrior : public Character {
  string weapon;
};

int main() { 
  Magician M1("Joe","Smith","joemomma"); 

  cout<<M1.getFname()<<endl;
  cout<<M1.getManna()<<endl;
  cout<<M1.getIntelligence()<<endl;
}