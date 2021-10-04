#include "../json.hpp"
#include "../JsonFacade.hpp"
#include <iostream>

using namespace std;

struct Animal {
    string animal_name;
    long date;
    double latitude;
    double longitude;
    float adjuster;
    bool validated;
    string version;
    float priority;

    Animal() {
        animal_name = "";
        date = 0;
        latitude = 0.0;
        longitude = 0.0;
        adjuster = 0.0;
        validated = 0;
        version = "";
        priority = 0.0;
    }

    Animal(string name, long _date, double lat, double lon, float adj, bool val, string ver) {
        animal_name = name;
        date = _date;
        latitude = lat;
        longitude = lon;
        adjuster = adj;
        validated = val;
        version = ver;
        priority = 0.0;
    }

    Animal(json j) {
        animal_name = j["animal_name"];
        date = j["date"];
        latitude = j["latitude"];
        longitude = j["longitude"];
        adjuster = j["adjuster"];
        validated = j["validated"];
        version = j["version"];
        priority = 0.0;
    }
};

int main(){

    Animal **Animals;
    JsonFacade *J;
    json obj;
    int size;

    J = new JsonFacade("../data/animals.json");
    size = J->getSize();
    Animals = new Animal *[size];
    for (int i = 0; i < size; i++) {
        obj = J->getNext();
        Animals[i] = new Animal(obj);
    }
    

    for (int i = 0; i < size; i++) {
            cout << Animals[i]->animal_name << " " 
            << Animals[i]->latitude << " " 
            << Animals[i]->longitude << " " 
            << Animals[i]->date << " " 
            << Animals[i]->adjuster << " " 
            << Animals[i]->validated << " " 
            << Animals[i]->version << " "
            << Animals[i]->priority << endl;
    }
}