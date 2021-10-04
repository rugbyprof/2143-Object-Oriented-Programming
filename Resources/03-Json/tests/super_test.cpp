#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>

#include "../json.hpp"

using namespace std;
using json = nlohmann::json;
//https://github.com/nlohmann/json

int main(){
    json jData;
    int Size;
    string FileName;

    // read a JSON file
    ifstream input("../data/super_heros.json");
    input >> jData;  // 
    input.close();

    // access a single key value pair in object
    cout<<jData["squadName"]<<endl;

    json Hero = jData["members"][0];    // get the first "hero" from the array of 'members'
    cout<<Hero<<endl;
    // Prints {"age":29,"name":"Molecule Man","powers":["Radiation resistance","Turning tiny","Radiation blast"],"secretIdentity":"Dan Jukes"}

    json Members = jData["members"];    // gets the entire array of heroes array
    cout<<Members<<endl;
    // Prints:
    //[{"age":29,"name":"Molecule Man","powers":["Radiation resistance","Turning tiny","Radiation blast"],"secretIdentity":"Dan Jukes"},
    // {"age":39,"name":"Madame Uppercut","powers":["Million tonne punch","Damage resistance","Superhuman reflexes"],"secretIdentity":"Jane Wilson"},
    // {"age":1000000,"name":"Eternal Flame","powers":["Immortality","Heat Immunity","Inferno","Teleportation","Interdimensional travel"],"secretIdentity":"Unknown"}]

    // What if you wanted to print the names of each hero?
    for (auto& mem : Members) {
        cout<<mem["name"]<<endl;
        // also write out thier powers
        for(int i=0;i<mem["powers"].size();i++){
            cout<<mem["powers"][i]<<endl;
        }
    }

    // loop trough each member in the members array (grabbing it straight from the original object)
    for (auto& el : jData["members"]) {

        // print out member name
        std::cout << el["name"] << '\n';

        el["powers"].push_back("new super power");

        // loop through the members powers and print them out
        for (auto& power : el["powers"]) {
            std::cout <<"\t"<< power << '\n';
        }
    }

    // write entire json object out to a new file
    // could be useful if we changed any of the data
    std::ofstream ofs("../data/pretty.json");
    ofs << std::setw(4) << jData << std::endl;
}