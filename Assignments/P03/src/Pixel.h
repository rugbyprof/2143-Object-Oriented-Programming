#pragma once

#include <ostream>

// -----------------------------------------------------------------------
// Pixel — one RGB pixel.  (provided)
//
// Channels are int, not unsigned char, so filter math can go below 0 or
// above 255 for a moment without silently wrapping around. Image::save()
// clamps every channel back into [0, 255] when it writes the file.
//
// A plain struct is fine here: a Pixel has no rules to protect (any three
// ints are a valid Pixel). In P04 it grows into a real Color class with
// operators and invariants.
// -----------------------------------------------------------------------
struct Pixel {
    int r = 0;
    int g = 0;
    int b = 0;
};

// Prints as (r,g,b), e.g. (255,128,0)
inline std::ostream& operator<<(std::ostream& os, const Pixel& p) {
    return os << '(' << p.r << ',' << p.g << ',' << p.b << ')';
}
