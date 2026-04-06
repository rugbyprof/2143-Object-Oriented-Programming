// Classroom discussion

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Args {
private:
public:
};

int main (int argc, char** argv) {
    // cout << argc << endl;
    // cout << argv[0] << endl;

    for (int i = 0; i < argc; i++) {
        cout << i << ": " << argv[i] << endl;
    }

    if (argc < 2) {
        cout << "Error: need a filename!" << endl;
        cout << "Usage: ./args <filename>" << endl;
        exit (1);
    }

    if (string (argv[3]) == "--grayscale") {
        // do something
    }
    ifstream fin;
    fin.open ("input");


    int x;
    while (!fin.eof ()) {
        fin >> x;
        cout << x << " ";
    }
}