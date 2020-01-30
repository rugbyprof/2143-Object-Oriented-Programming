#include <iostream>
#include <string>
#include "termio.h"

using namespace std;

const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4]={"♠", "♦", "♣", "♥"};
const string colors[4]={"&60","&20","&60","&20"};
const string ranks[13]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};


class Card{
private:
    int suitNum;    // 0-3
    int rank;       // 0 - 13
    int number;     // 1-52
    int value;      // 1-14 
    string suitChar;
    string rankChar;
    string color;
public:
    Card(int num){
        number = num;
        suitNum = number / 13;
        suitChar = suits[suitNum];
        color = colors[suitNum];
        rank = number % 13;
        rankChar = ranks[rank];
    }
    
    string Repr(){
        string s = "";
        s += "┌────┐\n";
        s += "│";
        if(rank != 9){
            s+=" ";
        }
        s += color+rankChar + " " + suitChar + "&00│\n";
        s +=  "└────┘";
        return s;
    }

    friend ostream& operator<<(ostream& os, Card obj){

        os << obj.Repr();

        return os;
    }

    // friend ostream& operator<<(ostream& os,const Card obj){

    //     os << "┌────┐\n";
    //     os << "│";
    //     if(obj.rank != 9){
    //         os<<" ";
    //     }
    //     os << obj.rankChar << " " << obj.suitChar<<"│\n";
    //     os << "└────┘";

    //     return os;
    // }




};

class Deck{
    // dealCard
    // shuffleCards
    // resetDeck

};

class Hand{

};

class Game{

};




int main(){
    Term::IO io;
    Card* cards[52];
    for(int i=0;i<52;i++){
        cards[i]= new Card(i);
        io<<Term::clear;
        io<<cards[i]->Repr()<<"\n";
        io<<Term::sleep(300);
    }
    // Card c1(4);
    // Card c2(14);
    // Card c3(23);
    // Card c4(38);
    // Card c5(29);



    // io<<Term::Point(5,0);

    

    // cout<<Term::fuse({c1.Repr(),c2.Repr(),c3.Repr(),c4.Repr(),c5.Repr()})<<endl;





    return 0;
}