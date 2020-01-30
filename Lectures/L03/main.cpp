#include <iostream>
#include <string>

using namespace std;

const string spade = "♠";
const string diamond = "♦";
const string heart = "♥";
const string club = "♣";

const string suits[4]={"♠", "♦", "♣", "♥"};
const string ranks[13]={"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};


class Card{
private:
    int suitNum;   // 0-3
    int rank;   // 0 - 13
    int number; // 1-52
    int value;  // 1-14 
    string suitChar;
    string rankChar;
public:
    Card(int num){
        number = num;
        suitNum = number / 13;
        suitChar = suits[suitNum];
        rank = number % 13;
        rankChar = ranks[rank];
    }
    

    friend ostream& operator<<(ostream& os,const Card obj){

        os << "┌────┐\n";
        os << "│";
        if(obj.rank != 9){
            os<<" ";
        }
        os << obj.rankChar << " " << obj.suitChar<<"│\n";
        os << "└────┘";

        return os;
    }

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
    Card* cards[52];
    for(int i=0;i<52;i++){
        cards[i]= new Card(i);
        cout<<*cards[i]<<endl;
    }
    return 0;
}