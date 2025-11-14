#pragma once
#include <random>

// --------------------------------------------------------------
// Function: wrapIndex
// Purpose : Wrap an integer index into the valid range [0, max-1].
//           This is useful when implementing grids that "wrap around"
//           (e.g., toroidal Game of Life, circular buffers, etc.).
//
// Why it's needed:
//   In C++, the % operator keeps the *sign* of the left operand,
//   so negative values produce negative results.
//
//   Example:
//       -1 % 5 == -1    (C++ behavior)
//       We actually want: -1 → 4
//
// Algorithm:
//   1. Compute value % max
//   2. If it is negative, add max to bring it into range
//
// Examples:
//   wrapIndex(0, 5)  -> 0
//   wrapIndex(4, 5)  -> 4
//   wrapIndex(5, 5)  -> 0  (wraps around)
//   wrapIndex(-1, 5) -> 4  (negative wrap)
// --------------------------------------------------------------
inline int wrapIndex(int value, int max) {
    int result = value % max;         // may be negative in C++
    return result < 0 ? result + max  // fix negative remainder
                      : result;       // already in range
}