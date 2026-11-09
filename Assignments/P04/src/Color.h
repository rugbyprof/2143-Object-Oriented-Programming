#pragma once

#include <ostream>
#include <string>

// -----------------------------------------------------------------------
// Color — an RGB color whose channels are ALWAYS in [0, 255].
// (header provided; YOU implement Color.cpp)
//
// P04 replaces P02/P03's plain struct Pixel with this class. The big
// difference is an INVARIANT: every constructor and operator clamps, so
// no Color can ever hold 300 or -5. The channels are private, so nothing
// outside the class can break that rule. (Image::save no longer needs
// to clamp anything. The class guarantees it.)
//
//   Color orange(255, 128, 0);
//   Color c = orange + 20;            // rgb(255, 148, 20)  (r clamped)
//   Color d = orange * 0.5;           // rgb(128, 64, 0)
//   Color w = Color::fromHex("#ffffff");
//   std::cout << d;                   // rgb(128, 64, 0)
// -----------------------------------------------------------------------
class Color {
public:
    Color();                      // black
    Color(int r, int g, int b);   // each channel clamped to [0, 255]

    // Named constructors (static factory methods)
    static Color gray(int level);                 // Color(level, level, level)
    static Color fromHex(const std::string& hex); // "#ff8000" or "ff8000"
                                                  // throws std::invalid_argument

    int r() const;
    int g() const;
    int b() const;

    // Channel by index: 0 = r, 1 = g, 2 = b. Throws std::out_of_range.
    // Returns a copy (not int&), so it can't be used to break the invariant.
    int operator[](int channel) const;

    // Perceived brightness: 0.299*r + 0.587*g + 0.114*b, ROUNDED to the
    // nearest int (std::lround). Don't truncate: for a gray like (254,254,254)
    // the sum is 253.99999999999997 in floating point, and truncating gives
    // 253. Rounding makes luminance() of any gray equal that gray.
    int luminance() const;

    // Arithmetic. Every result is clamped.
    Color operator+(const Color& other) const;   // channel by channel
    Color operator-(const Color& other) const;   // channel by channel
    Color operator+(int delta) const;            // add delta to all three
    Color operator*(double factor) const;        // scale all three, rounded
    friend Color operator*(double factor, const Color& c);   // 0.5 * c

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    // Prints  rgb(255, 128, 0)
    friend std::ostream& operator<<(std::ostream& os, const Color& c);

private:
    static int clamp(int value);

    int r_ = 0;
    int g_ = 0;
    int b_ = 0;
};
