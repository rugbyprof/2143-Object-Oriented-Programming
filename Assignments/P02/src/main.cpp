#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>

#include "stb_image.h"
#include "stb_image_write.h"

// ------------------------------------------------------------
// P02 Image Tool (Starter):
// - Uses argv[1] argv[2] for input/output
// - Loads an image, converts it to grayscale, saves as PNG
//
// YOU will add:
//   (A) FTXUI for colored messages
//   (B) a function to open the output image automatically
// ------------------------------------------------------------

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: ./imgtool <input_image> <output_image>\n";
        return 1;
    }

    std::string inputPath  = argv[1];
    std::string outputPath = argv[2];

    int width = 0, height = 0, channels_in_file = 0;

    // Force RGB (3 channels), no matter what the file has
    unsigned char* data = stbi_load(inputPath.c_str(),
                                    &width,
                                    &height,
                                    &channels_in_file,
                                    3);

    if (!data) {
        std::cerr << "Failed to load image: " << inputPath << "\n";
        return 1;
    }

    const int channels    = 3;
    const int totalPixels = width * height;

    std::cout << "Loaded image: " << width << "x" << height
              << " channels: " << channels << "\n";

    // Hardcoded grayscale (luminance)
    for (int i = 0; i < totalPixels; ++i) {
        int idx = i * channels;

        int r = data[idx + 0];
        int g = data[idx + 1];
        int b = data[idx + 2];

        // The weights add up to 1.0, so gray is always in [0, 255]
        int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

        unsigned char gr = static_cast<unsigned char>(gray);

        data[idx + 0] = gr;
        data[idx + 1] = gr;
        data[idx + 2] = gr;
    }

    // Save PNG
    if (!stbi_write_png(outputPath.c_str(),
                        width,
                        height,
                        channels,
                        data,
                        width * channels)) {

        std::cerr << "Failed to write output image: " << outputPath << "\n";
        stbi_image_free(data);
        return 1;
    }

    stbi_image_free(data);

    std::cout << "Saved output to: " << outputPath << "\n";

    // TODO (Task B): open output file automatically in default viewer

    return 0;
}
