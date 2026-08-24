// img2ppm.cpp
// Converts JPG or PNG images to uncompressed PPM (P3 ASCII format)
//
// Requires: stb_image.h (single-header library)
// Get it from: https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
// Place stb_image.h in the same directory as this file before compiling.
//
// Compile:
//   g++ -O2 -o img2ppm img2ppm.cpp
//
// Usage:
//   ./img2ppm input.jpg output.ppm
//   ./img2ppm input.png output.ppm

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

// Lowercase a string (for extension checking)
static std::string toLower (std::string s) {
    std::transform (s.begin (), s.end (), s.begin (), ::tolower);
    return s;
}

// Get file extension (including the dot), lowercased
static std::string getExtension (const std::string& path) {
    size_t dot = path.rfind ('.');
    if (dot == std::string::npos)
        return "";
    return toLower (path.substr (dot));
}

int main (int argc, char* argv[]) {
    // ---------------------------------------------------------------
    // 1. Argument validation
    // ---------------------------------------------------------------
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.(jpg|png)> <output.ppm>\n";
        return 1;
    }

    const std::string inputPath  = argv[1];
    const std::string outputPath = argv[2];

    // Check that the input is a supported format
    const std::string ext = getExtension (inputPath);
    if (ext != ".jpg" && ext != ".jpeg" && ext != ".png") {
        std::cerr << "Error: input file must be a .jpg/.jpeg or .png (got '" << ext << "')\n";
        return 1;
    }

    // ---------------------------------------------------------------
    // 2. Load the image with stb_image
    //    Force 3 channels (RGB) — strips alpha, handles grayscale, etc.
    // ---------------------------------------------------------------
    int width = 0, height = 0, channelsInFile = 0;
    const int FORCE_RGB = 3;

    unsigned char* pixels = stbi_load (inputPath.c_str (), &width, &height, &channelsInFile, FORCE_RGB);

    if (!pixels) {
        std::cerr << "Error: could not load image '" << inputPath << "'\n";
        std::cerr << "       stb_image says: " << stbi_failure_reason () << "\n";
        return 1;
    }

    std::cout << "Loaded: " << inputPath << "\n"
              << "  Size:     " << width << " x " << height << " pixels\n"
              << "  Channels: " << channelsInFile << " (forcing RGB output)\n";

    // ---------------------------------------------------------------
    // 3. Write PPM P3 (ASCII uncompressed)
    //
    //    PPM P3 format:
    //      P3\n
    //      <width> <height>\n
    //      <max_value>\n
    //      R G B  R G B  R G B ...   (one row per line, values 0-255)
    // ---------------------------------------------------------------
    std::ofstream out (outputPath); // text mode — no std::ios::binary
    if (!out.is_open ()) {
        std::cerr << "Error: could not open output file '" << outputPath << "' for writing\n";
        stbi_image_free (pixels);
        return 1;
    }

    // Write PPM header (no blank lines — strict single newline between fields)
    out << "P3\n"
        << width << " " << height << "\n"
        << "255\n";

    // Write pixel data as ASCII decimal triplets, one row per line
    const size_t dataSize = static_cast<size_t> (width) * height * FORCE_RGB;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const unsigned char* px = pixels + (y * width + x) * FORCE_RGB;
            out << static_cast<int> (px[0]) << " " // R
                << static_cast<int> (px[1]) << " " // G
                << static_cast<int> (px[2]);       // B
            if (x < width - 1)
                out << "  "; // space between pixels
        }
        out << "\n"; // newline after each row
    }

    if (!out.good ()) {
        std::cerr << "Error: failed to write pixel data to '" << outputPath << "'\n";
        stbi_image_free (pixels);
        return 1;
    }

    out.close ();
    stbi_image_free (pixels);

    // P3 files are much larger than P6 — warn the user if it'll be chunky
    const double sizeMB = static_cast<double> (dataSize) / (1024.0 * 1024.0);
    std::cout << "Written: " << outputPath << "\n"
              << "  Pixels: " << (width * height) << " (" << width << " x " << height << ")\n"
              << "  Approx raw size: " << sizeMB << " MB (ASCII will be ~3-4x larger)\n"
              << "Done!\n";

    return 0;
}