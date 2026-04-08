/**
 * args_vector.cpp — imgtool command-line parser (vector solution)
 *
 * Approach: copy argv[1..n] into a vector<string> and treat it as
 * a token queue — inspect front(), erase front() to consume.
 *
 * This is the starting point for a progression of solutions:
 *
 *   Stage 1 (here)  vector<string> queue + struct with typed members
 *   Stage 2         map<string,bool> + map<string,int> — named lookup, awkward split
 *   Stage 3         map<string, variant<bool,int,string>> — one map, type-safe
 *   Stage 4         map<string, any> — fully dynamic, discuss tradeoffs
 *   Stage 5         nlohmann JSON — argument definitions live in a file
 *
 * Discussion points are marked with [D] in comments.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// -------------------------------------------------------
// Utilities
// -------------------------------------------------------

struct Cmd{
    string name;
    string val;
    // Cmd(string name,char* val):name(name),val(val) {}
    Cmd(string name,string val):name(name),val(val) {}
    friend ostream& operator <<(ostream& os,const Cmd &c){
        return os << "Name:"<<c.name.substr(2)<<", Val: "<<c.val<<endl;
    }
};

bool isImageFile (const std::string& filename) {
    std::string lower = filename;

    // convert entire string to lowercase
    std::transform (lower.begin (), lower.end (), lower.begin (), ::tolower);

    std::vector<std::string> exts = { ".jpg", ".jpeg", ".png", ".bmp", ".gif", ".ppm" };

    for (const auto& ext : exts) {
        if (lower.size () >= ext.size () && lower.compare (lower.size () - ext.size (), ext.size (), ext) == 0) {
            return true;
        }
    }

    return false;
}

void error (const string& type, const string& msg) {
    cerr << "\033[31mError\033[0m \033[33m" << type << "\033[0m: " << msg << "\n";
    cerr << "Usage: ./imgtool <input> <output> [options]\n";
}

// Split "--brighten=20" into ("--brighten", "20").
// Returns ("token", "") when there is no '='.
pair<string, string> splitEq (const string& token) {
    size_t eq = token.find ('=');
    if (eq == string::npos)
        return { token, "" };
    return { token.substr (0, eq), token.substr (eq + 1) };
}

bool startsWith (const string& s, const string& prefix) {
    return s.rfind (prefix, 0) == 0; // C++20 has s.starts_with()
}

// -------------------------------------------------------
// Args struct
//
// One named field per known option.
//
// [D] Compare to map<string,T>:
//     Pros: named access, type safety, no lookup overhead.
//     Cons: adding a new option means editing the struct everywhere.
//     That friction is what motivates the map stages.
// -------------------------------------------------------

struct Args {
    // positional
    string input;
    string output;
    vector<Cmd> cmds;

    // flags (bool, default false)
    bool grayscale = false;
    bool blur      = false;
    bool flipH     = false;
    bool flipV     = false;

    // valued options — keep "was it set?" separate from the value
    // [D] Why not just use -1 as a sentinel? Because -1 is a valid brighten value.
    //     std::optional<int> is cleaner — introduce that in stage 3.
    bool use_brighten = false;
    int brighten      = 0;
    bool use_rotate   = false;
    int rotate        = 0;

    // -------------------------------------------------------
    // Static factory
    //
    // [D] Why static factory instead of Args(argc, argv)?
    //     A constructor can't return a failure state cleanly.
    //     This factory can throw, or we can change it to return
    //     optional<Args> later without touching call sites.
    // -------------------------------------------------------
    static Args parse (int argc, char* argv[]) {
        Args args;

        // [D] The vector is our token queue.
        //     front() = peek.  erase(begin()) = pop.
        //     This is O(n) per pop — that's why deque exists.
        vector<string> tokens;
        for (int i = 1; i < argc; ++i)
            tokens.push_back (argv[i]);

        // ---- positional args (required) ----
        // #1 check for NO params
        if (tokens.empty ()) {
            error ("missing args", "input and output files are required");
            exit (1);
        }

        // There are params so lets hope they are file names
        // required first param is an input file name
        // .front copies front element without altering (mutating) the container
        args.input = tokens.front ();

        // #2 check makes sure its an image (by extension only)
        if (!isImageFile (args.input)) {
            error ("Wrong Filetype", "input file is not an image file");
            exit (1);
        }

        // .erase is a mutating fool. whatever was on the front is now in args.input
        // and removed from tokens
        tokens.erase (tokens.begin ());

        // #3 check is to see if the tokens vector only had one filename in it (empty)
        // if vector is empty so nothing to do but error
        if (tokens.empty ()) {
            error ("missing args", "output file is required");
            exit (1);
        }
        // grab a copy of the front element. .front does not mutate the
        // container (it just reads the value)
        args.output = tokens.front ();

        // .erase mutates the crap out of the vector so front is now out
        // of the vector
        tokens.erase (tokens.begin ());

        // #4 check again checks for valid image file extension (not a legit way in real world)
        if (!isImageFile (args.output)) {
            error ("Wrong Filetype", "output file is not an image file");
            exit (1);
        }

        // ---- optional flags and valued options ----

        // while the vector has crap in it ...
        //ACTION!
        while (!tokens.empty ()) {
            // 1.  splitEq handles any tokens with this setup: "--brighten=20" and "--brighten 20" uniformly.
            //     After this, flag is the option name; inline_val is either
            //     the part after '=' or an empty string.

            // #1 check
            auto [flag, inline_val] = splitEq (tokens.front ());
            cout <<"flag: "<< flag << " val: " << inline_val << endl;
            args.cmds.push_back(Cmd(flag,inline_val));
            tokens.erase (tokens.begin ());



            // --- pure flags ---

            if (flag == "--grayscale" || flag == "-g") {
                args.grayscale = true;
            } else if (flag == "--blur" || flag == "-l") {
                args.blur = true;
            } else if (flag == "--flipH" || flag == "-h") {
                args.flipH = true;
            } else if (flag == "--flipV" || flag == "-v") {
                args.flipV = true;
            }

            // --- valued options ---

            else if (flag == "--brighten" || flag == "-b") {
                string val = inline_val;

                if (val.empty ()) {
                    // value must follow as the next token
                    if (tokens.empty ()) {
                        error ("missing value", flag + " requires an integer");
                        exit (1);
                    }
                    if (startsWith (tokens.front (), "-")) {
                        error ("missing value", flag + " expected a value but got " + tokens.front ());
                        exit (1);
                    }
                    val = tokens.front ();
                    tokens.erase (tokens.begin ());
                }

                // [D] stoi throws std::invalid_argument on non-numeric input
                //     and std::out_of_range on overflow.  Catch-all is lazy
                //     but fine for teaching; in production catch each type.
                try {
                    args.brighten = stoi (val);
                } catch (...) {
                    error ("invalid value", flag + " expects an integer, got \"" + val + "\"");
                    exit (1);
                }
                if (args.brighten < -255 || args.brighten > 255) {
                    error ("out of range", flag + " must be in [-255, 255], got " + val);
                    exit (1);
                }
                args.use_brighten = true;

            } else if (flag == "--rotate" || flag == "-r") {
                string val = inline_val;

                if (val.empty ()) {
                    if (tokens.empty ()) {
                        error ("missing value", flag + " requires an integer");
                        exit (1);
                    }
                    if (startsWith (tokens.front (), "-")) {
                        error ("missing value", flag + " expected a value but got " + tokens.front ());
                        exit (1);
                    }
                    val = tokens.front ();
                    tokens.erase (tokens.begin ());
                }

                int deg;
                try {
                    deg = stoi (val);
                } catch (...) {
                    error ("invalid value", flag + " expects an integer, got \"" + val + "\"");
                    exit (1);
                }
                if (deg != 0 && deg != 90 && deg != 180 && deg != 270) {
                    error ("invalid value", flag + " must be one of {0,90,180,270}, got " + val);
                    exit (1);
                }
                args.rotate     = deg;
                args.use_rotate = true;

            } else {
                error ("unknown option", flag);
                exit (1);
            }
        }

        return args;
    }

    void print () const {
        cout << "INPUT  : " << input << "\n";
        cout << "OUTPUT : " << output << "\n";

        cout << "FLAGS  :";
        if (grayscale)
            cout << " grayscale";
        if (blur)
            cout << " blur";
        if (flipH)
            cout << " flipH";
        if (flipV)
            cout << " flipV";
        cout << "\n";

        cout << "PARAMS :";
        if (use_brighten)
            cout << " brighten=" << brighten;
        if (use_rotate)
            cout << " rotate=" << rotate;
        cout << "\n";
    }

    // vector<Cmd> getCmds(){
    //     vector<Cmd> cmds;

    //     return cmds;
    // }

};

