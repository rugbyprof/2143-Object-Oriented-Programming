// Classroom discussion

#include <iostream>

using namespace std;

class Args {
    public:
    std::string input_file;
    std::string output_file;
    bool verbose   = false;
    int rotate     = 0;
    int brightness = 0;
    int grayscale  = 0;
    // more


    static Args parse (int argc, char* argv[]) {
        Args args;
        // args.parse_impl (argc, argv);
        // args.validate ();

        // read through argv and find if any of the arguments match items in the assignment.
        return args;
    }

    static Args fromFile (string filename) {
        // open the file
        // assign the arguments from the file
    }

    private:
    Args () = default;

    void parse_impl (int argc, char* argv[]) {
        // parse flags and values
    }

    void validate () {
        // check correctness
    }
};


int main (int argc, char** argv) {
    Args arg1 = Args::parse (argc, argv);

    Args arg2 = Args::fromFile (infile);


    return 0;
}