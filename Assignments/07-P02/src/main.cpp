// main.cpp — Program 2 driver
//
// You should not need to change this file.
// All parsing logic belongs in Args.h and Args.cpp.

#include "Args.h"

int main(int argc, char* argv[]) {
    Args args = Args::parse(argc, argv);
    args.print();
    return 0;
}
