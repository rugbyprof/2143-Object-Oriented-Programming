#pragma once

#include <string>

// Opens a file with the operating system's default program for it
// (Preview / Photos / an image viewer), the same as double-clicking it.
//
// Returns true if the open command ran successfully. On a machine with
// no display (Codespaces, SSH), this returns false. That's expected and
// not an error.
bool openInDefaultViewer(const std::string& path);
