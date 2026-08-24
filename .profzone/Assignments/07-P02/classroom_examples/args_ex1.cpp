// args_ex1.cpp — Classroom Discussion: What NOT to Do
//
// This is the raw first sketch from class. It shows the naive approach
// and several common mistakes. Read the comments to understand why each
// pattern is problematic.
//
// Compare this to args_ex2.cpp, which shows the correct direction.

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// PROBLEM: Args class is completely empty — no members, no methods.
// It stores nothing and does nothing. This is where students usually
// start: they know they need a class but aren't sure what goes in it yet.
class Args {
private:
public:
};

int main(int argc, char** argv) {
    // Iterating argv is a fine first step for understanding what arrives.
    // argv[0] is always the program name; user args start at argv[1].
    for (int i = 0; i < argc; i++) {
        cout << i << ": " << argv[i] << endl;
    }

    // PROBLEM: this check says "exit if fewer than 2 args total" but
    // argc includes argv[0] (the program name), so this triggers when
    // the user provides zero arguments, not one.
    // A more honest check for "user gave us nothing" would be argc < 2.
    if (argc < 2) {
        cout << "Error: need a filename!" << endl;
        cout << "Usage: ./args <filename>" << endl;
        exit(1);
    }

    // PROBLEM: argv[3] is hardcoded. If the user provides fewer than
    // 4 arguments this is undefined behavior — the program may crash,
    // silently read garbage, or do something worse.
    // Always check bounds before indexing into argv.
    if (string(argv[3]) == "--grayscale") {
        // do something
    }

    // PROBLEM: opening a hardcoded filename "input" defeats the whole
    // purpose of parsing command-line arguments.
    ifstream fin;
    fin.open("input");

    // PROBLEM: the while(!fin.eof()) pattern is a classic C++ bug.
    // It reads one extra iteration because eof() is only true AFTER
    // a failed read, not before. The last value gets printed twice.
    // Correct pattern: while (fin >> x) { ... }
    int x;
    while (!fin.eof()) {
        fin >> x;
        cout << x << " ";
    }

    // PROBLEM: no check that fin.open() succeeded.
    // If the file doesn't exist, fin is in a bad state and every
    // read silently fails. Always check: if (!fin) { ... }
}
