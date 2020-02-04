#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>

#include "../json.hpp"

using namespace std;
using json = nlohmann::json;
//https://github.com/nlohmann/json

int main(){
    json Data;
    int Size;
    string FileName;

    // read a JSON file
    ifstream input("../data/super_heros.json");
    input >> Data;
    input.close();

    // access a single key value pair in object
    cout<<Data["squadName"]<<endl;

    // loop trough each member in the members array
    for (auto& el : Data["members"]) {

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
    ofs << std::setw(4) << Data << std::endl;
}