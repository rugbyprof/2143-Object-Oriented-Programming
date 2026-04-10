// image_example.cpp — demonstrates the Image class.
//
// P04 update: Color is now Color. The pixel access pattern is unchanged —
// Color has the same .r / .g / .b members as Color did, plus arithmetic
// operators (+, *) and indexed access (c[0], c[1], c[2]).
//
// -----------------------------------------------------------------------
// Build (from the project root, 11-P04/):
//
//   g++ -std=c++17 -O2 -Wall -Wextra -pedantic -isystem include \
//       src/image_example.cpp src/Image.cpp src/Color.cpp src/Kernel.cpp \
//       -o image_example
//
// Why -isystem instead of -I?
//   -I tells the compiler to search a directory for headers AND emit
//   warnings for code inside those headers.
//   -isystem does the same search but marks the directory as "system
//   code" — warnings from inside the stb headers are suppressed.
//   Our own code still gets full -Wall -Wextra treatment.
// -----------------------------------------------------------------------
//
// Run:
//   ./image_example

#include "Image.h"
#include <algorithm>    // std::clamp (C++17)
#include <iostream>

// -----------------------------------------------------------------------
// Filter functions
//
// Each function takes an Image by reference and modifies it in-place.
// This mirrors the ppm_example.cpp pattern (grayScale, brighten) but the
// data structure is now a proper class instead of a raw struct with
// parallel R/G/B vectors.
//
// Since Color channels are int, arithmetic is clean — no casts needed.
// Image::save() clamps values back to [0, 255] before writing to disk.
// -----------------------------------------------------------------------

// Convert every pixel to grayscale using the luminance formula.
// (same formula as P01's starter code)
void grayScale(Image& img) {
    for (int row = 0; row < img.height(); ++row) {
        for (int col = 0; col < img.width(); ++col) {
            int r = img[row][col].r;
            int g = img[row][col].g;
            int b = img[row][col].b;

            // Luminance formula — weights more green because the eye is
            // more sensitive to green than red or blue.
            int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

            img[row][col] = Color(gray, gray, gray);
        }
    }
}

// Add 'amount' to every channel (positive = brighter, negative = darker).
// Channels are int, so no overflow risk; save() clamps on write.
void brighten(Image& img, int amount) {
    for (int row = 0; row < img.height(); ++row) {
        for (int col = 0; col < img.width(); ++col) {
            img[row][col].r += amount;
            img[row][col].g += amount;
            img[row][col].b += amount;
        }
    }
}

// Flip the image horizontally (mirror left-right).
void flipH(Image& img) {
    for (int row = 0; row < img.height(); ++row) {
        for (int col = 0; col < img.width() / 2; ++col) {
            int mirror = img.width() - 1 - col;
            std::swap(img[row][col], img[row][mirror]);
        }
    }
}

// -----------------------------------------------------------------------
// Demonstration: print first 5x5 pixels (top-left corner)
// -----------------------------------------------------------------------
void printCorner(const Image& img) {
    int rows = std::min(5, img.height());
    int cols = std::min(5, img.width());
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            std::cout << img[row][col] << "  ";
        }
        std::cout << "\n";
    }
}

// -----------------------------------------------------------------------
// main
// -----------------------------------------------------------------------
int main() {
    Image img = Image::load("in.png");
    std::cout << "Loaded: " << img << "\n\n";

    std::cout << "Top-left 5x5 corner (original):\n";
    printCorner(img);
    std::cout << "\n";

    // --- grayscale ---
    Image gray = img;
    grayScale(gray);
    gray.save("out_grayscale.png");
    gray.save("out_grayscale.jpg");
    std::cout << "Saved grayscale as PNG and JPEG.\n";

    // --- brighten ---
    Image bright = img;
    brighten(bright, 50);
    bright.save("out_brighten.png");
    std::cout << "Saved brightened image.\n";

    // --- flip ---
    Image flipped = img;
    flipH(flipped);
    flipped.save("out_flipH.png");
    std::cout << "Saved horizontally flipped image.\n";

    // --- create from scratch ---
    Image canvas(200, 200);
    for (int row = 0; row < canvas.height(); ++row) {
        for (int col = 0; col < canvas.width(); ++col) {
            if (std::abs(row - col) < 10) {
                canvas[row][col] = Color(255, 0, 0);   // red stripe
            } else {
                canvas[row][col] = Color(30, 30, 30);  // dark background
            }
        }
    }
    canvas.save("out_stripe.png");
    std::cout << "Saved synthetic stripe image.\n";

    return 0;
}

// -----------------------------------------------------------------------
// COMPARISON: ppm_example.cpp vs image_example.cpp
//
// ppm_example.cpp                      image_example.cpp (this file)
// -------------------------------------------------------
// IMG image;                           Image img = Image::load("in.png");
// loadPPM(image, "in.ppm");
//
// image.R[i]                           img[row][col].r
// image.G[i]                           img[row][col].g
// image.B[i]                           img[row][col].b
//
// for (int i=0; i<w*h; i++)            for (int row=0; row<img.height(); row++)
//   image.R[i] = ...                     for (int col=0; col<img.width(); col++)
//                                          img[row][col].r = ...
//
// savePPM(image, "out.ppm");           img.save("out.png");
//                                      img.save("out.jpg");   // same pixels!
//
// Key differences:
//  - No separate R/G/B arrays; all three channels travel together as a Color
//  - 2D [row][col] indexing instead of flat [i] with manual row*width+col math
//  - Any format stb_image supports; not just .ppm
//  - Color channels are int — no unsigned char overflow surprises
// -----------------------------------------------------------------------
