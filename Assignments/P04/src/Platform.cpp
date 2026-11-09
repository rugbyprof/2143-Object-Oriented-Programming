// Platform.cpp — provided (the P02 solution).

#include "Platform.h"

#include <cstdlib>

bool openInDefaultViewer(const std::string& path) {
    // The preprocessor keeps only the branch for the OS we compile on.
#if defined(_WIN32)
    std::string cmd = "start \"\" \"" + path + "\"";
#elif defined(__APPLE__)
    std::string cmd = "open \"" + path + "\"";
#else
    std::string cmd = "xdg-open \"" + path + "\" >/dev/null 2>&1";
#endif
    return std::system(cmd.c_str()) == 0;
}
