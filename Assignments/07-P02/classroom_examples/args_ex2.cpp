// args_ex2.cpp — Classroom Discussion: Factory Pattern Skeleton
//
// This is the structural starting point shown in class.
// The data members are defined and the factory method signature is in place,
// but the parsing logic is left empty — that's the assignment.
//
// Key ideas demonstrated here:
//   1. Typed members for each argument (not raw strings everywhere)
//   2. Static factory method as the only construction path
//   3. Private default constructor to prevent invalid objects
//   4. Multiple named factories for different input sources

#include <iostream>
#include <string>

using namespace std;

class Args {
public:
    // Each argument gets its own typed member.
    // This gives you named access (args.rotate) instead of
    // searching through a string map every time.
    std::string input_file;
    std::string output_file;
    bool  verbose    = false;
    int   rotate     = 0;
    int   brightness = 0;
    bool  grayscale  = false;
    // add more options as needed...

    // ----------------------------------------------------------------
    // Static factory: the one and only way to build a valid Args.
    //
    // "static" means you call it on the class, not an instance:
    //     Args a = Args::parse(argc, argv);
    //
    // It can construct the object (via the private default constructor),
    // fill it in, validate it, and return it — or call exit() on error.
    // ----------------------------------------------------------------
    static Args parse(int argc, char* argv[]) {
        Args args;
        // TODO: implement argv parsing here
        //   - read positional args (input_file, output_file)
        //   - loop over remaining tokens, match flags and options
        //   - validate values; call exit(1) with a message on any error
        return args;
    }

    // ----------------------------------------------------------------
    // Alternative factory: build Args from a config file instead of
    // the command line. Same interface, different input source.
    //
    // This shows why the factory pattern scales — you can add more
    // named construction paths without changing Args()'s meaning.
    // ----------------------------------------------------------------
    static Args fromFile(const string& filename) {
        Args args;
        // TODO: open filename, parse key=value pairs, fill in args
        return args;
    }

private:
    // Private default constructor: the only way to get an Args object
    // is through one of the static factories above. This prevents code
    // like "Args a;" from compiling — no uninitialized Args objects.
    Args() = default;

    void parse_impl(int argc, char* argv[]) {
        // optional helper — split the parsing logic out of parse()
    }

    void validate() {
        // optional helper — check ranges, required fields, etc.
    }
};


int main(int argc, char** argv) {
    // Build an Args from the command line.
    Args arg1 = Args::parse(argc, argv);

    // Build an Args from a config file.
    // Both return the same type — main doesn't care where the data came from.
    Args arg2 = Args::fromFile("config.txt");

    return 0;
}
