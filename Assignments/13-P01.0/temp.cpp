#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;
using namespace std;

int main() {
    // 1) Creating a new JSON object and adding top-level items
    json student;
    student["name"]    = "John Doe";
    student["gpa"]     = 3.85;  // A floating-point number
    student["courses"] = {"CS101", "Math202", "History10"};

    // 2) Creating a nested JSON object for test scores
    json testScores;
    testScores["test1"] = 94;
    testScores["test2"] = 88;
    testScores["test3"] = 76;

    // Add the nested JSON object to the main "student" JSON
    student["scores"] = testScores;

    // 3) Printing out the entire JSON object
    cout << "Student JSON:\n" << student.dump(4) << endl << endl;

    // 4) Iterating over the JSON object
    cout << "Iterating over top-level fields:\n";
    for (auto& el : student.items()) {
        cout << el.key() << " : " << el.value() << endl;
    }
    cout << endl;

    // 5) Iterating over the nested object (test scores)
    cout << "Iterating over test scores:\n";
    for (auto& el : student["scores"].items()) {
        cout << el.key() << " : " << el.value() << endl;
    }

    return 0;
}



