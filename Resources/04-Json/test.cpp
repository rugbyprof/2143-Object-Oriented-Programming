#include "JsonFacade.hpp"
#include <iostream>
#include <fstream>


using namespace std;

int main(){
    ifstream fin("./data/super_heros.json");
    json super;
    json members;
    fin >> super;
    
    for (json::iterator it = super.begin(); it != super.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << "\n";
    }

    members = super["members"];

    for (auto& el : members.items()) {
        std::cout << el.key() << " : " << el.value() << "\n";
    }


    return 0;
}