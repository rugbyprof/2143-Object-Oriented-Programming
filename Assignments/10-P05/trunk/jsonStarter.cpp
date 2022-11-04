#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define ROCK u8"\U0000270A"
#define PAPER u8"\U0000270B"
#define SCISSORS u8"\U0001F44C"
#define LIZARD u8"\U0001F918"
#define SPOCK u8"\U0001F596"

#include "json.hpp"

using json = nlohmann::json;


std::vector< std::string > WEAPONSLIST = {ROCK, PAPER, SCISSORS, LIZARD, SPOCK};

int main(int argc, char** argv){

    json obj;
    std::string FileName;
    int size;

    FileName = "gameData.json";

    std::ifstream input(FileName);
    input >> obj;
    input.close();

    size = obj.size();

    std::cout<<size<<std::endl;

    for (auto& [key, value] : obj.items()) {
        std::cout<<key<<","<<value<<std::endl;
    }

    std::cout<<obj["spock"]["beats"][0]<<std::endl;

    if (obj.contains("lizard")) {
        std::cout<<obj["lizard"]<<std::endl;
    }
}
