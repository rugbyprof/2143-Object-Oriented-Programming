#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <iostream>
#include <string>

#include "stb_image.h"
#include "stb_image_write.h"
#include "termcolor.hpp"

using namespace std;
using namespace termcolor;


class ImageTools{
    string imageName;
    int width;
    int height;
    int channels;
    unsigned char* data;
public:
    ImageTools(){}
    ImageTools(string imgName): imageName(imgName){
        data = stbi_load(imageName.c_str(),
                         &width,
                         &height,
                         &channels,
                         3);
        if (!data) {
            cerr << "Failed to load image: " << imageName << "\n";
        }
    }

    void grayScale() {
        // Hardcoded grayscale (luminance)
        for (int i = 0; i < width*height; ++i) {
            int idx = i * channels;

            int r = data[idx + 0];
            int g = data[idx + 1];
            int b = data[idx + 2];

            int gray = static_cast<int>(0.299 * r + 0.587 * g + 0.114 * b);

            // gray will already be in [0,255] for this formula
            unsigned char gr = static_cast<unsigned char>(gray);

            data[idx + 0] = gr;
            data[idx + 1] = gr;
            data[idx + 2] = gr;
        }
    }

    unsigned char* getData(){
        return data;
    }

    ~ImageTools(){}
};



// ------------------------------------------------------------
// Program 1 (Starter):
// - Uses argv[1] argv[2] for input/output
// - Loads an image, converts it to grayscale, saves as PNG
//
// YOU will add:
//   (A) termcolor for colored messages
//   (B) a function to open the output image automatically
// ------------------------------------------------------------

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cout<<red<<"===============================================\n"<<reset;
        std::cout << "Usage: ./imgtool <input_image> <output_image>\n";
        std::cout<<red<<"===============================================\n"<<reset;
        return 1;
    }

    // get input and output paths
    std::string inputPath  = argv[1];
    std::string outputPath = argv[2];

    int width = 0, height = 0, channels_in_file = 0;

    // Force RGB (3 channels)
    unsigned char* data = stbi_load(inputPath.c_str(),
                                    &width,
                                    &height,
                                    &channels_in_file,
                                    3);

    if (!data) {
        std::cerr << "Failed to load image: " << inputPath << "\n";
        return 1;
    }

    const int channels = 3;
    const int totalPixels = width * height;

    std::cout << "Loaded image: " << width << "x" << height
              << " channels: " << channels << "\n";

    data = grayScale(data, width, height, channels);

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

    // TODO (Student): open output file automatically in default viewer

    return 0;
}