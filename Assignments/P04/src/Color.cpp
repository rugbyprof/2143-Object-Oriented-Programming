// Color.cpp — YOU implement the functions marked TODO.
//
// Rule of thumb: build every result with the Color(int, int, int)
// constructor. It clamps, so your operators get the invariant for free.

#include "Color.h"

#include <algorithm>   // std::clamp
#include <cctype>      // std::isxdigit
#include <cmath>       // std::lround
#include <stdexcept>

// ---- provided ----

int Color::clamp(int value) {
    return std::clamp(value, 0, 255);
}

Color::Color() = default;

Color::Color(int r, int g, int b) : r_(clamp(r)), g_(clamp(g)), b_(clamp(b)) {}

int Color::r() const { return r_; }
int Color::g() const { return g_; }
int Color::b() const { return b_; }

// ---- TODO ----

Color Color::gray(int level) {
    (void)level;
    return Color();   // TODO
}

Color Color::fromHex(const std::string& hex) {
    // TODO: "#ff8000" or "ff8000" -> Color(255, 128, 0)
    //   - strip one leading '#'
    //   - exactly 6 characters, each std::isxdigit, or throw std::invalid_argument
    //   - std::stoi(two_chars, nullptr, 16) turns "ff" into 255
    (void)hex;
    return Color();
}

int Color::operator[](int channel) const {
    // TODO: 0 -> r_, 1 -> g_, 2 -> b_, anything else -> throw std::out_of_range
    (void)channel;
    return 0;
}

int Color::luminance() const {
    return 0;   // TODO: see Color.h (round, don't truncate)
}

Color Color::operator+(const Color& other) const {
    (void)other;
    return Color();   // TODO
}

Color Color::operator-(const Color& other) const {
    (void)other;
    return Color();   // TODO
}

Color Color::operator+(int delta) const {
    (void)delta;
    return Color();   // TODO
}

Color Color::operator*(double factor) const {
    (void)factor;
    return Color();   // TODO: round each product with std::lround
}

Color operator*(double factor, const Color& c) {
    (void)factor;
    (void)c;
    return Color();   // TODO: one line, reuse the member operator*
}

bool Color::operator==(const Color& other) const {
    (void)other;
    return false;   // TODO
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
    (void)c;
    return os;   // TODO: rgb(255, 128, 0)
}
