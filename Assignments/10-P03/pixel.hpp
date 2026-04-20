#pragma once

#include <iostream>
#include <vector>


using namespace std;


struct Pixel {
    int r, g, b;
};

using Image = std::vector<std::vector<Pixel>>;
