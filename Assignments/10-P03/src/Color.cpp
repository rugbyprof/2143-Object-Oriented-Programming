#include "Color.h"
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <cmath>

// -------------------------------------------------------
// Private helpers
// -------------------------------------------------------

int Color::clamp(int val) {
    return std::max(0, std::min(255, val));
}

int Color::clampDouble(double val) {
    return clamp(static_cast<int>(std::round(val)));
}

// -------------------------------------------------------
// Constructors
// -------------------------------------------------------

Color::Color() : r(0), g(0), b(0) {}

Color::Color(int r, int g, int b)
    : r(clamp(r)), g(clamp(g)), b(clamp(b)) {}

// -------------------------------------------------------
// Static factories
// -------------------------------------------------------

Color Color::fromRGB(int r, int g, int b) {
    return Color(r, g, b);
}

Color Color::fromHex(const std::string& hex) {
    const std::string value = (hex.size() == 7 && hex[0] == '#') ? hex.substr(1) : hex;

    if (value.size() != 6) {
        throw std::invalid_argument("hex color must contain exactly 6 hex digits");
    }

    for (char ch : value) {
        if (!std::isxdigit(static_cast<unsigned char>(ch))) {
            throw std::invalid_argument("hex color contains non-hex characters");
        }
    }

    return Color(
        std::stoi(value.substr(0, 2), nullptr, 16),
        std::stoi(value.substr(2, 2), nullptr, 16),
        std::stoi(value.substr(4, 2), nullptr, 16)
    );
}

Color Color::fromHSL(double h, double s, double l) {
    if (!(h >= 0.0 && h < 360.0 && s >= 0.0 && s <= 1.0 && l >= 0.0 && l <= 1.0)) {
        throw std::invalid_argument("hsl values out of range");
    }
    // TODO: implement HSL -> RGB conversion
    //   Hint: when s == 0, result is a gray: rgb = l * 255
    //   Hint: look up the standard HSL->RGB algorithm — understand it, don't just copy it
    // TODO: clamp and return Color(r, g, b)
    // throw std::invalid_argument("...") on bad input
    return Color();  // placeholder
}

// -------------------------------------------------------
// Channel access
// -------------------------------------------------------

int& Color::operator[](int index) {
    // TODO: return r, g, or b based on index
    // throw std::out_of_range("...") if index not in {0, 1, 2}
    switch (index) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        default: throw std::out_of_range("Color: channel index must be 0, 1, or 2");
    }
}

const int& Color::operator[](int index) const {
    // TODO: same as above, const version
    switch (index) {
        case 0: return r;
        case 1: return g;
        case 2: return b;
        default: throw std::out_of_range("Color: channel index must be 0, 1, or 2");
    }
}

// -------------------------------------------------------
// Arithmetic
// -------------------------------------------------------

Color Color::operator+([[maybe_unused]] const Color& other) const {
    // TODO: add channels, clamp result
    //   return Color(clamp(r + other.r), clamp(g + other.g), clamp(b + other.b));
    return Color();  // placeholder
}

Color Color::operator*([[maybe_unused]] double scalar) const {
    // TODO: multiply each channel by scalar, clamp
    //   return Color(clampDouble(r * scalar), clampDouble(g * scalar), clampDouble(b * scalar));
    return Color();  // placeholder
}

Color operator*(double scalar, const Color& c) {
    return c * scalar;   // reuse the above
}

// -------------------------------------------------------
// Comparison
// -------------------------------------------------------

bool Color::operator==([[maybe_unused]] const Color& other) const {
    // TODO: return true if r, g, b all match
    //   return r == other.r && g == other.g && b == other.b;
    return false;  // placeholder
}

bool Color::operator!=(const Color& other) const {
    return !(*this == other);
}

// -------------------------------------------------------
// I/O
// -------------------------------------------------------

std::ostream& operator<<(std::ostream& os, [[maybe_unused]] const Color& c) {
    // TODO: print as rgb(r, g, b)
    //   os << "rgb(" << c.r << ", " << c.g << ", " << c.b << ")";
    return os;  // placeholder
}

std::istream& operator>>(std::istream& is, [[maybe_unused]] Color& c) {
    // TODO: read three integers into c.r, c.g, c.b — clamp each
    //   int r, g, b; is >> r >> g >> b;
    //   c = Color(r, g, b);
    return is;  // placeholder
}
