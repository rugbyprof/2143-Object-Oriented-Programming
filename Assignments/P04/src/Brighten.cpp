// Brighten.cpp — provided, already ported to P04. Read it first.
//
// P03 version:                      P04 version:
//   for (auto& row : pixels)          pixels.forEach([this](Color& c) {
//       for (Pixel& p : row) {            c = c + amount_;
//           p.r += amount_;           });
//           p.g += amount_;
//           p.b += amount_;
//       }
//
// forEach is Matrix's member template: it takes any callable. The lambda
// captures 'this' so it can read amount_. Color's operator+(int) adds to
// all three channels and clamps.
//
// One behavior change: P03 let channels go past 255 mid-pipeline and
// clamped only on save. Color clamps immediately. So "brighten 100 then
// brighten -100" no longer gets you back where you started. That's the
// price of the invariant.

#include "Brighten.h"

Brighten::Brighten(int amount) : amount_(amount) {}

std::string Brighten::name() const {
    return "brighten(" + std::to_string(amount_) + ")";
}

void Brighten::apply(Grid& pixels) {
    pixels.forEach([this](Color& c) { c = c + amount_; });
}
