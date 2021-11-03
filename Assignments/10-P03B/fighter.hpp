#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "weapon.hpp"
#include "helpers.hpp"

using namespace std;

#pragma once


class BaseFighter {
    string name;
    Weapon *weapon;

public:
    BaseFighter() {
        name = "None";
        weapon = new Weapon;
    }

    virtual double attack(){
        return weapon->use();
    }

    friend ostream& operator<<(ostream& os, const BaseFighter& f) {
        return os << "[" << f.name << " , " << *f.weapon << "]";
    }

};