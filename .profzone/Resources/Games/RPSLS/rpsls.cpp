/*****************************************************************************
*                    
*  Author:           
*  Email:            theoopgamers@protonmail.com
*  Label:            Rock,Paper,Scissors,Lizard,Spock
*  Title:            Program 3A
*  Course:           2143-OOP
*  Semester:         Fall 2021
* 
*  Description:
*       Program that does Rock,Paper,Scissors,Lizard,Spock using Emojis as each object.
*       The rules are set in https://github.com/rugbyprof/2143-Object-Oriented-Programming/tree/master/Assignments/08-P03A 
*       This is a part one of our main project to help with defining weapons to our characters. 
*
*
* 
*  Usage:
*        just run in a folder with emoji.h
* 
*  Files:
*       main.cpp    :driver file
*       emoji.h     :emoji input 
*****************************************************************************/


#include <iostream>
//#include "emoji.h"    //https://github.com/99x/emojicpp
#include <functional>  // needed for `bind`
#include <map>
#include <random>
#include <string>
#include <fstream> 
#include <vector>

using namespace std;

#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"



/**
 * RandRoll
 * @description: A class to implement roll playing dice rolls.
 * @methods:
 * private:
 *      int Random(Max) : returns a value between 0 and max.
 *      int Random(Min , Max) : returns a value between min and max
 *      void init(int , int)  : initialize class
 * public:
 *      DieRoll()
 *      DieRoll(int)
 *      DieRoll(int,int)
 *      void setDie(int)    : set sides
 *      int Roll(int,int)   :  NEEDS FIXING!!!!!!
 */
class DieRoll {
    int sides;

    int Random(int max) {
        return 1 + (rand() % max);
    }

    // min = 40 max = 100
    int Random(int min, int max) {
        return 1 + min + (rand() % (max - min));
    }
    void init(int _seed, int _sides) {
        sides = _sides;
        srand(_seed);
    }
public:
    DieRoll() {
        //cout << "default base" << endl;
        init(time(0), 6);
    }
    DieRoll(int _seed) {
        //cout << "overloaded const" << endl;
        init(_seed, 6);
    }
    DieRoll(int _seed, int _sides) {
        //cout << "overloaded const" << endl;
        init(_seed, _sides);
    }

    void setDie(int _sides) {
        sides = _sides;
    }

    // NEEDS FIXING!!!
    int Roll(int sides, int times) {
        int sum = 0;
        while (times--) {
            sum += Random(sides);
        }
        return sum;
    }
};


/**
 * RandRoll
 * @description: A random die roller using a "better" random
 *      number generator. Docs: https://www.cplusplus.com/reference/random/
 * 
 * @methods:
 *     int Roll(int)    : give the "sides" will return an int between 1 and sides inclusive.
 * 
 */
class RandRoll {
    default_random_engine           generator;
    uniform_int_distribution< int > dieMap[21];

public:
    /**
     * Constructor
     * 
     * @description: Create an stl array that has the common dice values
     *              loaded as uniform distribution types.
     * 
     *  Wasteful, as not every array location has a uniform distribution 
     *  associated with it. Could you make it less wasteful?
     */
    RandRoll() {
        dieMap[4] = uniform_int_distribution< int >(1, 4);
        dieMap[6] = uniform_int_distribution< int >(1, 6);
        dieMap[8] = uniform_int_distribution< int >(1, 8);
        dieMap[10] = uniform_int_distribution< int >(1, 10);
        dieMap[12] = uniform_int_distribution< int >(1, 12);
        dieMap[20] = uniform_int_distribution< int >(1, 20);
    }

    /**
     * Generate a random number depending on the "sides" of the dice.
     */
    int Roll(int sides) {
        int diceRoll = dieMap[sides](generator);
        return diceRoll;
    };
};

map< string, string > Emojis = {
    {"rock", ROCK2},
    {"paper", PAPER2},
    {"scissors", SCISSORS2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2}
};

map<string,vector<string>> Rules = {
    {"rock", {"scissors","lizard"}},
    {"paper", {"rock","spock"}},
    {"scissors", {"lizard","paper"}},
    {"lizard", {"spock","paper"}},
    {"spock", {"rock","scissors"}}
};

string RandHand() {
    auto it = Emojis.begin();  // iterator to front of map
    std::advance(it, rand() % Emojis.size());  // advance some random amnt
                                              //   of steps
    string random_hand = it->second;  // grab emoji from map
    return random_hand;  // return rand emoji
}

/*
 * Scissors cuts Paper
 * Paper covers Rock
 * Rock crushes Lizard
 * Lizard poisons Spock
 * Spock smashes Scissors
 * Scissors decapitates Lizard
 * Lizard eats Paper
 * Paper disproves Spock
 * Spock vaporizes Rock
 * Rock crushes Scissors
 */
class Weapon{
private:

protected:
  string name;
public:
  Weapon(){
    name = RandHand();
  }
  Weapon(string n){
    name = n;
  }

  friend ostream& operator<<(ostream& os, const Weapon &w){
    return os << w.name;
  }

  //this = paper
  //rhs spock
  // paper < spock

  bool operator==(const Weapon &rhs){
    return this->name == rhs.name;
  }

  bool operator<(const Weapon &rhs){
    if(this->name == rhs.name){
      return 0;
    }
    if(count(Rules[this->name].begin(), Rules[this->name].end(), rhs.name)){
      return 0;
    }
    return 1;
  }

  bool operator>(const Weapon &rhs){
    if(this->name == rhs.name){
      return 0;
    }
    if(count(Rules[this->name].begin(), Rules[this->name].end(), rhs.name)){
      return 1;
    }
    return 0;
  }
};

class Character{
private:
  Weapon *primary;
  Weapon *secondary;
public:
  Character(){
    primary = new Weapon();
    secondary = new Weapon();
  }
  Character(string p,string s){
    primary = new Weapon(p);
    secondary = new Weapon(s);
  }

  friend ostream& operator<<(ostream &os,const Character &c){
    return os << "["<<*c.primary<<","<<*c.secondary<<"]";
  }

  bool operator>(const Character &rhs){
    if(this->primary>rhs.primary){
      return 1;
    }else if(this->secondary>rhs.secondary){
      return 1;
    }
    return 0;
  }

  bool operator<(const Character &rhs){
    if(this->primary<rhs.primary){
      return 1;
    }else if(this->secondary<rhs.secondary){
      return 1;
    }
    return 0;
  }
};

int main() {
    srand(time(0));
    Weapon w1;
    Weapon w2;

    Character c1;
    Character c2;

    cout<<w1<<" "<<w2<<endl;
    cout<<Rules["rock"][0]<<endl;
    cout<<(w2<w1)<<endl;

    cout<<c1<<endl;
    cout<<c2<<endl;

    return 0;
}
