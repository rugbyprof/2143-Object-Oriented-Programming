// Platform.cpp — YOU implement openInDefaultViewer.

#include "Platform.h"

#include <cstdlib>   // std::system

bool openInDefaultViewer(const std::string& path) {
    // TODO: build the right command for the operating system, using
    //   #if defined(_WIN32) / #elif defined(__APPLE__) / #else / #endif
    // then run it with std::system(cmd.c_str()). See the README.
    (void)path;
    return false;
}
