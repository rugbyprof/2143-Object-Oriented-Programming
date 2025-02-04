#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct Node {
    int         id;
    std::string first_name;
    std::string last_name;
    std::string city;
    std::string country;
    std::string company;

    Node(int _id, std::string _first, std::string _last, std::string _city, std::string _country, std::string _company)
        : id(_id), first_name(_first), last_name(_last), city(_city), country(_country), company(_company) {}
};

std::vector< Node > readCSV(const std::string& filename) {
    std::vector< Node > nodes;
    std::ifstream       file(filename);
    std::string         line, token;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return nodes;
    }

    // Read the first line (header) and discard it
    std::getline(file, line);

    // Read each remaining line in the file
    while (std::getline(file, line)) {
        std::stringstream          ss(line);
        std::vector< std::string > tokens;

        // Split line by commas
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Ensure the correct number of columns (6)
        if (tokens.size() == 6) {
            int id = std::stoi(tokens[0]);  // Convert id from string to int
            nodes.emplace_back(id, tokens[1], tokens[2], tokens[3], tokens[4], tokens[5]);
        } else {
            std::cerr << "Skipping invalid row: " << line << std::endl;
        }
    }

    file.close();
    return nodes;
}

int main() {
    std::vector< Node > data = readCSV("world_people.csv");

    // Print the loaded data
    for (const auto& person : data) {
        std::cout << "ID: " << person.id
                  << ", Name: " << person.first_name << " " << person.last_name
                  << ", City: " << person.city
                  << ", Country: " << person.country
                  << ", Company: " << person.company << std::endl;
    }

    return 0;
}