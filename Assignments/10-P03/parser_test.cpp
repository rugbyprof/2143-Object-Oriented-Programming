#include "parser.hpp"

// -------------------------------------------------------
// main — just parses and prints
// -------------------------------------------------------

int main (int argc, char* argv[]) {
    Args args = Args::parse (argc, argv);
    args.print ();
    vector<Cmd> cmds = args.cmds;

    for (auto &cmd : cmds){
        cout<<cmd<<endl;
    }
    
    return 0;
}