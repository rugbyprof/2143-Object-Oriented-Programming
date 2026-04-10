#pragma once
#include <iostream>
#include <string>

class Color {
public:
    // Constructors
    Color();                        // black (0, 0, 0)
    Color(int r, int g, int b);     // clamped to [0, 255]

    // Static factories
    static Color fromRGB(int r, int g, int b);
    static Color fromHex(const std::string& hex);          // "#ff8000" or "ff8000"
    static Color fromHSL(double h, double s, double l);    // h in [0,360), s/l in [0,1]

    // Channel access by index: 0=r, 1=g, 2=b
    int&       operator[](int index);
    const int& operator[](int index) const;

    // Arithmetic
    Color operator+(const Color& other) const;
    Color operator*(double scalar) const;
    friend Color operator*(double scalar, const Color& c);

    // Comparison
    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;

    // I/O
    friend std::ostream& operator<<(std::ostream& os, const Color& c);
    friend std::istream& operator>>(std::istream& is, Color& c);

    // Channels are public so P03 filter code (p.r, p.g, p.b) compiles unchanged.
    // The Color(int,int,int) constructor clamps on construction.
    // Direct assignment can go out of range — Image::save() clamps on write.
    int r, g, b;

private:
    static int clamp(int val);          // clamp to [0, 255]
    static int clampDouble(double val); // clamp double channel to [0, 255]
};
